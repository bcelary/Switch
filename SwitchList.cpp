#include "SwitchList.h"

// Append new switch element (new HEAD)
Switch& SwitchList::add(const char* name, bool isLight) {
  Switch *n = new Switch(name, isLight);
  if (m_head) {
    // list not empty
    Switch *s = m_head;
    while (s->next()) {
      s = s->next();
    }

    // reached last element
    s->setNext(n);
    return *n;
  }
  else {
    // list empty - 1st element
    m_head = n;
    return *n;
  }
}

Switch* SwitchList::find(uint8_t id) {
  Switch *s = m_head;

  while (s) {
    if (s->getId() == id) {
      return s;
    }
    s = s->next();
  }

  return NULL;
}

uint8_t SwitchList::poll() {
  uint8_t updatedSwitches = 0;
  Switch* s = m_head;
  while (s) {
    Button* buttonUpdated = s->getBls()->poll();
    if (buttonUpdated) {
      s->callback(buttonUpdated);
      updatedSwitches++;
    }
    s = s->next();
  }

  return updatedSwitches;
}
