#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GUI/GUIHandler.h"

#include "Panels/TestPanel.h"
#include "Panels/LibraryView.h"

int main(void)
{
    GLFWwindow* window;
    GuiLayer gui;

    gui.AddPanel<InspectorPanel>();
    //gui.AddPanel<LibraryPanel>();

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // OpenGL context must be current (and loader initialized) before ImGui OpenGL backend init.
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    gui.Init(window);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        gui.Begin();
        gui.RenderPanels();
        gui.End();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    gui.Shutdown();
    glfwTerminate();
    return 0;
}