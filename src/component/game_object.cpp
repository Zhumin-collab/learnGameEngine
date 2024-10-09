//
// created by yzm on 2024/9/21
//
#define RTTR_DLL

#include "game_object.h"
#include "component.h"
#include "utils/debug.h"

#include <rttr/registration>
#include <assert.h>


Tree GameObject::m_game_objects;

GameObject::GameObject():m_layer(0x01) {

}

GameObject::GameObject(const std::string& name): Tree::Node(), m_layer(0x01){
    set_name(name);

    m_game_objects.root_node()->add_child(this);
}   

GameObject::~GameObject() {

}

Component* GameObject::add_component(std::string component_type_name){
    rttr::type t = rttr::type::get_by_name(component_type_name);
    rttr::variant var = t.create();

    Component* component = var.get_value<Component*>();
    component->set_game_object(this);

    if(m_components.find(component_type_name) == m_components.end()){
        std::vector<Component*> components;
        components.push_back(component);
        m_components[component_type_name] = components;
    }else{
        m_components[component_type_name].push_back(component);
    }
    
    component->Awake();
    return component;
}

std::vector<Component*>& GameObject::get_components(std::string component_type_name){
    return m_components[component_type_name];
}

Component* GameObject::get_component(std::string component_type_name){
    if(m_components.find(component_type_name) == m_components.end()){
        return nullptr;
    }
    if(m_components[component_type_name].size() == 0){
        return nullptr;
    }
    return m_components[component_type_name][0];
}

void GameObject::ForeachComponent(std::function<void(Component* component)> func){
    for(auto it:m_components)
    {
        for(auto &iter:it.second)
        {
            Component* component = iter;
            func(component);
        }
    }
}

bool GameObject::set_parent(GameObject* parent){
    if(parent == nullptr){
        return false;
    }
    parent->add_child(this);
    return true;
}

void GameObject::Foreach(std::function<void(GameObject* game_object)> func){
    m_game_objects.Post(m_game_objects.root_node(),[&func](Tree::Node* node){
        auto n = node;
        GameObject* game_object = dynamic_cast<GameObject*>(n);
        func(game_object);
    });
}

GameObject* GameObject::Find(std::string name)
{
    GameObject* game_object_find = nullptr;

    m_game_objects.Find(m_game_objects.root_node(),[&name](Tree::Node* node){
        GameObject* game_object = dynamic_cast<GameObject*>(node);
        if(game_object->name() == name)
        {
            return true;
        }
        return false;
    },reinterpret_cast<Tree::Node**>(&game_object_find));

    return game_object_find;
}