#include "particle.h"

// ### CONSTRUCTORS, DESTRUCTORS ### //

Particle::Particle() {
    this->initVariable();
}

Particle::~Particle() {

}

// ### PUBLIC FUNCTIONS ### //

void Particle::calculateForce(Particle otherParticle) {

    double force = 0;

    double distance_x = otherParticle.x_ - this->x_;
    double distance_y = otherParticle.y_ - this->y_;

    double distance = distance_x * distance_x + distance_y * distance_y;

    if(distance == 0)
        return;

    force = (G * otherParticle.mass) / distance;

    double angle = atan2(distance_y, distance_x);

    

    this->vel_x += cos(angle) * force;
    this->vel_y += sin(angle) * force;

}

void Particle::update() {
    this->x_ += this->vel_x;
    this->y_ += this->vel_y;
}



void Particle::setCoordinates(double x, double y) {
    this->x_ = x;
    this->y_ = y;
}

// ### PRIVATE FUNCTIONS ### //

void Particle::initVariable() {
    this->x_ = 0;
    this->y_ = 0;
    this->force_x = 0;
    this->force_y = 0;
    this->vel_x = 0;
    this->vel_y = 0;
    this->mass = 100000000000;
}