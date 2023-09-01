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
        
        // Method for calculating the force of gravity between two Particle objects
        void calculateForce(const Particle&);
        // Method for updating the current coordinates according to the forces of gravity
        void update(const double&);
        
        // Method handling collision between two particles, updating their velocities, masses and radiuses after impact
        void handleCollision(Particle&);
        // Method for checking if a collision occured between two particles, returns true if.. true
        bool checkCollision(const Particle&) const;

    // ### SETTERS ### //

        void setCoordinates(double, double);
        void setMass(double);
        void setVelocity(double, double);

    // ### OPERATOR OVERLOADING, FRIEND CLASSES ### //

        friend class Simulation;
        // Compares two particles by ID
        bool operator== (const Particle&);
        // Compares two particles by ID
        bool operator!= (const Particle&);
        // Compares two particles by masses
        bool operator>= (const Particle&);

    private:

    // ### VARIABLES ### //

        // ID used to distinguish particles from each other
        int id;
        double x_, y_;
        double vel_x, vel_y;
        double force_x, force_y;
        double mass;
        double radius;
        
    // ### PRIVATE FUNCTIONS ### //

        void initVariable();

};