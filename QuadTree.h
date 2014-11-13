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
namespace ksh{
template <typename Type>
class QuadTree{
    Node<Type>* root;
    int height;
    int size;
    double length;
    double gravitation_constant;
    double theta;
    double dt;
    int calculations;
    std::vector<Type>* particles;
private:
    void build(){
        if(particles != nullptr){
            double l = root->getLength();
            delete root;
            root = new Node<Type>(0,0,l,l);
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
            computeMass(root);
        } else {
            throw "particles are not set exception";
        }
    };
    void insertParticle(Type* p){
        double x = p->getX();
        double y = p->getY();
        if(!(x > length/2 | x < -length/2 | y < -length/2 | y > length/2)){
            root->insertParticle(p);
            size++;
        }
    };
    void updateForces(){
        calculations = 0;

        std::for_each(particles->begin(), particles->end(), [this](Type &p){
            this->updateForce(&p);
        });
    }
    void updateForce(Type* p, Node<Type>* current){
        if (current->getChildCount() == 0){
            //external node
            //calculate net force with particle
            p->addForce(current->getParticle(),gravitation_constant);
            calculations++;
        } else {
            //internal node
            double d = p->distance(*current->getCenterOfMass());
            if(current->getLength()/d < theta){
                //loop childs
                for (int i = 0; i < 4; i++){
                    Node<Type>* child = current->getChild(i);
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
    };
    void updateForce(Type* p){
        p->setFx(0);
        p->setFy(0);
        updateForce(p, root);
    };
    void updateVelocities(double dt){
        for(int i = 0; i < particles->size(); i++){
            Type* temp = &(*particles)[i];
            temp->updateVelocity(dt);
        }
    };
    void updatePositions(double dt){
        for(int i = 0; i < particles->size(); i++){
            Type* temp = &(*particles)[i];
            temp->updatePos(dt);
        }
    };
    void leapfrog(){
        updatePositions(0.5*dt);
        updateForces();
        updateVelocities(0.5*dt);
        updatePositions(0.5*dt);
    };
    void computeMass(Node<Type>* n){
        if(n->getParticle() != nullptr){
            //external node
            Type* p = n->getParticle();
            n->setMass(p->getMass());
            n->setCenterOfMass(p->getX(), p->getY());
        } else {
            for(int i = 0; i < 4; i++){
                if(n->getChild(i) != nullptr)
                    computeMass( n->getChild(i) );
            }
            double mass = 0;
            for (int i = 0; i < 4; i++){
                if(n->getChild(i) != nullptr)
                    mass += n->getChild(i)->getMass();
            }
            point com(0,0);
            for (int i = 0; i < 4; i++){
                if(n->getChild(i) != nullptr){
                    point* p = n->getChild(i)->getCenterOfMass();
                    double p_mass = n->getChild(i)->getMass();
                    com = com + (*p)*p_mass;
                }
            }
            com = com * (1/mass);
            n->setMass(mass);
            n->setCenterOfMass(com.getX(),com.getY());
        }
    };
    std::vector<Type>* getParticles(){
        return particles;
    };
    Node<Type>* getRoot(){
        return root;
    };
public:
    QuadTree(double l, double g, double t, double timestep){
        root = new Node<Type>(0,0,l,l);
        length = l;
        gravitation_constant = g;
        particles = nullptr;
        theta = t;
        dt = timestep;
        
    };
    ~QuadTree(){
        delete root;
    };
    void forward(){
        build(); //inserting all particles into tree
        leapfrog(); //calculate all forces and move particles
    };
    void setParticles(std::vector<Type>* p){
        particles = p;
    };
    int getCalculations(){
        return calculations;
    };
    point getCenter(){
        return *root->getCenterOfMass();
    };
};
}
#endif /* defined(__ParticleSystem__QuadTree__) */
