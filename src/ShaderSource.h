//
// Created by yzm on 2024/9/16
//

#ifndef SHADERSOURCE_H
#define SHADERSOURCE_H

static const char* vertex_shader_source = 
        "#version 110\n"

        "uniform mat4 u_mvp;\n"

        "attribute vec3 a_pos;\n"
        "attribute vec4 a_color;\n"
        "attribute vec2 a_uv;\n"
        
        "varying vec2 v_uv;\n"
        "varying vec4 v_color;\n"
        
        "void main() {\n"
        "    gl_Position = u_mvp * vec4(a_pos, 1.0);\n"
        "    v_color = a_color;\n"
        "    v_uv = a_uv;\n"
        "}\n";

static const char* fragment_shader_source =
        "#version 110\n"

        "uniform sampler2D u_diffuse_texture;\n"
        "varying vec2 v_uv;\n"
        "varying vec4 v_color;\n"

        "void main() "
        "{\n"
        "    gl_FragColor = texture2D(u_diffuse_texture,v_uv);\n"
        "}\n";












#endif // SHADERSOURCE_H