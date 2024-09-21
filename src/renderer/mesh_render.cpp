//
// create by yzm on 2024/9/20
//

#define RTTR_DLL
#include <glad/gl.h>
#include <rttr/registration>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "mesh_render.h"
#include "texture2d.h"
#include "shader.h"
#include "material.h"
#include "mesh_filter.h"
#include "component/game_object.h"
#include "component/transform.h"


RTTR_REGISTRATION
{
    rttr::registration::class_<MeshRender>("MeshRender")
        .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}
MeshRender::MeshRender()
{

}

MeshRender::~MeshRender()
{

}

void MeshRender::SetMaterial(Material* material)
{
    m_material = material;
}


void MeshRender::Render()
{
    auto component_transform = game_object()->get_component("Transform");
    auto transform = dynamic_cast<Transform*>(component_transform);
    if(transform == nullptr)
    {
        return;
    }
    glm::mat4 trans = glm::translate(transform->position());
    auto rotation = transform->rotation();
    glm::mat4 rotate = glm::eulerAngleYXZ(transform->rotation().y, transform->rotation().x, transform->rotation().z);
    glm::mat4 scale = glm::scale(transform->scale());
    glm::mat4 model = trans*rotate*scale;
    glm::mat4 mvp = m_projection * m_view * model;


    auto component_mesh_filter = game_object()->get_component("MeshFilter");
    auto mesh_filter = dynamic_cast<MeshFilter*>(component_mesh_filter);
    if(mesh_filter == nullptr)
    {
        return;
    }

    GLuint gl_program_id = m_material->shader()->gl_program_id();
    if(m_vertex_array_object == 0)
    {
        GLint vpos_location = glGetAttribLocation(gl_program_id, "a_pos");
        GLint vcol_location = glGetAttribLocation(gl_program_id, "a_color");
        GLint a_uv_location = glGetAttribLocation(gl_program_id, "a_uv");

        glGenBuffers(1, &m_vertex_buffer_object);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_object);
        glBufferData(GL_ARRAY_BUFFER, mesh_filter->mesh()->vertex_num * sizeof(MeshFilter::Vertex), mesh_filter->mesh()->vertexs_data, GL_STATIC_DRAW);

        glGenBuffers(1, &m_element_buffer_object);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_buffer_object);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_filter->mesh()->vertex_index_num * sizeof(unsigned short), mesh_filter->mesh()->vertex_index_data, GL_STATIC_DRAW);

        glGenVertexArrays(1, &m_vertex_array_object);
        glBindVertexArray(m_vertex_array_object);
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_object);
            glVertexAttribPointer(vpos_location, 3, GL_FLOAT, false, sizeof(MeshFilter::Vertex), 0);
            glVertexAttribPointer(vcol_location, 4, GL_FLOAT, false, sizeof(MeshFilter::Vertex), (void*)(sizeof(float) * 3));
            glVertexAttribPointer(a_uv_location,2,GL_FLOAT,false,sizeof(MeshFilter::Vertex),(void*)(sizeof(float)*(3+4)));

            glEnableVertexAttribArray(vpos_location);
            glEnableVertexAttribArray(vcol_location);
            glEnableVertexAttribArray(a_uv_location);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_buffer_object);          
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    glUseProgram(gl_program_id);
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        glUniformMatrix4fv(glGetUniformLocation(gl_program_id,"u_mvp"), 1, GL_FALSE, &mvp[0][0]);
        
        auto textures = m_material->textures();

        for(int texture_index = 0; texture_index < textures.size(); texture_index++)
        {
            glActiveTexture(GL_TEXTURE0 + texture_index);
            glBindTexture(GL_TEXTURE_2D, textures[texture_index].second->texture_id());
            glUniform1i(glGetUniformLocation(gl_program_id, textures[texture_index].first.c_str()), texture_index);
        }

        glBindVertexArray(m_vertex_array_object);
        {
            glDrawElements(GL_TRIANGLES, mesh_filter->mesh()->vertex_index_num, GL_UNSIGNED_SHORT, 0);
        }
        glBindVertexArray(0);

    }
}