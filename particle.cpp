//
//  particle.cpp
//  particleSystem
//
//  Created by Alan Höng on 17/10/14.
//  Copyright (c) 2014 Alan Höng. All rights reserved.
//

#include "particle.h"

float Particle::getFx(){
    return fx;
}
float Particle::getFy(){
    return fy;
}
void Particle::setFx(float xp){
    fx = xp;
}
void Particle::setFy(float yp){
    fy = yp;
}
float Particle::getVx(){
    return vx;
}
float Particle::getVy(){
    return vy;
}
void Particle::setVx(float xp){
    vx = xp;
}
void Particle::setVy(float yp){
    vy = yp;
}
float Particle::getMass(){
    return mass;
}
float Particle::getRadius(){
    return radius;
}
void Particle::setMass(float mp){
    mass = mp;
}
void Particle::setRadius(float rp){
    radius = rp;
}
point* Particle::getPreviousPos(){
    return previousPos[0];
}
void Particle::setPreviousPos(int i, float fxp, float fyp){
    if (i > 0 & i <4){
        previousPos[i] = new point(fxp,fyp);
    } else {
        throw "index out of bounds exception";
    }
}

float Particle::adamBashForth(float y, float h, float i, float i1, float i2, float i3){
    return y + h/24*(55*i - 59*i1 + 37*i2 -9*i3);
}

float Particle::verletMethod(float h, float x, float x1, float a){
    return 2*x - x1 + a*h*h;
}

void Particle::savePosition(float x, float y){
    if(previousPos[3] != NULL) free(previousPos[3]);
    previousPos[3] = previousPos[2];
    previousPos[2] = previousPos[1];
    previousPos[1] = previousPos[0];
    previousPos[0] = new point(x,y);
}
void Particle::updateVelocity(float h){
    vx += fx/mass * h;
    vy += fy/mass * h;
}

void Particle::updatePos(float h){
    x += vx*h;
    y += vy*h;
}
void Particle::move(float h, int mode){
    float old_x = x;
    float old_y = y;
    if(mode == 1){
        //Not enough data to use adams bashforth use verlet
        #warning adams bashfort not working properly
        if(previousPos[3] == nullptr){
            if(previousPos[0] == nullptr){
                previousPos[0] = new point(x+fx,y+fy);
            }
            x = verletMethod(h, x, previousPos[0]->getX(), fx/mass);
            y = verletMethod(h, y, previousPos[0]->getY(), fy/mass);
        } else {
            x = adamBashForth(x, h, previousPos[0]->getX(), previousPos[1]->getX(), previousPos[2]->getX(), previousPos[3]->getX());
            y = adamBashForth(y, h, previousPos[0]->getY(), previousPos[1]->getY(), previousPos[2]->getY(), previousPos[3]->getY());
        }
        savePosition(old_x, old_y);
    } else {
        //Using verlet method
        if(previousPos[0] == nullptr){
            previousPos[0] = new point(x+fx,y+fy);
        }
        x = verletMethod(h, x, previousPos[0]->getX(), fx/mass);
        y = verletMethod(h, y, previousPos[0]->getY(), fy/mass);
        free(previousPos[0]);
        previousPos[0] =  new point(old_x,old_y);
    }
}

void Particle::addForce(point* p, float pmass, float g){
    if(x != p->getX() | y != p->getY()){
        float scale = -g*(mass*pmass)/pow(p->distance(*this),2);
        point force = (*this - *p)*scale;
        fx = force.getX();
        fy = force.getY();
    } else {
        throw "singularity exception distance is 0";
    }
}

void Particle::addForce(Particle* p, float g){
    //#warning use pointers fort p here to save time
    if(x != p->getX() | y != p->getY()){
        float scale = -g*(mass*p->getMass())/pow(p->distance(*this),2);
        point force = (*this - *p)*scale;
        fx = force.getX();
        fy = force.getY();
    }
}

Particle::Particle(float xp, float yp, float fxp, float fyp, float pmass, float pradius):point(xp,yp){
    fx = fxp;
    fy = fyp;
    mass = pmass;
    radius = pradius;
    for (int i = 0; i < 4; i++){
        previousPos[i] = nullptr;
    }
}
Particle::Particle(){
    fx = 0;
    fy = 0;
    mass = -1;
    radius = 0;
    for (int i = 0; i < 4; i++){
        previousPos[i] = nullptr;
    }
}
Particle::~Particle(){
    for (int i = 0; i < 4; i++){
        if(previousPos[i] != nullptr){
            delete previousPos[i];
        }
        previousPos.~array();
    }
}
void Particle::print(){
    std::cout << "x: " << x << "\n";
    std::cout << "y: " << y << "\n";
    std::cout << "Fx: " << fx << "\n";
    std::cout << "Fy: " << fy << "\n";
}
