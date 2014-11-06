//
//  QuadTree.cpp
//  ParticleSystem
//
//  Created by Alan Höng on 24/10/14.
//  Copyright (c) 2014 Alan Höng. All rights reserved.
//

#include "QuadTree.h"
void QuadTree::updateForce(Particle* p, Node* current){
    if (current->getChildCount() == 0){
        //external node
        //calculate net force with particle
        p->addForce(current->getParticle(),gravitation_constant);
        calculations++;
    } else {
        //internal node
        float d = p->distance(*current->getCenterOfMass());
        if(current->getLength()/d < theta){
            //loop childs
            for (int i = 0; i < 4; i++){
                Node* child = current->getChild(i);
                if (child != nullptr){
                    updateForce(p, child);
                }
            }
        }
        else {
            //calculate net force with com
            calculations++;
            p->addForce(current->getCenterOfMass(), current->getMass(), gravitation_constant);
        }
    }
}
int QuadTree::getCalculations(){
    return calculations;
}

void QuadTree::computeMass(Node* n){
    std::cout << "computeMass \n";
    if(n->getParticle() != nullptr){
        //external node
        Particle* p = n->getParticle();
        n->setMass(p->getMass());
        n->setCenterOfMass(p->getX(), p->getY());
    } else {
        for(int i = 0; i < 4; i++){
            computeMass(n->getChild(i));
        }
        float mass = 0;
        for (int i = 0; i < 4; i++){
            mass += n->getChild(i)->getMass();
        }
        point com(0,0);
        for (int i = 0; i < 4; i++){
            point* p = n->getChild(i)->getCenterOfMass();
            float p_mass = n->getChild(i)->getMass();
            com = com + (*p)*p_mass;
            com = com * (1/mass);
        }
        n->setMass(mass);
        n->setCenterOfMass(com.getX(),com.getY());
    }
}
void QuadTree::updateForce(Particle* p){
    p->setFx(0);
    p->setFy(0);
    updateForce(p, root);
}
void QuadTree::insertParticle(Particle* p){
    float x = p->getX();
    float y = p->getY();
    if(!(x > length/2 | x < -length/2 | y < -length/2 | y > length/2)){
        root->insertParticle(p);
        size++;
    }
}
QuadTree::QuadTree(float l, float g, float t){
    root = new Node(0,0,l,l);
    length = l;
    gravitation_constant = g;
    particles = nullptr;
    theta = t;
    
}
void QuadTree::updateForces(){
    calculations = 0;
    for(int i = 0; i < particles->size(); i++){
        Particle* temp = &(*particles)[i];
        //std::cout << i << " " << (*particles)[i].getX() << " " << (*particles)[i].getY() <<"\n";
        updateForce(temp);
    }
    /*
    for(std::vector<Particle>::iterator i = particles->begin(); i != particles->end(); i++){
        updateForce(&*i);
    }
     */
}
std::vector<Particle>* QuadTree::getParticles(){
    return particles;
}
Node* QuadTree::getRoot(){
    return root;
}
void QuadTree::setParticles(std::vector<Particle>* p){
    particles = p;
}
QuadTree::~QuadTree(){
    delete root;
}
void QuadTree::build(){
    if(particles != nullptr){
        float l = root->getLength();
        delete root;
        root = new Node(0,0,l,l);
        for(int i = 0; i < particles->size(); i++){
            Particle* temp = &(*particles)[i];
            //std::cout << i << " " << (*particles)[i].getX() << " " << (*particles)[i].getY() <<"\n";
            insertParticle(temp);
        }
        /*
        for(std::vector<Particle>::iterator i = particles->begin(); i != particles->end(); i++){
            std::cout << &i->getX() << " " <<"\n";
            insertParticle(*i);
        }*/
        std::cout << "computing masses \n";
        computeMass(root);
    } else {
        throw "particles are not set exception";
    }
}