#include <inttypes.h>

#ifndef _RELAY_LIST_H
#define _RELAY_LIST_H

#include "Relay.h"

class RelayList
{
public:
  RelayList()
    : m_head(0)
    , m_lock(false)
    {}

  void add(uint8_t pin, bool activeLow);
  void set(uint8_t value);
  Relay* head() { return m_head; }

  void setLock(bool lock) { m_lock = lock; }
  bool isLocked() const { return m_lock; }

private:
  Relay* m_head;
  bool m_lock;
};

#endif
