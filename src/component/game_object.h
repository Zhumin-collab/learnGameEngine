#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <rttr/registration>

class Component;
class GameObject {
public:
    GameObject();
    GameObject(const std::string& name);
    ~GameObject();

    std::string& name() {return m_name;}

    void set_name(const std::string& name) {m_name = name;}

    Component* add_component(std::string m_component_type_name);

    template<class T>
    T* add_component(){
        T* component = new T();
        rttr::type t = rttr::type::get(*component);
        std::string component_type_name = t.get_name().to_string();
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
    Component* get_component(std::string component_type_name);

    std::vector<Component*>& get_components(std::string component_type_name);
    
    unsigned char layer() {return m_layer;}
    void set_layer(unsigned char layer) {m_layer = layer;}
private:
    std::string m_name;
    std::unordered_map<std::string, std::vector<Component*>> m_components;
    unsigned char m_layer;

};



#endif // GAME_OBJECT_H