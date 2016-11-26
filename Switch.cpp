#include "Switch.h"

class Button;

uint8_t Switch::ID = 1;

/*!
 * \brief Sets the callback class for this manager.
 * \param callback Pointer to the callback handler
 * \return True if the callback was set
 */
bool Switch::cb(SwitchCallbackFunctionHandler *callback)
{
  if (callback == NULL)
    return false;

  m_callback = callback;
  return true;
}

/*!
 * \brief Sets the callback function for this manager.
 * \param callback Pointer to the callback function
 * \return True if the callback was set
 */
bool Switch::cb(
  SwitchCallbackFunctionHandler::SwitchCallbackFunction callback)
{
  if (callback == NULL)
    return false;

  m_callback = new SwitchCallbackFunctionHandler(callback);
  return true;
}

void Switch::callback(Button* b) {
  if (m_callback) m_callback->handleSwitchEvent(this, b);
}

// Add new button to this switch
Switch& Switch::b(uint8_t pin, bool activeLow, bool pullUp,
  uint32_t debounceDelay)
{
  if (m_bls) {
    m_bls->add(pin, activeLow, pullUp, debounceDelay);
  }

  return *this;
}

// Add new relay to this switch
Switch& Switch::r(uint8_t pin, bool activeLow) {
  if (m_rls) {
    m_rls->add(pin, activeLow);
  }

  return *this;
}

uint8_t Switch::toggle() {
  changeState(!m_state);
  return m_state;
}

void Switch::changeState(uint8_t state) {
  m_state = state;
  m_rls->set(state);
}
