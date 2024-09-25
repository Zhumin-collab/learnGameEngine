//
// created by yzm on 2024/9/19
//
#define RTTR_DLL

#include "mesh_filter.h"

#include <fstream>
#include <rttr/registration>

#include "../utils/application.h"

RTTR_REGISTRATION
{
    rttr::registration::class_<MeshFilter>("MeshFilter")
        .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}

MeshFilter::MeshFilter()
    : m_mesh(nullptr)
{
    
}

void MeshFilter::loadMesh(std::string mesh_file_path)
{
    std::ifstream in_file(Application::data_path()+mesh_file_path, std::ios::binary);
    MeshFileHead head;
    in_file.read((char*)&head, sizeof(MeshFileHead));

    unsigned char* vertex_data = (unsigned char*)malloc(sizeof(Vertex) * head.vertex_num);
    in_file.read((char*)vertex_data, sizeof(Vertex) * head.vertex_num);

    unsigned short* vertex_index_data = (unsigned short*)malloc(sizeof(unsigned short) * head.vertex_index_num);
    in_file.read((char*)vertex_index_data, sizeof(unsigned short) * head.vertex_index_num);
    in_file.close();

    m_mesh = new Mesh();
    m_mesh->vertex_num = head.vertex_num;
    m_mesh->vertex_index_num = head.vertex_index_num;
    m_mesh->vertexs_data = (Vertex*)vertex_data;
    m_mesh->vertex_index_data = vertex_index_data;
}

MeshFilter::~MeshFilter()
{
    delete m_mesh;
    m_mesh = nullptr;
}

void MeshFilter::CreateMesh(std::vector<Vertex> &vertices, std::vector<unsigned short> &vertex_indexs)
{
    m_mesh = new Mesh();
    m_mesh->vertex_num = vertices.size();
    m_mesh->vertex_index_num = vertex_indexs.size();

    unsigned short vertex_data_size = sizeof(Vertex) * vertices.size();
    m_mesh->vertexs_data = static_cast<Vertex*>(malloc(vertex_data_size));
    memcpy(m_mesh->vertexs_data, vertices.data(), vertex_data_size);

    unsigned short vertex_index_data_size = sizeof(Vertex) * vertices.size();
    m_mesh->vertex_index_data = static_cast<unsigned short*>(malloc(vertex_index_data_size));
    memcpy(m_mesh->vertex_index_data, vertex_indexs.data(), vertex_index_data_size);
}