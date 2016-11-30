#include <Arduino.h>

#include "SwitchList.h"
#include "SwitchCallbackFunctionHandler.h"

SwitchList sls;

void cb(Switch *s, Button *b) {
  if (!b->isActive() && b->lastActiveDuration()) {
    // toggle relays attached to this switch
    s->toggle();

    // info message
    Serial.print(F("Switch ID  ["));
    Serial.print(s->getId());
    Serial.print(F("]  ==  state ["));
    Serial.print(s->getState());
    Serial.print(F("]  ||  trg. button ["));
    Serial.print(b->getPin());
    Serial.print(F("]  "));

    Relay *r = s->getRls()->head();
    if (r) {
      Serial.print(F("||  toggled relays"));
      while (r) {
        Serial.print(F(" ["));
        Serial.print(r->getPin());
        Serial.print(F("]"));
        r = r->next();
      }
    }
    else {
      Serial.print(F("||  [NONE ATTACHED]"));
    }
    Serial.println();
  }
}

// same callback for all switches
SwitchCallbackFunctionHandler h(cb);

void setup() {
  Serial.begin(115200);
  delay(100);

  // Below is a way to configure the switches.

  Serial.println("INIT");
  // No check is being performed whether buttons or relays are used in more
  // than 1 switch. It should still work but the memory will be allocated
  // multiple times.

  // Start adding switches. Each line add another switch which is populated
  // with buttons (b) and relays (r). In order to do anything when the change
  // happens a callback (cb) needs to be added. It could be the function:
  // void cb(Switch *s, Button *b), cb in that case or an address to a
  // SwitchCallbackFunctionHandler class as shown below. The later is more
  // efficient as it won't create duplicate handler class objects.

  // You can adjust some relays or buttons as you go by adding optional values:
  //
  // b(pin, activeLow, pullUp, debounceDelay)
  // r(pin, activeLow)
  //
  // The defaults need to be changed in the source code of the lib for now.

  sls.add("Switch 1").b(26).r(46).cb(&h);
  sls.add("Switch 2").b(27).r(47).cb(&h);
  sls.add("Switch 3").b(28).b(29).r(48).cb(&h);
  sls.add("Switch 4").b(30).r(47).r(49).cb(&h);
  sls.add("Switch 5").b(31).b(32).r(50).r(51).cb(&h);
  sls.add("Switch 6").b(33).cb(&h);
  sls.add("Switch 7").b(40).cb(&h);

  Serial.println("INIT (DONE)");
}

void loop() {
  sls.poll();
}
