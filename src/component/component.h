#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;
class Component
{
public:
    Component();
    virtual ~Component();

    GameObject* game_object() { return m_game_object; }
    void set_game_object(GameObject* game_object) { m_game_object = game_object; }

    virtual void OnEnable();

    virtual void Awake();

    virtual void Update();

    virtual void OnPreRender();

    virtual void OnPostRender();

    virtual void OnDisable();
private:
    GameObject* m_game_object;
};




#endif // COMPONENT_H