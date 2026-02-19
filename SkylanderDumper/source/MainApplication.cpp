#include <MainApplication.hpp>

extern MainApplication::Ref g_MainApplication;

void MainApplication::OnLoad()
{
  // Create the layout (calling the smart constructor above)
  this->mainLayout = NFCLayout::New();
  this->skylanderLayout = SkylanderLayout::New();

  // Load the layout. In applications layouts are loaded, not added into a container (you don't
  // select an added layout, just load it from this function) Simply explained: loading layout = the
  // application will render that layout in the very next frame
  this->LoadLayout(this->mainLayout);

  // Set a function when input is caught. This input handling will be the first one to be handled
  // (before Layout or any Elements) Using a lambda function here to simplify things You can use
  // member functions via std::bind() C++ wrapper
  this->SetOnInput([&](const u64 keys_down, const u64 keys_up, const u64 keys_held,
                       const pu::ui::TouchPoint touch_pos) {
    // If + is pressed, exit application
    if (keys_down & HidNpadButton_Plus)
    {
      this->Close();
    }
  });
}
