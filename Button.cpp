#include <Arduino.h>

#include "Button.h"

Button::Button(uint8_t    pin,
               bool       activeLow,
               bool       pullUp,
               uint32_t   debounceDelay)
    : m_active(false)
    , m_lastStateChange(0)
    , m_lastActiveDuration(0)
    , m_debounceDelay(debounceDelay)
    , m_pin(pin)
    , m_activeLow(activeLow)
    , m_pullUp(pullUp)
    , m_next(0)
{
  if (pin) {
    init(pin, pullUp);
  }
}

void Button::init(uint8_t pin, bool pullUp) {
  if (pullUp) pinMode(pin, INPUT_PULLUP);
  else pinMode(pin, INPUT);
}

bool Button::poll() {
  if ((millis() - m_lastStateChange > m_debounceDelay) ||
      (m_lastStateChange == 0))
  {
    bool state = getPhysicalState();

    if (state != m_active)
    {
      if (!state) m_lastActiveDuration = millis() - m_lastStateChange;

      m_lastStateChange = millis();
      m_active          = state;

      return true;
    }
  }

  return false;
}

uint8_t Button::getPhysicalState() const {
  if (m_activeLow)
    return !digitalRead(m_pin);
  else
    return digitalRead(m_pin);
}
