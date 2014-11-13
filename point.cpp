//
//  point.cpp
//  ParticleSystem
//
//  Created by Alan Höng on 17/10/14.
//  Copyright (c) 2014 Alan Höng. All rights reserved.
//
#include "point.h"
using namespace ksh;
point::point(){
    x = 0;
    y = 0;
    z = 0;
}
point::point(double xp, double yp){
    x = xp;
    y = yp;
    z = 0;
    
}
point::point(double xp, double yp, double zp){
    x = xp;
    y = yp;
    z = zp;
    
}
void point::setX(double xp){
    x = xp;
    
}
void point::setY(double yp){
    y = yp;
    
}
void point::setZ(double zp){
    z = zp;
    
}
double point::getX(){
    return x;
}
double point::getY(){
    return y;
}
double point::getZ(){
    return z;
}
double point::distance(point &p1){
    return sqrt(pow((x-p1.getX()),2) + pow((y-p1.getY()),2));
}
void point::scale(double s){
    x *= s;
    y *= s;
    z *= z;
}
point point::operator+(const point& right){
    point sum(0.0,0.0);
    sum.setX(x+right.x);
    sum.setY(y+right.y);
    sum.setZ(z+right.z);
    return sum;
}
point point::operator-(const point& right){
    point tmp(0.0,0.0);
    tmp.setX(x-right.x);
    tmp.setY(y-right.y);
    tmp.setZ(z-right.z);
    return tmp;
}
double point::operator*(const point& right){
    return (x*right.x + y*right.y + z*right.z);
    
}
point point::operator*(const double& right){
    point tmp(0.0,0.0);
    tmp.setX(x*right);
    tmp.setY(y*right);
    tmp.setZ(z*right);
    return tmp;
}