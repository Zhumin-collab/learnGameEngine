// Created by yzm on 2024/9/16

#define GLFW_INCLUDE_NONE
#define RTTR_DLL
#include "component/game_object.h"
#include "utils/application.h"

int main(void)
{
    Application::set_data_path("E:/learnGameEngine/data/");
    Application::InitOpengl();

    GameObject* go = new GameObject("LoginScene");
    go->add_component("Transform");
    go->add_component("LoginScene");

    Application::Run();
}