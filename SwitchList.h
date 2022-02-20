#include <Arduino.h>

#ifndef _SWITCH_LIST_H
#define _SWITCH_LIST_H

#include "Switch.h"

class SwitchList {
public:
  SwitchList() : m_head(0) {}

  Switch& add(const char* name="", const bool isLight=true);
  Switch* head() const { return m_head; }
  Switch* find(uint8_t id);
  uint8_t poll();

private:
    Switch *m_head;
};

#endif
