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
Node::Node(float xmidp, float ymidp, float h, float w){
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
    float h = heigth/2;
    float w = width/2;
    float new_mid_x;
    float new_mid_y;
    float x = new_p->getX();
    float y = new_p->getY();
    int index;
    //std::cout << "inserting particle " << x <<" " << y <<" middle is" << xmid <<" " << ymid << "\n" ;
    //This node will become internal
    //its not allowed to contain a particle anymore
    //Update center of mass of internal nodes
    if (x >= xmid && y >= ymid){
        //NE
        //std::cout << "NE\n";
        index = 0;
        new_mid_x = xmid + w/2;
        new_mid_y = ymid + h/2;
    } else if (x >= xmid && y <= ymid){
        //SE
        //std::cout << "SE\n";
        index = 1;
        new_mid_x = xmid + w/2;
        new_mid_y = ymid - h/2;
    } else if (x <= xmid && y <= ymid ){
        //SW
        //std::cout << "SW\n";
        index = 2;
        new_mid_x = xmid - w/2;
        new_mid_y = ymid - h/2;
    } else if ( x <= xmid && y >= ymid){
        //NW
        //std::cout << "NW\n";
        index = 3;
        new_mid_x = xmid - w/2;
        new_mid_y = ymid + h/2;
    } else {
        throw "Error could not determine position in quad\n";
        return;
    }
    // Node is free
    if(child[index] == nullptr){
        //std::cout << "Node is free case\n";
        child[index] = new Node(new_mid_x, new_mid_y, h, w);
        child[index]->setParticle(new_p);
        children++;
        //if we created a new internal node find new node for the containing particle
        if(this->p != nullptr){
            //std::cout << "reinserting particle: " << this->p->getX() <<" " << this->p->getY()<<"\n";
            Particle* temp = this->p;
            this->p = nullptr;
            //temp->print();
            this->insertParticle(temp);
            //remove particle from new internal node
            
        }
        #warning not correct
        /*
        //update total mass
        mass += new_p->getMass();
        //Update center of mass of node
        float totalMass = mass + new_p->getMass();
        float comx = (centerOfMass.getX()*mass + new_p->getX()*new_p->getMass());
        float comy = (centerOfMass.getY()*mass + new_p->getY()*new_p->getMass());
        centerOfMass.setX(comx);
        centerOfMass.setY(comy);
        centerOfMass = centerOfMass*(1/totalMass);
        //std::cout << "Node inserted\n";
        */
    } else {
        //std::cout << "recursive case: " << child[index]->getParticle()->getX() <<" " << child[index]->getParticle()->getY() <<"\n";
        child[index]->insertParticle(new_p);
    }
    
}
void Node::setParticle(Particle* particle){
    p = particle;
    mass = particle->getMass();
    //????? :O
    centerOfMass = point(particle->getX(),particle->getY());
}
bool Node::isInside(point p){
    float x = p.getX();
    float y = p.getY();
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
float Node::getLength(){
    return width;
}
Particle* Node::getParticle(){
    return p;
}
float Node::getMass(){
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
void Node::setMass(float m){
    mass = m;
}
void Node::setCenterOfMass(float x, float y){
    centerOfMass.setX(x);
    centerOfMass.setY(y);
}