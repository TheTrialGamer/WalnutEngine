#include "_Core.h"

#include "generic/GameObject.h"
#include "generic/Component.h"
#include "generic/Transform.h"
#include "utils/DataPool.h"

#include "imgui/ImGuiLayer.h"
#include "utils/Core.h"


namespace core {

	std::unordered_map<core_id, GameObject*> GameObject::IDMap;

	void GameObject::StopComponentIndex(uint32_t index)
	{
        components[index]->OnStop();
	}

	void GameObject::DeleteComponentIndex(uint32_t index)
	{
        delete components[index];
	}

    GameObject::GameObject(std::string name, Transform& transform, ProjectionMode mode)
        : name(name), transform(transform), mode(mode)
    {
        this->zIndex = 0;

        objectID = Core::RequestID();
        IDMap.emplace(objectID, this);
    }


    GameObject::~GameObject()
    {
        deleteComponents();
    }


    bool GameObject::AddComponent(Component* component)
	{
        for (const auto i : components) 
        {
            if (i == component) 
            {
                return false;
            }
        }
        components.push_back(component);
        component->gameObject = this;
        return true;
    }

    void GameObject::Update()
	{
        // update gameObject, in order to display moving changes
        for (auto component : components) {
            component->OnUpdate();
        }
        transform.Update();
    }

    void GameObject::start()
	{
        // start all components
        running = true;
        for (auto component : components) {
            component->OnStart();
        }
    }

    void GameObject::stop()
    {
        running = false;
        for (auto component : components) 
        {
            component->OnStop();
        }
    }

    void GameObject::deleteComponents()
	{
        // delete all components
        for (auto comp : components)
        {
            if (running) 
				comp->OnStop();
            delete comp;
            comp = nullptr;
        }
        components.clear();
    }

    GameObject* GameObject::AddTag(std::string tag)
    {
        std::transform(tag.begin(), tag.end(), tag.begin(), ::toupper);
        if (std::find(tagList.begin(), tagList.end(), tag) != tagList.end())
        {
            LOG_CORE_WARN("Adding a tag to a GameObject which it already has: '" + tag + "'");
            return this;
        }
        tagList.emplace_back(tag);
        return this;
    }

    GameObject* GameObject::AddTag(std::initializer_list<std::string> tags)
    {
        for (std::string tag : tags) {
            std::transform(tag.begin(), tag.end(), tag.begin(), ::toupper);
            AddTag(tag);
        }
        return this;
    }

    bool GameObject::RemoveTag(std::string tag)
    {
        std::transform(tag.begin(), tag.end(), tag.begin(), ::toupper);
        std::vector<std::string>::iterator it = std::find(tagList.begin(), tagList.end(), tag);
        if (it == tagList.end())
        {
            LOG_CORE_WARN("Removing a tag from a GameObject which it doesn't have: '" + tag + "'");
            return false;
        }
        tagList.erase(it);
        return true;
    }

    bool GameObject::HasTag(std::string tag)
    {
        std::transform(tag.begin(), tag.end(), tag.begin(), ::toupper);
        std::vector<std::string>::iterator it = std::find(tagList.begin(), tagList.end(), tag);
        return it != tagList.end();
    }


    void GameObject::event(Event& event)
    {
	    for (auto* component : components)
	    {
            component->OnEvent(event);
	    }
    }


	void GameObject::imgui(float dt) {
		ImGui::Text("Transform:");
		ImGui::SliderFloat(std::string("X:").c_str(), &this->transform.position.x, -10.0f, 10.0f, 0);
		ImGui::SliderFloat(std::string("Y:").c_str(), &this->transform.position.y, -10.0f, 10.0f, 0);
		ImGui::SliderFloat(std::string("Width:").c_str(), &this->transform.scale.x, 0.0f, 10.0f, 0);
		ImGui::SliderFloat(std::string("Height:").c_str(), &this->transform.scale.y, 0.0f, 10.0f, 0);

		for (auto component : components) {
		    component->OnImgui(dt);
		}
    }

    GameObject* GameObject::GetGameObjectByID(core_id id)
    {
        CORE_ASSERT(id > 0, "invalid ID");
        if (IDMap.find(id) != IDMap.end()) {
            return IDMap.at(id);
        }
        CORE_ASSERT(false, "invalid ID");
        return nullptr;
    }

    

}