#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>

class GLFWwindow;
class Application
{
public:

    static void set_title(std::string title) {m_title = title;}
    static const std::string& data_path() {return m_data_path;}

    static void set_data_path(const std::string& data_path) {m_data_path = data_path;};

    static void Init();

    static void Run();

    static void UpdateScreenSize();

    static void Update();

    static void Render();

private:
    static std::string m_data_path;

    static std::string m_title;

    static GLFWwindow* m_window;
};







#endif // APPLICATION_H