#pragma once

#include "events/observer.hpp"

struct SensorObserver : public Observer {
    virtual ~SensorObserver() = default;
    virtual void notify() = 0;
};

struct SensorSubject : public Subject<SensorObserver> {
    virtual void trigger() {
        for ( auto& obs : observers ) {
            obs->notify();
        }
    }
};
