//
//  Node.cpp
//  ParticleSystem
//
//  Created by Alan Höng on 24/10/14.
//  Copyright (c) 2014 Alan Höng. All rights reserved.
//

#include "Node.h"
Node::Node(){
    xmid = 0;
    ymid = 0;
    p = nullptr;
    mass = 0;
    centerOfMass = point(0,0);
    heigth = 0;
    width = 0;
    children = 0;
    for (int i = 0; i < 4; i++){
        child[i]=nullptr;
    }
}
Node::Node(double xmidp, double ymidp, double h, double w){
    xmid = xmidp;
    ymid = ymidp;
    p = nullptr;
    mass = 0;
    centerOfMass = point(0,0);
    heigth = h;
    width = w;
    children = 0;
    for (int i = 0; i < 4; i++){
        child[i]=nullptr;
    }
}


void Node::insertParticle(Particle* new_p){
    double h = heigth/2;
    double w = width/2;
    double new_mid_x;
    double new_mid_y;
    double x = new_p->getX();
    double y = new_p->getY();
    int index;
    //This node will become internal
    //its not allowed to contain a particle anymore
    if (x >= xmid && y >= ymid){
        //NE
        index = 0;
        new_mid_x = xmid + w/2;
        new_mid_y = ymid + h/2;
    } else if (x >= xmid && y <= ymid){
        //SE
        index = 1;
        new_mid_x = xmid + w/2;
        new_mid_y = ymid - h/2;
    } else if (x <= xmid && y <= ymid ){
        //SW
        index = 2;
        new_mid_x = xmid - w/2;
        new_mid_y = ymid - h/2;
    } else if ( x <= xmid && y >= ymid){
        //NW
        index = 3;
        new_mid_x = xmid - w/2;
        new_mid_y = ymid + h/2;
    } else {
        throw "Error could not determine position in quad\n";
        return;
    }
    // Node is free
    if(child[index] == nullptr){
        child[index] = new Node(new_mid_x, new_mid_y, h, w);
        child[index]->setParticle(new_p);
        children++;
        //if we created a new internal node find new node for the containing particle
        if(this->p != nullptr){
            Particle* temp = this->p;
            this->p = nullptr;
            this->insertParticle(temp);
            //remove particle from new internal node
            
        }
    } else {
        child[index]->insertParticle(new_p);
    }
    
}
void Node::setParticle(Particle* particle){
    p = particle;
    mass = particle->getMass();
    centerOfMass = point(particle->getX(),particle->getY());
}
bool Node::isInside(point p){
    double x = p.getX();
    double y = p.getY();
    if( x > (xmid-width/2) & x < (xmid+width/2)){
        if (y > (ymid-heigth/2) & y < (ymid + heigth/2) )
            return true;
    }
    return false;
}

short Node::getChildCount(){
    return children;
}
Node* Node::getChild(int i){
    return child[i];
}
point* Node::getCenterOfMass(){
    return &centerOfMass;
}
double Node::getLength(){
    return width;
}
Particle* Node::getParticle(){
    return p;
}
double Node::getMass(){
    return mass;
}
Node::~Node(){
    if(children>0){
        for (int i = 0; i<4; i++){
            if(child[i]!=nullptr){
                delete child[i];
            }
        }
    }
    child.~array();
}
void Node::setMass(double m){
    mass = m;
}
void Node::setCenterOfMass(double x, double y){
    centerOfMass.setX(x);
    centerOfMass.setY(y);
}