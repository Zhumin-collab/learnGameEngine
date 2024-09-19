//
// created by yzm on 2024/9/19
//

#include <fstream>
#include "mesh_filter.h"

MeshFilter::MeshFilter()
    : m_mesh(nullptr)
{
    
}

void MeshFilter::loadMesh(std::string mesh_file_path)
{
    std::ifstream in_file(mesh_file_path, std::ios::binary);
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