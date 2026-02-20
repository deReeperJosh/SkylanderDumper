#include <NFCLayout.hpp>

#include <MainApplication.hpp>

extern MainApplication::Ref g_MainApplication;

// Implement all the layout/application functions here

NFCLayout::NFCLayout() : Layout::Layout()
{
  // Create the TextBlock instance with the text we want
  this->helloText = pu::ui::elm::TextBlock::New(300, 300, "Press x to Scan a Skylander");
  this->menu =
      pu::ui::elm::Menu::New(0, 0, pu::ui::render::ScreenWidth, pu::ui::Color(254, 251, 255, 255),
                             pu::ui::Color(111, 190, 232, 255), 100, 3);
  this->skylander_menu_item = pu::ui::elm::MenuItem::New("Dump a Skylander Figure");
  this->skylander_menu_item->AddOnKey(std::bind(&NFCLayout::DumpSkylanderFigure, this));
  this->infinity_menu_item = pu::ui::elm::MenuItem::New("Dump an Infinity Figure");
  this->infinity_menu_item->AddOnKey(std::bind(&NFCLayout::DumpInfinityFigure, this));
  this->dimensions_menu_item = pu::ui::elm::MenuItem::New("Dump a Dimensions Figure");
  this->dimensions_menu_item->AddOnKey(std::bind(&NFCLayout::DumpDimensionsFigure, this));
  this->menu->AddItem(this->skylander_menu_item);
  this->menu->AddItem(this->infinity_menu_item);
  this->menu->AddItem(this->dimensions_menu_item);
  // Add the instance to the layout. IMPORTANT! this MUST be done for them to be used, having them
  // as members is not enough (just a simple way to keep them)
  // this->Add(this->helloText);
  this->Add(this->menu);
}

void NFCLayout::DumpSkylanderFigure()
{
    g_MainApplication->LoadLayout(g_MainApplication->GetSkylanderLayout());
}

void NFCLayout::DumpInfinityFigure()
{
    g_MainApplication->LoadLayout(g_MainApplication->GetInfinityLayout());
}

void NFCLayout::DumpDimensionsFigure()
{
}