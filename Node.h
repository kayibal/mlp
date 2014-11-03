//
//  Node.h
//  ParticleSystem
//
//  Created by Alan Höng on 24/10/14.
//  Copyright (c) 2014 Alan Höng. All rights reserved.
//

#ifndef __ParticleSystem__Node__
#define __ParticleSystem__Node__

#include <iostream>
#include "point.h"
#include "particle.h"
#include <stdio.h>
#include <array>
enum quad {NW,SW,SE,NE};

class Node{
    float xmid;
    float ymid;
    //TODO: change this to length must be quadratric
    float heigth;
    float width;
    
    point centerOfMass;
    float mass;
    
    Particle* p;
    
    std::array<Node*,4> child;
    short children;
    
public:
    Node();
    Node(float xmidp, float ymidp, float h, float w);
    ~Node();
    void insertParticle(Particle* p);
    bool isInside(point p);
    void setParticle(Particle* particle);
    short getChildCount();
    Node* getChild(int i);
    point* getCenterOfMass();
    float getLength();
    Particle* getParticle();
    float getMass();
    void setMass(float m);
    void setCenterOfMass(float x, float y);
};
#endif /* defined(__ParticleSystem__Node__) */
