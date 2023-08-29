#pragma once

#include <cmath>
#include <iostream>

double const G = 6.6743 * pow(10, -11);
double const AU = 150 * pow(10, 6) * 1000;

class Particle {
    public:

        // ### CONSTRUCTORS, DESTRUCTORS ### //
        Particle();
        virtual ~Particle();

        // ### PUBLIC FUNCTIONS ### //
        void update();
        void calculateForce(Particle);

        void setCoordinates(double, double);

        friend class Simulation;

    private:
        // ### VARIABLES ### //
        double x_, y_;
        double vel_x, vel_y;
        double force_x, force_y;
        double mass;

        // ### PRIVATE FUNCTIONS ### //
        void initVariable();

};