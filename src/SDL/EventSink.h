//
// Created by jay on 7/7/26.
//

#ifndef JSB_EVENTSINK_H
#define JSB_EVENTSINK_H

/**
 * Defines functionality for discrete events like mouse, keyboard.
 * Events here are taken directly from an event pump.
 */
class EventSink {
public:
    virtual ~EventSink() = default;
    virtual void onEvent(ControlEvent& out) = 0; //This can't use ControlEvent
};

#endif //JSB_EVENTSINK_H
