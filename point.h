//
//  point.h
//  ParticleSystem
//
//  Created by Alan Höng on 17/10/14.
//  Copyright (c) 2014 Alan Höng. All rights reserved.
//

#ifndef ParticleSystem_point_h
#define ParticleSystem_point_h

#include <math.h>


class point{
protected:
    float x;
    float y;
    float z;
public:
    point();
    point(float xp, float yp);
    point(float xp, float yp, float zp);
    void setX(float xp);
    void setY(float yp);
    void setZ(float zp);
    float getX();
    float getY();
    float getZ();
    float distance(point p1);
    void scale(float s);
    point operator+(const point& right);
    point operator-(const point& right);
    float operator*(const point& right);
    point operator*(const float& right);
};


#endif
