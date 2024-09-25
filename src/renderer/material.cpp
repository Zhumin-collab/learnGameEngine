#include <iostream>
#include <fstream>
#include <glad/gl.h>
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include <rapidxml_print.hpp>

#include "shader.h"
#include "texture2d.h"
#include "material.h"
#include "../utils/application.h"

Material::Material()
{
    
}

Material::~Material()
{
    
}

void Material::Parse(std::string material_name)
{
    std::string name = Application::data_path() + material_name;
    std::cout << name;
    rapidxml::file<> xmlFile(name.c_str());

    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* material_node = doc.first_node("material");
    if (material_node == nullptr)
    {
        std::cout << "material node is null" << std::endl;
        return;
    }

    rapidxml::xml_attribute<>* material_shader_attribute = material_node->first_attribute("shader");
    if (material_shader_attribute == nullptr)
    {
        std::cout << "material shader attribute is null" << std::endl;
        return;
    }

    m_shader = Shader::Find(material_shader_attribute->value());

    rapidxml::xml_node<>* material_texture_node = material_node->first_node("texture");
    while (material_texture_node != nullptr)
    {
        rapidxml::xml_attribute<>* texture_name_attribute = material_texture_node->first_attribute("name");
        if (texture_name_attribute == nullptr)
        {
            std::cout << "texture name attribute is null" << std::endl;
            return;
        }

        rapidxml::xml_attribute<>* texture_image_attribute = material_texture_node->first_attribute("image");
        if (texture_image_attribute == nullptr)
        {
            std::cout << "texture image attribute is null" << std::endl;
            return;
        }

        std::string shader_peoperty_name = texture_name_attribute->value();
        std::string texture_image_path = Application::data_path() + texture_image_attribute->value();
        Texture2D* texture2d = Texture2D::LoadFromFile(texture_image_path);
        m_textures.push_back(std::make_pair(shader_peoperty_name, texture2d));

        material_texture_node = material_texture_node->next_sibling("texture");

    }
}

void Material::SetUniformMatrix4fv(std::string uniform_name, float* value)
{
    m_uniformMatrix4fv_map[uniform_name] = value;
}

void Material::SetUniform1i(std::string uniform_name, int value)
{
    m_uniform1i_map[uniform_name] = value;
}

void Material::SetTexture(std::string property, Texture2D* texture)
{
    for(auto& pair:m_textures)
    {
        if(pair.first == property)
        {
            delete pair.second;
            pair.second = texture;
            return;
        }
    }
}