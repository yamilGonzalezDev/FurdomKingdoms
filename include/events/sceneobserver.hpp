#pragma once

#include "events/observer.hpp"
#include "scenes/portalid.hpp"

struct SceneObserver : public Observer {
    virtual ~SceneObserver() = default;
    virtual void sensorNotify(PortalID) = 0;
};

struct SceneSubject : public Subject<SceneObserver> {
    virtual void sensorTrigger( PortalID n_p_id ) {
        for ( const auto& obs : observers ) {
            obs->sensorNotify(n_p_id);
        }
    }
};
