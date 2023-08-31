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

        void onKey(int, int, int, int);

        bool checkOutOfBounds(Particle&);
        void handleBorderCollision(Particle&);
        
        void pollEvents();
        void update();
        void render();
        

        // ### ACCESSORS ### //
        GLFWwindow* getWindow() const;

    private:
        // ### VARIABLES ### //
        int windowSizeX;
        int windowSizeY;
        int particleAmount;

        bool windowRestrictionFlag;

        GLFWwindow* window;
        std::vector<Particle> particles;

        // ### OBJECTS ### //
        Particle particle;

        // ### PRIVATE FUNCTIONS ### //
        void initInstructions();
        void initVariable();
        void initWindow();
        void initObjects();

        static void keyCallback(GLFWwindow*, int, int, int, int);
};