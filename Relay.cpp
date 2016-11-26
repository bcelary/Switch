#include <Arduino.h>

#include "Relay.h"

Relay::Relay(uint8_t pin, bool activeLow)
  : m_lastStateChange(0)
  , m_lastActiveDuration(0)
  , m_pin(pin)
  , m_activeLow(activeLow)
  , m_next(NULL)
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, activeLow);
}

void Relay::setPhysicalState(uint8_t state) {
  if (m_activeLow) {
    digitalWrite(m_pin, !state);
  }
  else {
    digitalWrite(m_pin, state);
  }
}

uint8_t Relay::getPhysicalState() const {
  return digitalRead(m_pin);
}
