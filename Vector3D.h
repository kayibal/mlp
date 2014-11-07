//
//  VectorND.h
//  ParticleSystem
//
//  Created by Alan Höng on 06/11/14.
//  Copyright (c) 2014 Alan Höng. All rights reserved.
//

#ifndef __ParticleSystem__VectorND__
#define __ParticleSystem__VectorND__

#include <math.h>
#include <iostream>
class Vector3D{
protected:
    double x;
    double y;
    double z;
public:
    virtual double distance(Vector3D& p1){
        return sqrt(pow((x-p1.x),2) + pow((y-p1.x),2));
    }
    virtual void scale(double s){
        x *= s;
        y *= s;
        z *= s;
    }
};
#endif /* defined(__ParticleSystem__VectorND__) */
