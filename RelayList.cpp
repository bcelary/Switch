#include "RelayList.h"

void RelayList::add(uint8_t pin, bool activeLow) {
  if (m_head) {
    // list not empty
    Relay *r = m_head;
    Relay *prev;

    do {
      prev = r;

      if (r->getPin() == pin) {
        // pin is already added
        return;
      }
      r = r->next();
    } while (r);

    // reached last element
    prev->setNext(new Relay(pin, activeLow));
    return;
  }
  else {
    // list empty - 1st element
    m_head = new Relay(pin, activeLow);
    return;
  }
}

void RelayList::set(uint8_t value) {
  if (!m_lock) {
    Relay* r = m_head;
    while(r) {
      r->setState(value);
      r = r->next();
    }
  }
}
