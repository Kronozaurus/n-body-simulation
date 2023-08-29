#pragma once

#include <iostream>
#include <vector>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "particle.h"

class Simulation {
    public:
        // ### CONSTRUCTORS, DESTRUCTORS ### //
        Simulation();
        virtual ~Simulation();

        // ### PUBLIC FUNCTIONS ### //
        float pixelsToVertex(double);

        void pollEvents();

        void update();
        void render();
        

        // ### ACCESSORS ### //
        GLFWwindow* getWindow() const;

    private:
        // ### VARIABLES ### //
        int windowSizeX = 800;
        int windowSizeY = 600;
        int particleAmount = 80;
        GLFWwindow* window;
        std::vector<Particle> particles;

        // ### OBJECTS ### //
        Particle particle;

        // ### PRIVATE FUNCTIONS ### //
        void initVariable();
        void initWindow();
        void initObjects();
};