//
// create by yzm on 2024/9/20
//

#include <glad//gl.h>

#include "mesh_render.h"
#include "mesh_filter.h"
#include "texture2d.h"
#include "shader.h"
#include "material.h"

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

void MeshRender::SetMeshFilter(MeshFilter* mesh_filter)
{
    m_mesh_filter = mesh_filter;
}

void MeshRender::SetMVP(glm::mat4 mvp)
{
    m_mvp = mvp;
}

void MeshRender::Render()
{
    GLuint gl_program_id = m_material->shader()->gl_program_id();
    if(m_vertex_array_object == 0)
    {
        GLint vpos_location = glGetAttribLocation(gl_program_id, "a_pos");
        GLint vcol_location = glGetAttribLocation(gl_program_id, "a_color");
        GLint a_uv_location = glGetAttribLocation(gl_program_id, "a_uv");

        glGenBuffers(1, &m_vertex_buffer_object);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_object);
        glBufferData(GL_ARRAY_BUFFER, m_mesh_filter->mesh()->vertex_num * sizeof(MeshFilter::Vertex), m_mesh_filter->mesh()->vertexs_data, GL_STATIC_DRAW);

        glGenBuffers(1, &m_element_buffer_object);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_buffer_object);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_mesh_filter->mesh()->vertex_index_num * sizeof(unsigned short), m_mesh_filter->mesh()->vertex_index_data, GL_STATIC_DRAW);

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

        glUniformMatrix4fv(glGetUniformLocation(gl_program_id,"u_mvp"), 1, GL_FALSE, &m_mvp[0][0]);
        
        auto textures = m_material->textures();

        for(int texture_index = 0; texture_index < textures.size(); texture_index++)
        {
            glActiveTexture(GL_TEXTURE0 + texture_index);
            glBindTexture(GL_TEXTURE_2D, textures[texture_index].second->texture_id());
            glUniform1i(glGetUniformLocation(gl_program_id, textures[texture_index].first.c_str()), texture_index);
        }

        glBindVertexArray(m_vertex_array_object);
        {
            glDrawElements(GL_TRIANGLES, m_mesh_filter->mesh()->vertex_index_num, GL_UNSIGNED_SHORT, 0);
        }
        glBindVertexArray(0);

    }
}