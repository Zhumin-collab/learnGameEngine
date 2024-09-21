#ifndef MESHLIB_MESH_FILTER_H
#define MESHLIB_MESH_FILTER_H

#include <string>
#include <glm/glm.hpp>

#include "component/component.h"

class MeshFilter: public Component
{
public:
    MeshFilter();
    ~MeshFilter();

public:
    struct Vertex {
        glm::vec3 pos;
        glm::vec4 color;
        glm::vec2 uv;
    };

    struct MeshFileHead {
        char type[4]; //文件类型
        unsigned short vertex_num; //顶点数量
        unsigned short vertex_index_num; //顶点索引数量
    };

    struct Mesh {
        unsigned short vertex_num;
        unsigned short vertex_index_num;
        Vertex* vertexs_data;
        unsigned short* vertex_index_data;
    };

    void loadMesh(std::string mesh_file_path);
    Mesh* mesh() { return m_mesh; };
    
private:
    Mesh* m_mesh;
    
};


#endif //MESHLIB_MESH_FILTER_H