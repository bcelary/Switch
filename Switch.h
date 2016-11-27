#include <Arduino.h>

#ifndef _SWITCH_H
#define _SWITCH_H

#include "ButtonList.h"
#include "RelayList.h"
#include "SwitchCallbackFunctionHandler.h"

#define MAX_NAME_SIZE 16;

class Switch {
public:
  Switch(const char *name="")
      : m_next(0)
      , m_callback(0)
      , m_state(0)
      , m_id(ID++)
      , m_bls(new ButtonList())
      , m_rls(new RelayList())
      , m_name(name)
  {}

  void init(uint8_t state) {
    m_state = state;
  }

  bool cb(SwitchCallbackFunctionHandler *callback);
  bool cb(
    SwitchCallbackFunctionHandler::SwitchCallbackFunction
    callback);
  uint8_t getState() const { return m_state; }
  const char *getName() const { return m_name; }
  uint8_t getId() const { return m_id; }
  ButtonList *getBls() const { return m_bls; }
  RelayList *getRls() const { return m_rls; }
  Switch *next() const { return m_next; }

  void setNext(Switch* next) { m_next = next; }

  // TODO figure out the best way to have these defaults configurable
  Switch& b(uint8_t pin, bool activeLow=false, bool pullUp=true,
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
  const char* m_name;
};

#endif // ifndef __SWITCH_H
