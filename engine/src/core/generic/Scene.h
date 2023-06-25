#pragma once
#include "Engine.h"
#include "utility.h"

#include "utils/UUID.h"

namespace ppr {

    class Entity;

    class Scene {
        friend class Application;
        friend class YAMLSerializer;
    public:

        Scene();
        Scene(const UUID& uuid);
        Scene(const std::string& name);
        Scene(const UUID& uuid, const std::string& name);
        ~Scene();

        void Start();

        void Stop();

        void Render();

        Entity CreateEntity(const std::string& name);
        Entity CreateEntity(const UUID& id, const std::string& name);
        bool DestroyEntity(Entity entity);

        Entity GetEntity(const UUID& id);
        UUID GetUUID() const { return uuid; }
        std::string GetName() const { return name; }

        auto& Registry() { return registry; }
        auto& EntityMap() { return entityMap; }
        
    private:
        UUID uuid;
        std::string name;

        entt::registry registry;
        std::unordered_map<UUID, entt::entity> entityMap;
    };

}