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

  // a way to configure the switches.
  // no check is being performed whether buttons or relays are used in more
  // than 1 switch. It should still work but the memory will be allocated
  // multiple times.
  Serial.println("INIT");
  sls.add().b(26).r(46).cb(&h);
  sls.add().b(27).r(47).cb(&h);
  sls.add().b(28).b(29).r(48).cb(&h);
  sls.add().b(30).r(47).r(49).cb(&h);
  sls.add().b(31).b(32).r(50).r(51).cb(&h);
  sls.add().b(33).cb(&h);
  sls.add().b(40).cb(&h);
  Serial.println("INIT (DONE)");
}

void loop() {
  sls.poll();
}
