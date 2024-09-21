#ifndef MESH_RENDER_H
#define MESH_RENDER_H

#include <glm/glm.hpp>

#include "component/component.h"

class MeshFilter;
class Material;
class Texture2D;
class MeshRender: public Component
{
public:
    MeshRender();
    ~MeshRender();

    void SetMaterial(Material* material);
    Material* material() { return m_material; }

    void SetView(glm::mat4 view) { m_view = view; }
    void SetProjection(glm::mat4 projection) { m_projection = projection; }

    void Render();

private:
    Material* m_material;

    glm::mat4 m_view;
    glm::mat4 m_projection;

    unsigned int m_vertex_buffer_object = 0;
    unsigned int m_element_buffer_object = 0;
    unsigned int m_vertex_array_object = 0;
};


#endif // MESH_RENDER_H