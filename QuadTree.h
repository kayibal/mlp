//
//  QuadTree.h
//  ParticleSystem
//
//  Created by Alan Höng on 24/10/14.
//  Copyright (c) 2014 Alan Höng. All rights reserved.
//

#ifndef __ParticleSystem__QuadTree__
#define __ParticleSystem__QuadTree__

#include <iostream>
#include "Node.h"
#include <vector>
class QuadTree{
    Node* root;
    int height;
    int size;
    double length;
    double gravitation_constant;
    double theta;
    double dt;
    int calculations;
    std::vector<Particle>* particles;
private:
    void build();
    void insertParticle(Particle* p);
    void updateForces();
    void updateForce(Particle* p, Node* current);
    void updateForce(Particle* p);
    void updateVelocities(double dt);
    void updatePositions(double dt);
    void leapfrog();
    void computeMass(Node* n);
    std::vector<Particle>* getParticles();
    Node* getRoot();
public:
    QuadTree(double l, double g, double t, double timestep);
    ~QuadTree();
    void forward();
    void setParticles(std::vector<Particle>* particles);
    int getCalculations();
    point getCenter();
};
#endif /* defined(__ParticleSystem__QuadTree__) */
