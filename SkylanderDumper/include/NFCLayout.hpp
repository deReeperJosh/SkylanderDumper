#pragma once

// Include Plutonium's main header
#include <pu/Plutonium>

// Define your main layout as a class inheriting from pu::Layout
class NFCLayout : public pu::ui::Layout
{
private:
  // An easy way to keep objects is to have them as private members
  // Using ::Ref (of a Plutonium built-in object or any class having PU_SMART_CTOR) is an alias to a
  // shared_ptr of the instance.
  pu::ui::elm::TextBlock::Ref helloText;
  pu::ui::elm::Menu::Ref menu;
  pu::ui::elm::MenuItem::Ref skylander_menu_item;
  pu::ui::elm::MenuItem::Ref infinity_menu_item;
  pu::ui::elm::MenuItem::Ref dimensions_menu_item;

  void DumpSkylanderFigure();
  void DumpInfinityFigure();
  void DumpDimensionsFigure();

public:
  NFCLayout();

  // Have ::Ref alias and ::New() static constructor
  PU_SMART_CTOR(NFCLayout)
};