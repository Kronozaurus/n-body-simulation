#include "simulation.h"

// ### CONSTRUCTORS, DESTRUCTORS ### //

Simulation::Simulation() {

    this->initVariable();

    this->initWindow();

    this->initObjects();

}

Simulation::~Simulation() {

    glfwTerminate();

}

// ### PUBLIC FUNCTIONS ### //

float Simulation::pixelsToVertex(double pixels) {
    return static_cast<float> ((pixels / 400) - 1);
}

void Simulation::pollEvents() {

}

void Simulation::update() {
    for(int i = 0; i < particleAmount; i++) {
        for(int j = 0; j < particleAmount; j++) {
            particles[i].calculateForce(particles[j]);
        }
        particles[i].update();
    }
}

void Simulation::render() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f); 
    //glPointSize(5.0f);

    
    glBegin(GL_POINTS);
    
    for(auto &i : this->particles) {
        glVertex2f(
            pixelsToVertex(i.x_),
            pixelsToVertex(i.y_)
        );
    }
    
    glEnd();

    glfwSwapBuffers(this->window);

    glfwPollEvents();

    update();
}

// ### ACCESSORS ### //
GLFWwindow* Simulation::getWindow() const {
    return this->window;
}


// ### PRIVATE FUNCTIONS ### //

void Simulation::initVariable() {

}

void Simulation::initWindow() {

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(windowSizeX, windowSizeY, "Hello World", NULL, NULL);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
}

void Simulation::initObjects() {
    for(int i = 0; i < particleAmount; i++) {
        this->particle.setCoordinates(
            static_cast<double>(rand() % windowSizeX),
            static_cast<double>(rand() % windowSizeY)
        );
        particles.emplace_back(particle);
    }
}
