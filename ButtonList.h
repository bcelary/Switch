#ifndef _BUTTON_LIST_H
#define _BUTTON_LIST_H

#include "Button.h"

class ButtonList
{
public:
  ButtonList() : m_head(0) {}

  void add(uint8_t pin, bool activeLow, bool pullUp, uint32_t debounceDelay);
  Button* poll();

  Button* head() const { return m_head; }

private:
  Button* m_head;
};

#endif
