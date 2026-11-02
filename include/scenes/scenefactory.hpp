#pragma once

#include <memory>
#include "scenes/portalid.hpp"

struct Scene;
namespace Facade { struct Window; }

namespace SceneFactory {
    std::unique_ptr<Scene> createScene(PortalID, Facade::Window*);
}
