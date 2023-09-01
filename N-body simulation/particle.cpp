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

    // Calculating the force of graviy, the formula lacks the mass of this particle object,
    // but it's because it would cancel itself later on in the calculations
    force = (G * otherParticle.mass) / distance;

    // We're calculating the actual force of gravity between two particles by drawing a right triangle
    // with the known distance and two force components Fx, Fy in the x and y direction
    // since we know the distance x and y, we can calculate the angle between F and Fx
    double angle = atan2(distance_y, distance_x);

    // Then, using that angle, force of gravity F (hypotenuse) and some trigonometry we can calculate 
    // the Fx and Fy components of the force to determine our velocity in the x and y direction 
    this->vel_x += cos(angle) * force;
    this->vel_y += sin(angle) * force; // TU RÓWNA SIE? a nie plus równa sie

}
// A = F/m i ta masa sie skróciła SPRÓBUJ DODAĆ MASE DO FORCE I TU TEŻ BO MOŻE ZŁE OBLICZENIA
void Particle::update(const double& STEP) {
    // obejrzyj filmik jeszcze raz i to zobacz
    // tu przed tym velx += total fx / masa * step
    this->x_ += this->vel_x * STEP;
    this->y_ += this->vel_y * STEP;
}
//dodaj rozbicie na kilka nowych
void Particle::handleCollision(Particle& otherParticle) {
    if(radius < 180)
        this->radius++;
    this->mass += otherParticle.mass / 2;
    this->vel_x = (otherParticle.vel_x * otherParticle.mass + this->vel_x * this->mass) / (this->mass + otherParticle.mass);
    this->vel_y = (otherParticle.vel_y * otherParticle.mass + this->vel_y * this->mass) / (this->mass + otherParticle.mass);
}

bool Particle::checkCollision(const Particle& otherParticle) const{
    return (
        abs(otherParticle.x_ - this->x_) <= radius / 4 &&
        abs(otherParticle.y_ - this->y_) <= radius / 4
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

void Particle::setVelocity(double vel_x, double vel_y) {
    this->vel_x = vel_x;
    this->vel_y = vel_y;
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
    return (this->mass >= toCompare.mass);
}