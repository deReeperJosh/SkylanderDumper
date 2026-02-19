#pragma once

// Include Plutonium's main header
#include <pu/Plutonium>

class SkylanderLayout : public pu::ui::Layout
{
private:
  // An easy way to keep objects is to have them as private members
  // Using ::Ref (of a Plutonium built-in object or any class having PU_SMART_CTOR) is an alias to a
  // shared_ptr of the instance.
  pu::ui::elm::TextBlock::Ref skylanderText;
  pu::ui::elm::TextBlock::Ref fileText;
  pu::ui::elm::ProgressBar::Ref progressBar;

  Result ProcessSkylander();
  Result EventWaitLoop(Event* event);
  std::string PrintHex(void* buf, size_t size);
  u16 Swap16(u16 data);
  u32 Swap32(u32 data);
  u64 Swap64(u64 data);
  u64 ComputeCRC48(u8 data[5]);
  u64 CalculateKeyA(u8 sector, u8 nuid[4]);
  u8 GetSectorFromBlock(u8 block);
  NfcMifareReadBlockParameter GenerateMifareParam(u8 block, u8 nuid[4]);

public:
  SkylanderLayout();

  // Have ::Ref alias and ::New() static constructor
  PU_SMART_CTOR(SkylanderLayout)
};
