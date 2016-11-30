#include <inttypes.h>

#ifndef _BUTTON_H
#define _BUTTON_H

class Button
{
public:
  Button(uint8_t pin, bool activeLow,
         bool pullUp, uint32_t debounceDelay);
  virtual ~Button() {};

  /*!
   * \brief Sets the debounce delay time.
   */
  void setDebounceDelay(uint32_t debounce) { m_debounceDelay = debounce; }

  /*!
   * \brief Gets the debounce delay time.
   * \return Debounce delay in ms
   */
  uint32_t getDebounceDelay() const { return m_debounceDelay; }

  /*!
   * \brief Polls this input device for change.
   * \return True if any state change occurred.
   */
  bool poll();

  /*!
   * \brief Determines if the button is currently active.
   * \return True of button is active
   */
  bool isActive() const { return m_active; }

  /*!
   * \brief Returns the time of the last state change.
   * \return Time in ms
   */
  uint32_t lastStateChange() const { return m_lastStateChange; }

  /*!
   * \brief Returns the duration for which the button was last active.
   * \return Duration in ms
   */
  uint32_t lastActiveDuration() const { return m_lastActiveDuration; }

  /*!
   * \brief Gets the pin the button is attached to.
   * \return Pin number
   */
  uint8_t getPin() const { return m_pin; }

  /*!
   * \brief Determines if the pin logic is active low.
   * \return True if active low
   */
  bool isActiveLow() const { return m_activeLow; }

  /*!
   * \brief Determines if the pin is pulled high.
   * \return True if pull up active
   */
  bool isPullUp() const { return m_pullUp; }

  Button* next() const { return m_next; };
  void setNext(Button* next) { m_next = next; }

protected:
  /*!
   * \brief Gets the current physical state of the button.
   * \return True if button state is high
   */
  uint8_t getPhysicalState() const;

private:
  bool m_active; //!< Current active state of the button

  uint32_t m_lastStateChange;    //!< Time of last state change
  uint32_t m_lastActiveDuration; //!< Duration of last active state

  uint32_t m_debounceDelay; //!< Debounce delay time

  uint8_t m_pin;    //!< Pin button is attached to
  bool m_activeLow; //!< If the button logic is active low
  bool m_pullUp;    //!< If the button pin is pulled up

  Button* m_next;
};

#endif
