#include <Arduino.h>

// TODO Add your MySensor Configuration
#include <MySensors.h>

#include "SwitchList.h"
#include "SwitchCallbackFunctionHandler.h"

SwitchList sls;

bool initial_state_sent = false;

void presentation()  {
  sendSketchInfo("Test Node (N) ", "0.1");

  Switch *s = sls.head();
  while(s) {
    present(s->getId(), S_BINARY, s->getName());
    s = s->next();
  }
}

void cb(Switch *s, Button *b) {
  if (!b->isActive() && b->lastActiveDuration()) {
    bool newState = s->toggle();
    MyMessage gwUpdateMsg(s->getId(), V_STATUS);
    gwUpdateMsg.setType(C_REQ);
    send(gwUpdateMsg.set(newState));
  }
}

// same callback for all switches
SwitchCallbackFunctionHandler h(cb);

void setup() {
  sls.add("optional").b(26).r(46).cb(&h);
  sls.add("name").b(27).r(47).cb(&h);
  sls.add("used").b(28).b(29).r(48).cb(&h);
  sls.add("by").b(30).r(47).r(49).cb(&h);
  sls.add("mysensors").b(31).b(32).r(50).r(51).cb(&h);
  sls.add("presentation").b(33).cb(&h);
  sls.add().b(40).cb(&h);
}

void loop() {
  if (initial_state_sent) {
    sls.poll();
  }
  else {
    // first run

    Switch *s = sls.head();
    while(s) {
      request(s->getId(), V_STATUS);
      wait(MY_CFG_STATUS_REQ_TO, C_SET, V_STATUS);

      MyMessage msg(s->getId(), V_STATUS);
      send(msg.set(s->getState()));

      s = s->next();
    }

    initial_state_sent = true;
  }
}

void receive(const MyMessage& message) {
  switch (message.getCommand()) {
  case C_SET:

    if (message.type == V_STATUS) {
      Switch *s = sls.find(message.sensor);
      if (!s) break;

      s->changeState(message.getBool());

      MyMessage response(message.sensor, V_STATUS);
      response.setDestination(message.sender);
      send(response.set(s->getState()));
    }
    break;

  case C_REQ:

    if (message.type == V_STATUS) {
      Switch *s = sls.find(message.sensor);
      if (!s) break;

      MyMessage response(message.sensor, V_STATUS);
      response.setDestination(message.sender);
      send(response.set(s->getState()));
    }
    break;

  default:
    break;
  }
}
