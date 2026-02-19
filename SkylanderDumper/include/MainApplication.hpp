
#pragma once

// Include Plutonium's main header
#include <pu/Plutonium>

// Define your main layout as a class inheriting from pu::Layout
class CustomLayout : public pu::ui::Layout
{
private:
  // An easy way to keep objects is to have them as private members
  // Using ::Ref (of a Plutonium built-in object or any class having PU_SMART_CTOR) is an alias to a
  // shared_ptr of the instance.
  pu::ui::elm::TextBlock::Ref helloText;

public:
  CustomLayout();

  // Have ::Ref alias and ::New() static constructor
  PU_SMART_CTOR(CustomLayout)
};

class NFCLayout : public pu::ui::Layout
{
private:
  pu::ui::elm::Menu::Ref options_menu;
  pu::ui::elm::MenuItem::Ref explore_menu_item;
  pu::ui::elm::MenuItem::Ref app_list_menu_item;
  pu::ui::elm::MenuItem::Ref tickets_menu_item;
  pu::ui::elm::MenuItem::Ref web_browser_menu_item;
  pu::ui::elm::MenuItem::Ref account_menu_item;
  pu::ui::elm::MenuItem::Ref amiibo_menu_item;
  pu::ui::elm::MenuItem::Ref settings_menu_item;
  pu::ui::elm::MenuItem::Ref about_menu_item;

public:
  NFCLayout();

  PU_SMART_CTOR(NFCLayout)
};

// Define your application (can't instantiate base class, so need to make a derived one)
class MainApplication : public pu::ui::Application
{
private:
  // Layout instance
  NFCLayout::Ref layout;

public:
  using Application::Application;
  PU_SMART_CTOR(MainApplication)

  // We need to define this, and use it to initialize everything
  void OnLoad() override;
};
