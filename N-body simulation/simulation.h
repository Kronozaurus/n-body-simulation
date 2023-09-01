#pragma once

#include <iostream>
#include <vector>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "particle.h"

// ### Simulation class, for handling the window, rendering and updating objects ### //
class Simulation {
    public:

    // ### CONSTRUCTORS, DESTRUCTORS ### //

        Simulation();
        virtual ~Simulation();

    // ### PUBLIC FUNCTIONS ### //
        
        // Method for re-calculating particle positions from coordinates to vertex 
        float pixelsToVertex(double); 

        // Method passed into key_callback, with keyboard input handling
        void onKey(int, int, int, int);

        // Checks if a particle object is out of bonds (out of the current window coordinates)
        bool checkOutOfBounds(Particle&);
        // Method for handling particle object collisions with window border, so that they don't go beyond the visible area
        void handleBorderCollision(Particle&);
        
        // Polling input events without the use of key_callback, for rapid spawning of objects with mouse input
        void pollEvents();
        // Updating the position of objects and collisions before rendering them
        void update();
        // Rendering the objects on screen
        void render();
        

    // ### ACCESSORS ### //

        GLFWwindow* getWindow() const;

    private:

    // ### VARIABLES ### //

        int windowSizeX;
        int windowSizeY;
        // Number of initial particles in the simulation
        int particleAmount;
        // A multiplicator for speeding and slowing up the simulation, might tamper with actual calculations
        double STEP;
        // A flag that when set to true makes objects bounce off window borders, otherwise set to false
        bool windowRestrictionFlag;

        GLFWwindow* window;
        std::vector<Particle> particles;

    // ### OBJECTS ### //

        Particle particle;

    // ### PRIVATE FUNCTIONS ### //

        // Functions used to initialize variables
        void initInstructions();
        void initVariable();
        void initWindow();
        void initObjects();

        // A static function passed to key_callback in the constructor, used to process user inputs without repetition
        // Static - because glfwSetKeyCallback won't accept regular methods, since they have 1 more argument (this)
        static void keyCallback(GLFWwindow*, int, int, int, int);
};