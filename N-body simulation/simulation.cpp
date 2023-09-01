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
    
    // On SPACE - switch border collisions on/off and clear out of bounds particles
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        
        // Set the flag to the opposite value
        this->windowRestrictionFlag = !this->windowRestrictionFlag;  
        printf("Is window border collision turned on? : %d\n", windowRestrictionFlag);

        for(int i = 0; i < particles.size(); i++) {
            // Erase out of bounds particles to avoid clutter
            if(checkOutOfBounds(particles[i])) {
                particles.erase(particles.begin() + i);
            }

        }
        printf("Current number of particles: %d\n", particles.size());

    }
    
    // On ENTER - spawn a new, single particle at random coordinates
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {

        this->particle.setCoordinates(
            static_cast<double>(rand() % windowSizeX),
            static_cast<double>(rand() % windowSizeY)
        );

        this->particle.setMass(
            static_cast<double>(rand() % 100000 + 100000)
        );
        
        // Random velocity for more visually appealing results (so that particles wont just attract each other and collide, but instead start orbiting each other)
        // However, it's bugged and doesn't work as intended yet, hence the comment-out
        // this->particle.setVelocity(
        //     static_cast<double>(rand() % 24 + (-12)),
        //     static_cast<double>(rand() % 24 + (-12))
        // );
        
        particles.emplace_back(particle);
        printf("Added a particle. \n Current number of particles: %d\n", particles.size());
    }

    // On RIGHT ARROW - speeds up the simulation (double each input) 
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS && this->STEP < (3600* 32)) {
        this->STEP *= 2;
        printf("Doubled simulation speed. \n");
    }

    // On LEFT ARROW - slows down the simulation (by two times each input)
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS && this->STEP > (3600 / 32)) {
        this->STEP /= 2;
        printf("Slowed simulation speed. \n");
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
    
    // After collision with window border, just reverse the direction of the particle
    if(toCheck.x_ < 0 || toCheck.x_ > windowSizeX)
        toCheck.vel_x *= -1;

    if(toCheck.y_ < 0 || toCheck.y_ > windowSizeY)
        toCheck.vel_y *= -1;

}

void Simulation::pollEvents() {

    // On LEFT MOUSE BUTTON - spawn new particles with repetition and without any delay, allows to spam new particles
    if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

        double xpos = 0, ypos = 0;
        glfwGetCursorPos(window, &xpos, &ypos);

        // Reversing the y-coordinate, since glVertex and glfwGetCursorPos return coordinates with different (0, 0) coordinates
        // Top left for glfw and down left for glVertex
        ypos = windowSizeY - ypos;

        this->particle.setCoordinates(
            xpos,
            ypos
        );

        this->particle.setMass(
            static_cast<double>(rand() % 100000 + 100000)
        );

        // Random velocity for more visually appealing results (so that particles wont just attract each other and collide, but instead start orbiting each other)
        // However, it's bugged and doesn't work as intended yet, hence the comment-out
        // this->particle.setVelocity(
        //     static_cast<double>(rand() % 2 ),
        //     static_cast<double>(rand() % 2 )
        // );

        particles.emplace_back(particle);
        printf("Added a particle. \n Current number of particles: %d\n", particles.size());       

    }

}

void Simulation::update() {
    
    // Iterating through the particles vector containing all particle objects
    for(int i = 0; i < particles.size(); i++) {
        // Second loop for comparing particles with each other

        // !!!!!!!!!!!!!!!!!!!!
        // DRUGA ITERACJA MOGŁABY DZIAŁAĆ OD INT J = I + 1, +1 NIWELUJE POTRZEBE SPRAWDZANIA CZY TO TA SAMA CZĄSTECZKA W IFIE
        // ALE WTEDY TROCHE INACZEJ DZIAŁA PROGRAM, CHYBA MNIEJ POPRAWNIE 
        // !!!!!!!!!!!!!!!!!!!!

        for(int j = 0; j < particles.size(); j++) {

            // When encountering the same particle, skip the iteration
            if(particles[i] == particles[j]) 
                 continue;

            // If there is no collision detected between two particles, calculate the gravitational force and skip to the next iteration
            if (!particles[i].checkCollision(particles[j])) {

                particles[i].calculateForce(particles[j]);
                continue;
            }
            
            // If a collision has been detected and particle i has bigger mass than particle j (>= operator is overloaded to compare masses)
            // Handle the collision and delete the less massive object
            if (particles[i] >= particles[j]) {

                particles[i].handleCollision(particles[j]);
                particles.erase(particles.begin() + j);
                
                continue;
            } else {
                // If particle j is more massive instead
                particles[j].handleCollision(particles[i]);
                particles.erase(particles.begin() + i);
                
                continue; 
            }
        }
        // Update the positions of particles in the loop
        particles[i].update(STEP);

        // Handling collision with the window border if the flag is set to true, else nothing
        if(windowRestrictionFlag == true)
            handleBorderCollision(particles[i]);
    }
}

void Simulation::render() {
    
    // Iterating through particles vector
    for(auto &i : this->particles) {
        // Each particle has its independent size, based on the amount of collisions (MIGHT MAKE IT MORE ACCURATE LATER)
        glPointSize(i.radius);
        glBegin(GL_POINTS);
        // Draw the point its current coordinates
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
    printf("To turn window border collisions on/off press SPACE - default: OFF \n");
    printf("To spawn more particles, use LEFT MOUSE BUTTON or ENTER\n");
    printf("To speed up the simulation, press RIGHT, to slow down press LEFT\n\n");
}

void Simulation::initVariable() {
    this->windowSizeX = 800;
    this->windowSizeY = 800;
    this->particleAmount = 500;

    // 60 * 60 meaning this current step is one hour of simulation a frame
    this->STEP = 3600;

    // By default, objects won't bounce off the border of the window
    this->windowRestrictionFlag = false;
}

void Simulation::initWindow() {

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(windowSizeX, windowSizeY, "N-body simulation", NULL, NULL);

    /* Set a pointer to the current window to pass to other Simulation objects in order to work on the same window */
    glfwSetWindowUserPointer(window, this);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Setting up key callback to listen for user input without repetition */
    glfwSetKeyCallback(window, keyCallback);
    
}

void Simulation::initObjects() {
    // Initializing a set amount of particles at the start of the simulation
    for(int i = 0; i < particleAmount; i++) {
        this->particle.setCoordinates(
            static_cast<double>(rand() % windowSizeX),
            static_cast<double>(rand() % windowSizeY)
        );
        this->particle.setMass(
            static_cast<double>(rand() % 1000000 + 10000)
        );
        particles.emplace_back(particle);
    }
}

void Simulation::keyCallback(GLFWwindow* window, int key, int scancode, int actions, int mods) {
    // A static method, requiring to create another Simulation object and pass the current window pointer to it
    // Passing the current window to the temporary Simulation object
    Simulation* obj = reinterpret_cast<Simulation* >(glfwGetWindowUserPointer(window));
    // And then when the object is created, handling keyboard input using onKey method from the Simulation class
    if(obj)
        obj->onKey(key, scancode, actions, mods);
}

