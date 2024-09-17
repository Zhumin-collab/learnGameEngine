//
// Created by yzm on 2024/9/16
//

#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include <glm/glm.hpp>

// 顶点数据结构
static const glm::vec3 kPositions[3] = {
    glm::vec3{ -1.0f, -1.0f, 0.0f},
    glm::vec3{  1.0f, -1.0f, 0.0f},
    glm::vec3{  0.0f,  1.0f, 0.0f}
};


static const glm::vec4 kColors[3] = {
    glm::vec4{ 1.0f, 0.0f, 0.0f, 1.f},
    glm::vec4{ 0.0f, 1.0f, 0.0f, 1.f},
    glm::vec4{ 0.0f, 0.0f, 1.0f, 1.f}
};










#endif // VERTEXDATA_H