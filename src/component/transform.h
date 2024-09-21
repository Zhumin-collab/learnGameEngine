#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

#include "component.h"

class Transform : public Component
{
public:
    Transform();
    ~Transform();

    glm::vec3 position() const { return m_position; }
    glm::vec3 rotation() const { return m_rotation; }
    glm::vec3 scale() const { return m_scale; }

    void set_position(glm::vec3 position) { m_position = position; }
    void set_rotation(glm::vec3 rotation) { m_rotation = rotation; }
    void set_scale(glm::vec3 scale) { m_scale = scale; }
    


private:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
};





#endif // TRANSFORM_H