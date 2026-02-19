#include <SkylanderLayout.hpp>

#include <MainApplication.hpp>

extern MainApplication::Ref g_MainApplication;

static PadState pad;

SkylanderLayout::SkylanderLayout() : Layout::Layout()
{
  // Create the TextBlock instance with the text we want
  this->skylanderText = pu::ui::elm::TextBlock::New(0, 300, "Press x to Scan a Skylander");
  this->progressBar = pu::ui::elm::ProgressBar::New(0, 400, pu::ui::render::ScreenWidth, 50, 16);
  // Add the instance to the layout. IMPORTANT! this MUST be done for them to be used, having them
  // as members is not enough (just a simple way to keep them)
  this->Add(this->skylanderText);
  this->Add(this->progressBar);

  this->SetOnInput([&](const u64 keys_down, const u64 keys_up, const u64 keys_held,
                       const pu::ui::TouchPoint touch_pos) {
    // If + is pressed, exit application
    if (keys_down & HidNpadButton_Plus)
    {
      g_MainApplication->Close();
    }
    else if (keys_down & HidNpadButton_X)
    {
      ProcessSkylander();
    }
    else if (keys_down & HidNpadButton_B)
    {
      g_MainApplication->LoadLayout(g_MainApplication->GetMainLayout());
      this->progressBar->SetProgress(0);
      this->skylanderText->SetText("Press x to Scan a Skylander");
    }
  });
}

// Indefinitely wait for an event to be signaled
// Break when + is pressed, or if the application should quit (in this case, return value will be
// non-zero)
Result SkylanderLayout::EventWaitLoop(Event* event)
{
  Result rc = 1;
  while (appletMainLoop())
  {
    rc = eventWait(event, 0);
    padUpdate(&pad);
    if (R_SUCCEEDED(rc) || (padGetButtonsDown(&pad) & HidNpadButton_Plus))
      break;
  }
  return rc;
}

// Print raw data as hexadecimal numbers.
std::string SkylanderLayout::PrintHex(void* buf, size_t size)
{
  std::stringstream ss;
  for (size_t i = 0; i < size; i++)
  {
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(((u8*)buf)[i]);
  }
  return ss.str();
}

u16 SkylanderLayout::Swap16(u16 data)
{
  return (data >> 8) | (data << 8);
}

u32 SkylanderLayout::Swap32(u32 data)
{
  return (Swap16(data) << 16) | Swap16(data >> 16);
}

u64 SkylanderLayout::Swap64(u64 data)
{
  return ((u64)Swap32(data) << 32) | Swap32(data >> 32);
}

// CRC-64 algorithm that is limited to 48 bits every iteration
u64 SkylanderLayout::ComputeCRC48(u8 data[5])
{
  const u64 polynomial = 0x42f0e1eba9ea3693;
  const u64 initial_register_value = 2ULL * 2ULL * 3ULL * 1103ULL * 12868356821ULL;

  const u64 msb = 0x800000000000;

  u64 crc = initial_register_value;
  for (size_t i = 0; i < 5; ++i)
  {
    crc ^= (((u64)data[i]) << 40);
    for (size_t j = 0; j < 8; ++j)
    {
      if (crc & msb)
      {
        crc = (crc << 1) ^ polynomial;
      }
      else
      {
        crc <<= 1;
      }
    }
  }
  return crc & 0x0000FFFFFFFFFFFF;
}

u64 SkylanderLayout::CalculateKeyA(u8 sector, u8 nuid[4])
{
  if (sector == 0)
  {
    return 73ULL * 2017ULL * 560381651ULL;
  }

  u8 data[5] = {nuid[0], nuid[1], nuid[2], nuid[3], sector};

  u64 big_endian_crc = ComputeCRC48(data);
  u64 little_endian_crc = Swap64(big_endian_crc) >> 16;

  return little_endian_crc;
}

u8 SkylanderLayout::GetSectorFromBlock(u8 block)
{
  float block_float = block;
  return floor(block_float / 4);
}

NfcMifareReadBlockParameter SkylanderLayout::GenerateMifareParam(u8 block, u8 nuid[4])
{
  NfcMifareReadBlockParameter param;
  param.sector_number = block;
  NfcSectorKey key;
  key.mifare_command = NfcMifareCommand_AuthA;
  key.unknown = 1;
  u64 keyA = CalculateKeyA(GetSectorFromBlock(block), nuid);
  for (u32 j = 0; j < 6; j++)
  {
    u8 byte = (keyA >> (j * 8)) & 0xFF;
    key.sector_key[(5 - j)] = byte;
  }
  param.sector_key = key;
  return param;
}

