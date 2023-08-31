#include "simulation.h"

// ### CONSTRUCTORS, DESTRUCTORS ### //

Simulation::Simulation() {

    this->initInstructions();

    this->initVariable();

    this->initObjects();

    this->initWindow();

}

Simulation::~Simulation() {

    glfwDestroyWindow(this->window);
    glfwTerminate();

}

// ### PUBLIC FUNCTIONS ### //

float Simulation::pixelsToVertex(double pixels) {
    return static_cast<float> ((pixels / 400) - 1);
}

void Simulation::onKey(int key, int scancode, int action, int mods) {
    
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {

        this->windowRestrictionFlag = !this->windowRestrictionFlag;  
        printf("Is window border collision turned on? : %d\n", windowRestrictionFlag);

        for(int i = 0; i < particles.size(); i++) {

            if(checkOutOfBounds(particles[i])) {
                particles.erase(particles.begin() + i);
            }

        }
        printf("Current number of particles: %d\n", particles.size());

    }
    
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {

        this->particle.setCoordinates(
            static_cast<double>(rand() % windowSizeX),
            static_cast<double>(rand() % windowSizeY)
        );

        this->particle.setMass(
            //static_cast<double>(rand() % 100000 + 100000000)
            1000000000
        );

        particles.emplace_back(particle);
        printf("Added a particle. \n Current number of particles: %d\n", particles.size());
    }
}

bool Simulation::checkOutOfBounds(Particle& toCheck) {
    if (
        (toCheck.x_ < 0 || toCheck.x_ > windowSizeX) ||
        (toCheck.y_ < 0 || toCheck.y_ > windowSizeY)
    ) {
        return true;
    }
    
    return false;
}

void Simulation::handleBorderCollision(Particle& toCheck) {

    if(toCheck.x_ < 0 || toCheck.x_ > windowSizeX)
        toCheck.vel_x *= -1;

    if(toCheck.y_ < 0 || toCheck.y_ > windowSizeY)
        toCheck.vel_y *= -1;

}

void Simulation::pollEvents() {

    if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

        double xpos = 0, ypos = 0;
        glfwGetCursorPos(window, &xpos, &ypos);
        
        printf("x: %f, y: %f \n", xpos, ypos);

        this->particle.setCoordinates(
        xpos,
        ypos
        );

        this->particle.setMass(
            //static_cast<double>(rand() % 100000 + 100000000)
            1000000000
        );

        particles.emplace_back(particle);
        printf("Added a particle. \n Current number of particles: %d\n", particles.size());       

    }

}

void Simulation::update() {

    for(int i = 0; i < particles.size(); i++) {

        for(int j = 0; j < particles.size(); j++) {

            if(particles[i] == particles[j]) 
                continue;

            if (!particles[i].checkCollision(particles[j])) {

                particles[i].calculateForce(particles[j]);
                continue;
            }
                
            if (particles[i] >= particles[j]) {

                particles[i].handleCollision(particles[j]);
                particles.erase(particles.begin() + j);
                
                continue;
            } else {

                particles[j].handleCollision(particles[i]);
                particles.erase(particles.begin() + i);
                
                continue; 
            }
        }

        particles[i].update();

        if(windowRestrictionFlag == true)
            handleBorderCollision(particles[i]);
    }
}

void Simulation::render() {
    
    
    for(auto &i : this->particles) {
        glPointSize(i.radius);
        glBegin(GL_POINTS);
        glVertex2f(
            pixelsToVertex(i.x_),
            pixelsToVertex(i.y_)
        );
        glEnd();
    }
    
    
}

// ### ACCESSORS ### //
GLFWwindow* Simulation::getWindow() const {
    return this->window;
}


// ### PRIVATE FUNCTIONS ### //

void Simulation::initInstructions() {
    printf("To turn window border collisions on/off press SPACE - default: ON \n");
    printf("To spawn more particles, use LEFT MOUSE BUTTON or ENTER\n\n");
}

void Simulation::initVariable() {
    this->windowSizeX = 800;
    this->windowSizeY = 800;
    this->particleAmount = 300;

    this->windowRestrictionFlag = true;
}

void Simulation::initWindow() {

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(windowSizeX, windowSizeY, "N-body simulation", NULL, NULL);

    glfwSetWindowUserPointer(window, this);
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, keyCallback);
    
}

void Simulation::initObjects() {
    for(int i = 0; i < particleAmount; i++) {
        this->particle.setCoordinates(
            static_cast<double>(rand() % windowSizeX),
            static_cast<double>(rand() % windowSizeY)
        );
        this->particle.setMass(
            //static_cast<double>(rand() % 100000 + 100000000)
            1000000000
        );
        particles.emplace_back(particle);
    }
}

void Simulation::keyCallback(GLFWwindow* window, int key, int scancode, int actions, int mods) {
    Simulation* obj = reinterpret_cast<Simulation* >(glfwGetWindowUserPointer(window));
    if(obj)
        obj->onKey(key, scancode, actions, mods);
}

