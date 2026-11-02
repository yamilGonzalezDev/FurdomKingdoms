#include "scenes/scenefactory.hpp"
#include "scenes/menuscene.hpp"
#include "scenes/housescene.hpp"
#include "scenes/testscene.hpp"
#include "utils/cast.hpp"
#include <array>
#include <cassert>
#include <cstddef>

namespace SceneFactory {
    using SceneChangerFunc = std::unique_ptr<Scene>(*)(Facade::Window*);

    template <typename T>
    std::unique_ptr<Scene> make(Facade::Window* w) { return std::make_unique<T>(w); }

    constexpr std::size_t count = static_cast<std::size_t>(PortalID::COUNT);

    constexpr std::array<SceneChangerFunc, count> factories = [] {
        std::array<SceneChangerFunc, count> f{};
        f[to_size_t(PortalID::TO_MENU )] = &make<MenuScene >;
        f[to_size_t(PortalID::TO_HOUSE)] = &make<HouseScene>;
        f[to_size_t(PortalID::TO_TEST )] = &make<TestScene >;
        return f;
    }();

    std::unique_ptr<Scene> createScene(PortalID id, Facade::Window* w) {
        SceneChangerFunc scenefactory = factories[to_size_t(id)];
        assert(scenefactory);
        return scenefactory(w);
    }
}
