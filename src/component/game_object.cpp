//
// created by yzm on 2024/9/21
//
#define RTTR_DLL

#include "game_object.h"
#include "component.h"

#include <rttr/registration>

GameObject::GameObject() {

}

GameObject::GameObject(const std::string& name):m_layer(0x01){
    set_name(name);
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