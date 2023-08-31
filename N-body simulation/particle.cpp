#include "particle.h"

// ### CONSTRUCTORS, DESTRUCTORS ### //

Particle::Particle() {
    this->initVariable();
}

Particle::~Particle() {

}

// ### PUBLIC FUNCTIONS ### //

void Particle::calculateForce(Particle& otherParticle) {

    double force = 0;

    double distance_x = otherParticle.x_ - this->x_;
    double distance_y = otherParticle.y_ - this->y_;

    double distance = distance_x * distance_x + distance_y * distance_y;

    force = (G * otherParticle.mass) / distance;

    double angle = atan2(distance_y, distance_x);

    this->vel_x += cos(angle) * force;
    this->vel_y += sin(angle) * force;

}

void Particle::update() {
    this->x_ += this->vel_x;
    this->y_ += this->vel_y;
}
//dodaj rozbicie na kilka nowych
void Particle::handleCollision(Particle& otherParticle) {
    if(radius < 185)
        this->radius++;
    this->mass += otherParticle.mass;
    this->vel_x = (otherParticle.vel_x * otherParticle.mass + this->vel_x * this->mass) / (this->mass * this->mass);
    this->vel_y = (otherParticle.vel_y * otherParticle.mass + this->vel_y * this->mass) / (this->mass * this->mass);
}

bool Particle::checkCollision(const Particle& otherParticle) const{
    return (
        abs(otherParticle.x_ - this->x_) <= radius/2 &&
        abs(otherParticle.y_ - this->y_) <= radius/2
    );
}

// ### SETTERS ### //

void Particle::setCoordinates(double x, double y) {
    this->x_ = x;
    this->y_ = y;
    id++;
}

void Particle::setMass(double mass) {
    this->mass = mass;
}

// ### PRIVATE FUNCTIONS ### //

void Particle::initVariable() {
    this->id = 0;
    this->x_ = 0;
    this->y_ = 0;
    this->force_x = 0;
    this->force_y = 0;
    this->vel_x = 0;
    this->vel_y = 0;
    this->mass = 0;
    this->radius = 5;
}

// ### OPERATOR OVERLOADING ### //

bool Particle::operator==(const Particle& toCompare) {
    return (this->id == toCompare.id);
}

bool Particle::operator!=(const Particle& toCompare) {
    return (this->id != toCompare.id);
}

bool Particle::operator>=(const Particle& toCompare) {
    return (this->mass >= toCompare.mass);
}