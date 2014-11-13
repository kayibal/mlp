//
//  particle.h
//  ParticleSystem
//
//  Created by Alan Höng on 17/10/14.
//  Copyright (c) 2014 Alan Höng. All rights reserved.
//

#ifndef __ParticleSystem__particle__
#define __ParticleSystem__particle__

#include <iostream>
#include "point.h"
#include <array>
namespace ksh{
class Particle:public point{
    double fx;
    double fy;
    double vx;
    double vy;
    double mass;
    double radius;
    //std::array<point*,4> previousPos;
public:
    Particle();
    Particle(double x, double y, double fx, double fy, double mass, double radius);
    ~Particle();
    double getFx();
    double getFy();
    double getVx();
    double getVy();
    void setFx(double xp);
    void setFy(double yp);
    double getMass();
    double getRadius();
    void setMass(double mp);
    void setRadius(double rp);
    /*
    point* getPreviousPos();
    void setPreviousPos(int i, double fxp, double fyp);
    void savePosition(double x, double y);
     */
    void addForce(point* position, double mass, double g);
    void addForce(Particle* p, double g);
    void updateVelocity(double h);
    void updatePos(double h);
    void print();
    void setVx(double xp);
    void setVy(double yp);
};
}

#endif /* defined(__ParticleSystem__particle__) */
