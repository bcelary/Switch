#include <Arduino.h>

#ifndef _SWITCH_H
#define _SWITCH_H

#include "ButtonList.h"
#include "RelayList.h"
#include "SwitchCallbackFunctionHandler.h"

class Switch {
public:
  Switch(uint8_t state = 0)
      : m_next(0)
      , m_callback(0)
      , m_state(state)
      , m_id(ID++)
      , m_bls(new ButtonList())
      , m_rls(new RelayList())
  {}

  void init(uint8_t state) {
    m_state = state;
  }

  bool cb(SwitchCallbackFunctionHandler *callback);
  bool cb(
    SwitchCallbackFunctionHandler::SwitchCallbackFunction
    callback);
  uint8_t getState() const { return m_state; }
  uint8_t getId() const { return m_id; }
  ButtonList *getBls() const { return m_bls; }
  RelayList *getRls() const { return m_rls; }
  Switch *next() const { return m_next; }

  void setNext(Switch* next) { m_next = next; }

  Switch& b(uint8_t pin, bool activeLow=true, bool pullUp=true,
    uint32_t debounceDelay=50);
  Switch& r(uint8_t pin, bool activeLow=true);

  void callback(Button* b);

  uint8_t toggle();
  void changeState(uint8_t state);
  void setLock(bool lock) { m_rls->setLock(lock); }
  bool isLocked() const { return m_rls->isLocked(); }

private:
  static uint8_t ID;
  Switch *m_next;
  SwitchCallbackFunctionHandler *m_callback;
  uint8_t m_state;
  bool m_lock;
  const uint8_t m_id;
  ButtonList *m_bls;
  RelayList *m_rls;
};

#endif // ifndef __SWITCH_H
