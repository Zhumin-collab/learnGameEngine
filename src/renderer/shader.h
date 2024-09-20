#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <unordered_map>
class Shader
{
public:
    Shader();
    ~Shader();
public:
    void Parse(std::string shader_name);
    void CreateGPUProgram(const char* vertex_shader_text, const char* fragment_shader_text);

    void Active();
    void InActive();

    unsigned int gl_program_id() { return m_gl_program_id; }

    static Shader* Find(std::string shader_name);
private:
    std::string m_shader_name;
    unsigned int m_gl_program_id;

    static std::unordered_map<std::string, Shader*> m_shader_map;

};






#endif // SHADER_H