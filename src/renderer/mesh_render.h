#ifndef MESH_RENDER_H
#define MESH_RENDER_H

#include <glm/glm.hpp>

class MeshFilter;
class Material;
class Texture2D;
class MeshRender
{
public:
    MeshRender();
    ~MeshRender();

    void SetMaterial(Material* material);
    Material* material() { return m_material; }

    void SetMeshFilter(MeshFilter* mesh_filter);
    MeshFilter* mesh_filter() { return m_mesh_filter; }

    void SetMVP(glm::mat4 mvp);

    void Render();

private:
    MeshFilter* m_mesh_filter;
    Material* m_material;

    glm::mat4 m_mvp;

    unsigned int m_vertex_buffer_object = 0;
    unsigned int m_element_buffer_object = 0;
    unsigned int m_vertex_array_object = 0;
};


#endif // MESH_RENDER_H