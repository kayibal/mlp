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
    double xmid;
    double ymid;
    //TODO: change this to length must be quadratric
    double heigth;
    double width;
    
    point centerOfMass;
    double mass;
    
    Particle* p;
    
    std::array<Node*,4> child;
    short children;
    
public:
    Node();
    Node(double xmidp, double ymidp, double h, double w);
    ~Node();
    void insertParticle(Particle* p);
    bool isInside(point p);
    void setParticle(Particle* particle);
    short getChildCount();
    Node* getChild(int i);
    point* getCenterOfMass();
    double getLength();
    Particle* getParticle();
    double getMass();
    void setMass(double m);
    void setCenterOfMass(double x, double y);
};
#endif /* defined(__ParticleSystem__Node__) */
