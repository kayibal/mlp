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
namespace ksh{
template <typename Type>
class Node{
    double xmid;
    double ymid;
    //TODO: change this to length must be quadratric
    double heigth;
    double width;
    
    point centerOfMass;
    double mass;
    
    Type* p;
    
    std::array<Node*,4> child;
    short children;
    
public:
    Node(){
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
    };
    Node(double xmidp, double ymidp, double h, double w){
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
    };
    ~Node(){
        if(children>0){
            for (int i = 0; i<4; i++){
                if(child[i]!=nullptr){
                    delete child[i];
                }
            }
        }
        child.~array();
    }
    void insertParticle(Type* new_p){
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
                Type* temp = this->p;
                this->p = nullptr;
                this->insertParticle(temp);
                //remove particle from new internal node
                
            }
        } else {
            child[index]->insertParticle(new_p);
        }
        
    };
    bool isInside(point p){
        double x = p.getX();
        double y = p.getY();
        if( x > (xmid-width/2) & x < (xmid+width/2)){
            if (y > (ymid-heigth/2) & y < (ymid + heigth/2) )
                return true;
        }
        return false;
    };
    void setParticle(Type* particle){
        p = particle;
        mass = particle->getMass();
        centerOfMass = point(particle->getX(),particle->getY());
    };
    short getChildCount(){
        return children;
    }
    Node* getChild(int i){
        return child[i];
    }
    point* getCenterOfMass(){
        return &centerOfMass;
    }
    double getLength(){
        return width;
    }
    Type* getParticle(){
        return p;
    }
    double getMass(){
        return mass;
    }
    void setMass(double m){
        mass = m;
    }
    void setCenterOfMass(double x, double y){
        centerOfMass.setX(x);
        centerOfMass.setY(y);
    }
};
}
#endif /* defined(__ParticleSystem__Node__) */
