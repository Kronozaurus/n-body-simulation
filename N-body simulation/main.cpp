#include "simulation.h"

int main(void){

    //Random init
    srand(static_cast<unsigned>(time(NULL)));

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    Simulation mySimulation;
    
    if (!mySimulation.getWindow()) {
        glfwTerminate();
        return -1;
    }
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(mySimulation.getWindow())){
        
        mySimulation.render();

    }

    return 0;
}
