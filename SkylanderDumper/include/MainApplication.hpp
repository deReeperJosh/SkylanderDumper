
#pragma once

// Include Plutonium's main header
#include <pu/Plutonium>

#include <NFCLayout.hpp>
#include <SkylanderLayout.hpp>

// Define your application (can't instantiate base class, so need to make a derived one)
class MainApplication : public pu::ui::Application
{
private:
  // Layout instance
  NFCLayout::Ref mainLayout;
  SkylanderLayout::Ref skylanderLayout;

public:
  using Application::Application;
  PU_SMART_CTOR(MainApplication)

  // We need to define this, and use it to initialize everything
  void OnLoad() override;

  inline NFCLayout::Ref& GetMainLayout() { return this->mainLayout; }
  inline SkylanderLayout::Ref& GetSkylanderLayout() { return this->skylanderLayout; }
};
