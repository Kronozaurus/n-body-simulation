#pragma once

#include <cmath>
#include <iostream>

// ### GLOBAL CONSTANTS ### //
double const G = 6.6743 * pow(10, -11); 
double const AU = 150 * pow(10, 6) * 1000;

class Particle {
    public:

        // ### CONSTRUCTORS, DESTRUCTORS ### //
        Particle();
        virtual ~Particle();

        // ### PUBLIC FUNCTIONS ### //
        
        void calculateForce(Particle&);
        void update();
        
        void handleCollision(Particle&);
        bool checkCollision(const Particle&) const;

        // ### SETTERS ### //

        void setCoordinates(double, double);
        void setMass(double);

        // ### OPERATOR OVERLOADING, FRIEND CLASSES ### //
        friend class Simulation;
        bool operator== (const Particle&);
        bool operator!= (const Particle&);
        bool operator>= (const Particle&);

    private:
        // ### VARIABLES ### //
        int id;
        double x_, y_;
        double vel_x, vel_y;
        double force_x, force_y;
        double mass;
        double radius;
        // ### PRIVATE FUNCTIONS ### //
        void initVariable();

};