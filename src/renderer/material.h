#ifndef MATERIAL_H
#define MATERIAL_H

#include<string>
#include<vector>
#include<map>

class Shader;
class Texture2D;

class Material
{
public:
    Material();
    ~Material();

    void Parse(std::string material_name);

    void SetUniformMatrix4fv(std::string uniform_name, float* value);
    void SetUniform1i(std::string uniform_name, int value);

    void SetTexture(std::string property, Texture2D* texture);

    Shader* shader() { return m_shader; }

    std::vector<std::pair<std::string, Texture2D*>> textures() { return m_textures; }

private:
    Shader* m_shader;
    std::vector<std::pair<std::string, Texture2D*>> m_textures;
    std::map<std::string, int> m_uniform1i_map;
    std::map<std::string, float*> m_uniformMatrix4fv_map;
};





#endif // MATERIAL_H