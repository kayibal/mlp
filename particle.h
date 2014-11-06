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
class Particle:public point{
    float fx;
    float fy;
    float vx;
    float vy;
    float mass;
    float radius;
    std::array<point*,4> previousPos;
private:
    float adamBashForth(float y, float h, float i, float i1, float i2, float i3);
    float verletMethod(float h, float x, float x1, float a);
public:
    Particle();
    Particle(float x, float y, float fx, float fy, float mass, float radius);
    ~Particle();
    float getFx();
    float getFy();
    float getVx();
    float getVy();
    void setFx(float xp);
    void setFy(float yp);
    float getMass();
    float getRadius();
    void setMass(float mp);
    void setRadius(float rp);
    point* getPreviousPos();
    void setPreviousPos(int i, float fxp, float fyp);
    void savePosition(float x, float y);
    void move(float h, int mode);
    void addForce(point* position, float mass, float g);
    void addForce(Particle* p, float g);
    void updateVelocity(float h);
    void updatePos(float h);
    void print();
    void setVx(float xp);
    void setVy(float yp);
};


#endif /* defined(__ParticleSystem__particle__) */
