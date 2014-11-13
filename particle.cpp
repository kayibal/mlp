//
//  particle.cpp
//  particleSystem
//
//  Created by Alan Höng on 17/10/14.
//  Copyright (c) 2014 Alan Höng. All rights reserved.
//

#include "particle.h"
using namespace ksh;
double Particle::getFx(){
    return fx;
}
double Particle::getFy(){
    return fy;
}
void Particle::setFx(double xp){
    fx = xp;
}
void Particle::setFy(double yp){
    fy = yp;
}
double Particle::getVx(){
    return vx;
}
double Particle::getVy(){
    return vy;
}
void Particle::setVx(double xp){
    vx = xp;
}
void Particle::setVy(double yp){
    vy = yp;
}
double Particle::getMass(){
    return mass;
}
double Particle::getRadius(){
    return radius;
}
void Particle::setMass(double mp){
    mass = mp;
}
void Particle::setRadius(double rp){
    radius = rp;
}
/*
point* Particle::getPreviousPos(){
    return previousPos[0];
}
void Particle::setPreviousPos(int i, double fxp, double fyp){
    if (i > 0 & i <4){
        previousPos[i] = new point(fxp,fyp);
    } else {
        throw "index out of bounds exception";
    }
}

void Particle::savePosition(double x, double y){
    if(previousPos[3] != NULL) free(previousPos[3]);
    previousPos[3] = previousPos[2];
    previousPos[2] = previousPos[1];
    previousPos[1] = previousPos[0];
    previousPos[0] = new point(x,y);
}
 */
void Particle::updateVelocity(double h){
    vx += fx/mass * h;
    vy += fy/mass * h;
}

void Particle::updatePos(double h){
    x += vx*h;
    y += vy*h;
}

void Particle::addForce(point* p, double pmass, double g){
    if(x != p->getX() | y != p->getY()){
        double scale = -g*(mass*pmass)/(pow(p->distance(*this),2));
        point force = (*this - *p)*scale;
        fx = force.getX();
        fy = force.getY();
    } else {
        throw "singularity exception distance is 0";
    }
}

void Particle::addForce(Particle* p, double g){
    //#warning use pointers fort p here to save time
    if(x != p->getX() | y != p->getY()){
        double scale = -g*(mass*p->getMass())/(pow(p->distance(*this),2));
        point force = (*this - *p)*scale;
        fx = force.getX();
        fy = force.getY();
    }
}

Particle::Particle(double xp, double yp, double fxp, double fyp, double pmass, double pradius):point(xp,yp){
    fx = fxp;
    fy = fyp;
    mass = pmass;
    radius = pradius;
}
Particle::Particle(){
    fx = 0;
    fy = 0;
    mass = -1;
    radius = 0;

}
Particle::~Particle(){

}
void Particle::print(){
    std::cout << "x: " << x << "\n";
    std::cout << "y: " << y << "\n";
    std::cout << "Fx: " << fx << "\n";
    std::cout << "Fy: " << fy << "\n";
}
