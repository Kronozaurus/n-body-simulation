#include "simulation.h"

int main(void){

    //Random init
    srand(static_cast<unsigned>(time(NULL)));

    /* Initialize the GLFW library */
    if (!glfwInit())
        return -1;
    
    // ### Initialize the simulation object ### //
    Simulation mySimulation;
    
    if (!mySimulation.getWindow()) {
        glfwTerminate();
        return -1;
    }
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(mySimulation.getWindow())){

        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0f, 1.0f, 1.0f);
        glEnable(GL_POINT_SMOOTH);
        glEnable(GL_PROGRAM_POINT_SIZE);

        mySimulation.render();
        mySimulation.update();
        mySimulation.pollEvents();

        glfwSwapBuffers(mySimulation.getWindow());

        glfwPollEvents();
    }

    return 0;
}
