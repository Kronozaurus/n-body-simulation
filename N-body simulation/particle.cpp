#include "particle.h"

// ### CONSTRUCTORS, DESTRUCTORS ### //

Particle::Particle() {
    this->initVariable();
}

Particle::~Particle() {

}

// ### PUBLIC FUNCTIONS ### //

void Particle::calculateForce(const Particle& otherParticle) {

    double force = 0;

    double distance_x = otherParticle.x_ - this->x_;
    double distance_y = otherParticle.y_ - this->y_;
    
    // Calculating the distance between two particles using the pythagorean theorem
    // distance should be under the square root, but since we need distance squared to calculate the force of gravity,
    // we can simplify the calculations by just not calculating the square root of the distance and then not squaring it in the denominator
    // when callculating the force
    double distance = distance_x * distance_x + distance_y * distance_y;

    // Calculating the force of graviy
    force = (G * otherParticle.mass * this->mass) / (distance);

    // We're calculating the actual force of gravity between two particles by drawing a right triangle
    // with the known distance and two force components Fx, Fy in the x and y direction
    // since we know the distance x and y, we can calculate the angle between F and Fx
    double angle = atan2(distance_y, distance_x);

    // Then, using that angle, force of gravity F (hypotenuse) and some trigonometry we can calculate 
    // the Fx and Fy total force components to determine our velocity in the x and y direction 
    this->force_x += cos(angle) * force;
    this->force_y += sin(angle) * force;

    // Now, we can calculate the actual velocity of this object in the x and y directons using a = F / m
    this->vel_x += this->force_x / this->mass;
    this->vel_y += this->force_y / this->mass;

}
void Particle::update(const double& STEP) {
    // Updating the current position of the object by the current velocity multiplied by TIMESTEP (for slowing or speeding up the simulation)
    this->x_ += this->vel_x * STEP;
    this->y_ += this->vel_y * STEP;
}
// TODO: rozbicia na kilka cząsteczek przy podobnych masach
void Particle::handleCollision(Particle& otherParticle) {
    // Increase the radius on collision while less than 180, 180 being approximately the maximum radius of POINTS on my machine
    if(radius < 180)
        this->radius++;
    // Add the masses of two colliding objects 
    this->mass += otherParticle.mass;
    // Calculate the momentum after impact
    this->vel_x = (this->force_x + otherParticle.force_x) / (this->mass + otherParticle.mass);
    this->vel_y = (this->force_x + otherParticle.force_x) / (this->mass + otherParticle.mass);
    // this->vel_x = (otherParticle.vel_x * otherParticle.mass + this->vel_x * this->mass) / (this->mass + otherParticle.mass);
    // this->vel_y = (otherParticle.vel_y * otherParticle.mass + this->vel_y * this->mass) / (this->mass + otherParticle.mass);
}

bool Particle::checkCollision(const Particle& otherParticle) const{
    return (
        abs(otherParticle.x_ - this->x_) <= radius / 3  &&
        abs(otherParticle.y_ - this->y_) <= radius / 3 
    );
}

// ### SETTERS ### //

void Particle::resetTotalForce() {
    this->force_x = 0;
    this->force_y = 0;
}

void Particle::setCoordinates(double x, double y) {
    this->x_ = x;
    this->y_ = y;
    id++;
}

void Particle::setMass(double mass) {
    this->mass = mass;
}

void Particle::setVelocity(double vel_x, double vel_y) {
    this->vel_x = vel_x;
    this->vel_y = vel_y;
}
 
void Particle::setRadius(float radius) {
    this->radius = radius;
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
    this->radius = 1;
}

// ### OPERATOR OVERLOADING ### //

bool Particle::operator==(const Particle& toCompare) {
    return (this->id == toCompare.id);
}

bool Particle::operator!=(const Particle& toCompare) {
    return (this->id != toCompare.id);
}

bool Particle::operator>=(const Particle& toCompare) {
    return ((this->mass * this->radius) >= (toCompare.mass * toCompare.radius));
}