Result SkylanderLayout::ProcessSkylander()
{
  Result rc = 0;

  // Get the handle of the first controller with NFC capabilities.
  NfcDeviceHandle handle = {0};
  if (R_SUCCEEDED(rc))
  {
    s32 device_count;
    rc = nfcMfListDevices(&device_count, &handle, 1);

    if (R_FAILED(rc))
      return rc;
  }

  if (R_SUCCEEDED(rc))
  {
    u32 npadId;
    rc = nfcMfGetNpadId(&handle, &npadId);

    if (R_FAILED(rc))
      return rc;
  }

  // Get the activation event. This is signaled when a tag is detected.
  Event activate_event = {0};
  if (R_FAILED(nfcMfAttachActivateEvent(&handle, &activate_event)))
  {
    eventClose(&activate_event);

    return rc;
  }

  // Get the deactivation event. This is signaled when a tag is removed.
  Event deactivate_event = {0};
  if (R_FAILED(nfcMfAttachDeactivateEvent(&handle, &deactivate_event)))
  {
    eventClose(&deactivate_event);
    eventClose(&activate_event);

    return rc;
  }

  NfcState state = NfcState_NonInitialized;
  if (R_SUCCEEDED(rc))
  {
    rc = nfcMfGetState(&state);

    if (R_SUCCEEDED(rc) && state == NfcState_NonInitialized)
    {
      this->skylanderText->SetText("Bad NFC State: " + std::to_string(state));
      g_MainApplication->CallForRender();
      rc = -1;
    }
  }

  NfcMifareDeviceState device_state = NfcMifareDeviceState_Initialized;
  if (R_SUCCEEDED(rc))
  {
    rc = nfcMfGetDeviceState(&handle, &device_state);

    if (R_SUCCEEDED(rc) && device_state > NfcMifareDeviceState_TagFound)
    {
      this->skylanderText->SetText("Bad NFC Device State: " + std::to_string(device_state));
      g_MainApplication->CallForRender();
      rc = -1;
    }
  }

  if (R_FAILED(rc))
  {
    eventClose(&deactivate_event);
    eventClose(&activate_event);

    return rc;
  }

  // Start the detection of tags.
  rc = nfcMfStartDetection(&handle);
  if (R_SUCCEEDED(rc))
  {
    this->skylanderText->SetText("Scanning for a tag...");
    g_MainApplication->CallForRender();
  }

  // Wait until a tag is detected.
  // You could also wait until nfcGetDeviceState returns NfcDeviceState_TagFound.
  if (R_SUCCEEDED(rc))
  {
    rc = EventWaitLoop(&activate_event);

    if (R_SUCCEEDED(rc))
    {
      this->skylanderText->SetText(
          "A tag was detected, please do not remove it from the NFC spot.");
          g_MainApplication->CallForRender();
    }
  }

  // Retrieve the tag info data, which contains the protocol, type and uuid.
  NfcTagInfo tag_info = {0};
  if (R_SUCCEEDED(rc))
  {
    rc = nfcMfGetTagInfo(&handle, &tag_info);

    if (R_SUCCEEDED(rc))
    {
      std::stringstream ss;
      ss << "Tag protocol: 0x" << std::hex << static_cast<int>(tag_info.protocol) << ", type: 0x"
         << std::hex << static_cast<int>(tag_info.tag_type);

      this->skylanderText->SetText(ss.str());
      g_MainApplication->CallForRender();
    }
  }

  u8 skylander_data[0x40 * 0x10];
  bool read = true;

  if (R_SUCCEEDED(rc) && tag_info.tag_type == NfcTagType_Mifare)
  {
    const u8 num_blocks = 4;
    u8 nuid[4] = {tag_info.uid.uid[0], tag_info.uid.uid[1], tag_info.uid.uid[2],
                  tag_info.uid.uid[3]};
    for (u8 i = 0; i < 16; i++)
    {
      NfcMifareReadBlockParameter params[num_blocks];
      NfcMifareReadBlockData response[num_blocks];
      for (u8 j = 0; j < num_blocks; j++)
      {
        params[j] = GenerateMifareParam((i * 4) + j, nuid);
      }
      rc = nfcMfReadMifare(&handle, response, params, num_blocks);
      if (R_FAILED(rc))
      {
        this->skylanderText->SetText("Error reading sector " + std::to_string(i));
        g_MainApplication->CallForRender();
        read = false;
        break;
      }
      else
      {
        this->progressBar->SetProgress(this->progressBar->GetProgress() + 1);
        g_MainApplication->CallForRender();
        // printf("Sector %u data:\n", i);
        for (u8 j = 0; j < num_blocks; j++)
        {
          //   PrintHex(response[j].data, sizeof(response[j].data));
          memcpy(&skylander_data[i * 0x40 + j * 0x10], response[j].data, sizeof(response[j].data));
        }
      }
    }

    if (read)
    {
      FILE* file = fopen("mifare/skylander_data.bin", "wb");
      if (file)
      {
        fwrite(skylander_data, 1, sizeof(skylander_data), file);
        fclose(file);
        this->skylanderText->SetText("Skylander data written to 'mifare/skylander_data.bin'");
        g_MainApplication->CallForRender();
      }
      else
      {
        this->skylanderText->SetText("Failed to open file for writing.");
        g_MainApplication->CallForRender();
      }
    }
  }

  // Wait until the tag is removed.
  // You could also wait until nfcGetDeviceState returns NfcDeviceState_TagRemoved.
  if (R_SUCCEEDED(rc))
  {
    this->skylanderText->SetText("You can now remove the tag.");
    g_MainApplication->CallForRender();
    EventWaitLoop(&deactivate_event);
  }

  // Stop the detection of tags.
  nfcMfStopDetection(&handle);

  // Cleanup.
  eventClose(&deactivate_event);
  eventClose(&activate_event);

  return rc;
}
