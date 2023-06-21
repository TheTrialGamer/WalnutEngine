#pragma once
#include "Engine.h"
#include "utility.h"

#include "Scene.h"

namespace engine {

    class Component;
    class RenderComponent;
    class Layer;
    class Scene;

    class Entity {
    public:
        Entity() = default;
        Entity(std::string name, Scene* scene);
        Entity(const UUID& id, std::string name, Scene* scene);

        ~Entity();

        template<typename T>
        T& GetComponent();

    	template<typename T>
        bool HasComponent() const;

    	template<typename T, typename... ARGS>
        T& AddComponent(ARGS&... args);

    	template<typename T>
        bool RemoveComponent();

        operator bool() const { return entity != entt::null; }
        operator entt::entity() const { return entity; }
        operator uint32_t() const { return (uint32_t)entity; }

        Entity* AddTag(std::string tag);
        Entity* AddTag(std::initializer_list<std::string> tags);
        bool RemoveTag(std::string tag);
        bool HasTag(std::string tag);

    	UUID& GetUUID();

        std::string GetName();
        void SetName(const std::string& name);

    private:
        Scene* scene = nullptr;

        entt::entity entity = entt::null;
    };

    template <typename T>
    T& Entity::GetComponent()
    {
        CORE_ASSERT(HasComponent<T>(), "Entity does not have this Component");
        return scene->Registry().get<T>(entity);
    }

    template <typename T>
    bool Entity::HasComponent() const
    {
        return scene->Registry().all_of<T>(entity);
    }

    template <typename T, typename ... ARGS>
    T& Entity::AddComponent(ARGS&... args)
    {
        CORE_ASSERT(!HasComponent<T>(), "Entity already has this Component");
        return scene->Registry().emplace<T>(entity, std::forward<ARGS>(args)...);
    }

    template <typename T>
    bool Entity::RemoveComponent()
    {
        CORE_ASSERT(HasComponent<T>(), "Entity does not have this Component");
        return scene->Registry().remove<T>(entity);
    }
}
