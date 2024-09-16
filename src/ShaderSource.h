//
// Created by yzm on 2024/9/16
//

#ifndef SHADERSOURCE_H
#define SHADERSOURCE_H

static const char* vertex_shader_source = 
        "#version 110\n"
        "uniform mat4 u_mvp;\n"
        "attribute vec3 a_position;\n"
        "attribute vec4 a_color;\n"
        "varying vec4 v_color;\n"
        "void main() {\n"
        "    gl_Position = u_mvp * vec4(a_position, 1.0);\n"
        "    v_color = a_color;\n"
        "}\n";

static const char* fragment_shader_source =
        "#version 110\n"
        "varying vec4 v_color;\n"
        "void main() {\n"
        "    gl_FragColor = v_color;\n"
        "}\n";












#endif // SHADERSOURCE_H