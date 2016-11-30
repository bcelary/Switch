#ifndef _RELAY_H
#define _RELAY_H

#include <inttypes.h>

class Relay {
public:
  Relay(uint8_t pin, bool activeLow);
  virtual ~Relay() {};

  /*!
  * \brief Sets a relay state.
  */
  void setState(uint8_t state) { setPhysicalState(state); };

  /*!
  * \brief Determines if the relay is currently active.
  * \return True of button is active
  */
  bool isActive() const { return getPhysicalState(); }

  /*!
   * \brief Returns the time of the last state change.
   * \return Time in ms
   */
  uint32_t lastStateChange() const { return m_lastStateChange; }

  /*!
   * \brief Returns the duration for which the relay was last active.
   * \return Duration in ms
   */
  uint32_t lastActiveDuration() const { return m_lastActiveDuration; }

  /*!
   * \brief Gets the pin the relay is attached to.
   * \return Pin number
   */
  uint8_t getPin() const { return m_pin; }

  /*!
   * \brief Determines if the pin logic is active low.
   * \return True if active low
   */
  bool isActiveLow() const { return m_activeLow; }

  Relay* next() const { return m_next; }
  void setNext(Relay* next) { m_next = next; }

protected:
  /*!
   * \brief Gets the current physical state of the relay.
   * \return True if button state is high
   */
  uint8_t getPhysicalState() const;

  /*!
  * \brief Sets the physical state of the relay.
  */
  void setPhysicalState(uint8_t state);

private:
  uint32_t m_lastStateChange;    //!< Time of last state change
  uint32_t m_lastActiveDuration; //!< Duration of last active state

  uint8_t m_pin; //!< Pin relay is attached to
  bool m_activeLow; //!< If the relay logic is active low
  Relay* m_next;

  static bool defaultActiveLow;
};

#endif
