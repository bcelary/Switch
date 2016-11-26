#include "ButtonList.h"

void ButtonList::add(uint8_t pin, bool activeLow, bool pullUp,
  uint32_t debounceDelay)
{
  if (m_head) {
    // list not empty
    Button *b = m_head;
    Button *prev;

    do {
      prev = b;

      if (b->getPin() == pin) {
        // pin is already added
        return;
      }
      b = b->next();
    } while (b);

    // reached last element
    prev->setNext(new Button(pin, activeLow, pullUp, debounceDelay));
    return;
  }
  else {
    // list empty - 1st element
    m_head = new Button(pin, activeLow, pullUp, debounceDelay);
    return;
  }
}

Button* ButtonList::poll() {
  Button* b = m_head;
  while (b) {
    if (b->poll()) {
      return b;
    }
    b = b->next();
  }
  return 0;
}
