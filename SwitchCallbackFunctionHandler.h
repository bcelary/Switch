#include <Arduino.h>

#ifndef _SWITCH_CALLBACK_FUNCTION_HANDLER_H
#define _SWITCH_CALLBACK_FUNCTION_HANDLER_H

class Switch;
class Button;

/*!
 * \brief Callback handler for function pointers.
 */
class SwitchCallbackFunctionHandler
{
public:
  /*!
   * \typedef SwitchCallbackFunction
   * \brief Callback function pointer type.
   */
  typedef void (*SwitchCallbackFunction)(Switch *sw, Button *btn);

  /*!
   * \brief Create a new function pointer callback handler.
   * \param func Pointer to the callback function
   */
  SwitchCallbackFunctionHandler(SwitchCallbackFunction func)
      : m_function(func)
  {
  }

  /*!
   * \brief Dispatches the event to the function given in the constructor.
   */
  void handleSwitchEvent(Switch *sw, Button *btn)
  {
    if (m_function)
      m_function(sw, btn);
  }

private:
  SwitchCallbackFunction m_function; //!< The callback function pointer
};

#endif
