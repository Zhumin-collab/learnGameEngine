#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

class Application
{
public:
    static const std::string& data_path() {return m_data_path;};
    static void set_data_path(const std::string& data_path) {m_data_path = data_path;};

    static void InitOpengl();

    static void Run();

    static void UpdateScreenSize();

    static void Update();

    static void Render();

private:
    static std::string m_data_path;

    static GLFWwindow* m_window;
};







#endif // APPLICATION_H