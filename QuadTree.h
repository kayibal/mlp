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
    float length;
    float gravitation_constant;
    float theta;
    float dt;
    int calculations;
    std::vector<Particle>* particles;
public:
    QuadTree(float l, float g, float t, float timestep);
    ~QuadTree();
    void build();
    void insertParticle(Particle* p);
    void updateForces();
    void updateForce(Particle* p, Node* current);
    void updateForce(Particle* p);
    void updateVelocities(float dt);
    void updatePositions(float dt);
    void leapfrog();
    void computeMass(Node* n);
    std::vector<Particle>* getParticles();
    int getCalculations();
    void setParticles(std::vector<Particle>* particles);
    Node* getRoot();
    void forward();
    
};
#endif /* defined(__ParticleSystem__QuadTree__) */
