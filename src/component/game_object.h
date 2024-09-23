#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <list>
#include <functional>

class Component;
class GameObject {
public:
    GameObject();
    GameObject(const std::string& name);
    ~GameObject();

    std::string& name() {return m_name;}

    void set_name(const std::string& name) {m_name = name;}

    Component* add_component(std::string m_component_type_name);

    Component* get_component(std::string component_type_name);

    std::vector<Component*>& get_components(std::string component_type_name);
    
    unsigned char layer() {return m_layer;}
    void set_layer(unsigned char layer) {m_layer = layer;}

    /// @brief 遍历所有组件
    /// @param func 需要执行的函数

    void ForeachComponent(std::function<void(Component* component)> func);

    /// @brief 遍历所有camera组件
    /// @param func 需要执行的函数
    static void Foreach(std::function<void(GameObject* game_object)> func);
private:
    std::string m_name;
    std::unordered_map<std::string, std::vector<Component*>> m_components;
    unsigned char m_layer;

    static std::list<GameObject*> m_game_objects;

};



#endif // GAME_OBJECT_H