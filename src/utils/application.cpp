
#include <memory>
#include "component/game_object.h"
#include "renderer/camera.h"
#include "renderer/mesh_render.h"
#include "control/input.h"
#include "application.h"
#include "screen.h"


std::string Application::m_data_path;
GLFWwindow* Application::m_window;


static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Input::RecordKey(key, action);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    Input::RecordKey(button, action);
    std::cout<<"mouse_button_callback:"<<button<<","<<action<<std::endl;
}

void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{
    Input::set_mousePosition(xpos, ypos);
}

void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Input::set_mouse_scroll(yoffset);
}

void Application::InitOpengl()
{
    std::cout<<"init_opengl"<<std::endl;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(960, 640, "Simple example", NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(m_window);
    gladLoadGL(glfwGetProcAddress);

    glfwSwapInterval(1);

    glfwSetKeyCallback(m_window, key_callback);
    glfwSetMouseButtonCallback(m_window, mouse_button_callback);
    glfwSetScrollCallback(m_window, mouse_scroll_callback);
    glfwSetCursorPosCallback(m_window, mouse_move_callback);

}

void Application::Update()
{
    UpdateScreenSize();

    GameObject::Foreach([](GameObject* game_object){
        game_object->ForeachComponent([](Component* component){
            component->Update();
        });
    });

    Input::Update();
}


void Application::Render()
{
    Camera::Foreach([&](){
        GameObject::Foreach([](GameObject* game_object){
            auto component = game_object->get_component("MeshRender");
            if(component == nullptr)
            {
                return;
            }
            auto mesh_render = dynamic_cast<MeshRender*>(component);
            if(mesh_render == nullptr)
            {
                return;
            }
            mesh_render->Render();
        });
    });
}
void Application::Run()
{
    while(!glfwWindowShouldClose(m_window))
    {

        Update();
        Render();

        glfwSwapBuffers(m_window);

        glfwPollEvents();
    }

    glfwDestroyWindow(m_window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void Application::UpdateScreenSize()
{
    int width, height;
    glfwGetFramebufferSize(m_window, &width, &height);
    glViewport(0, 0, width, height);

    Screen::set_width_height(width, height);
}