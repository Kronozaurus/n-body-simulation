// ### simplified N-body simulator made with OpenGL ### //
// ### Jordan Szymański, Piotr Pankowski ### //

#include "simulation.h"

int main(void){

    // ### Random init ### //
    srand(static_cast<unsigned>(time(NULL)));

    // ### Initializing GLFW library ### //
    if (!glfwInit())
        return -1;
    
    // ### Initialize the simulation object ### //
    Simulation mySimulation;
    
    // ### If the constructor failed to initialize the window, terminate the program ### //
    if (!mySimulation.getWindow()) {
        glfwTerminate();
        return -1;
    }

    // ### Loop until the user closes the window ### //
    while (!glfwWindowShouldClose(mySimulation.getWindow())){

        // ### GL options for vertexes ### //
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0f, 1.0f, 1.0f);
        glEnable(GL_POINT_SMOOTH); //circular points
        glEnable(GL_PROGRAM_POINT_SIZE);

        // ### Rendering the objects and updating their position, then checking for input ### //
        mySimulation.render();
        mySimulation.update();
        mySimulation.pollEvents();

        glfwSwapBuffers(mySimulation.getWindow());

        glfwPollEvents();
    }

    return 0;
}
