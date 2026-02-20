#pragma once

// Include Plutonium's main header
#include <pu/Plutonium>

class InfinityLayout : public pu::ui::Layout
{
private:
  // An easy way to keep objects is to have them as private members
  // Using ::Ref (of a Plutonium built-in object or any class having PU_SMART_CTOR) is an alias to a
  // shared_ptr of the instance.
  pu::ui::elm::TextBlock::Ref figureText;
  pu::ui::elm::TextBlock::Ref fileText;
  pu::ui::elm::ProgressBar::Ref progressBar;

  Result ProcessFigure();
  Result EventWaitLoop(Event* event);
  std::vector<u8> CalculateKeyA(u8 nuid[7]);
  NfcMifareReadBlockParameter GenerateMifareParam(u8 block, u8 nuid[7]);

public:
  InfinityLayout();

  // Have ::Ref alias and ::New() static constructor
  PU_SMART_CTOR(InfinityLayout)
};
