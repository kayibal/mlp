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
#include "Vector3D.h"
class point:public Vector3D{
protected:
    double mass;
public:
    point();
    point(double xp, double yp);
    point(double xp, double yp, double zp);
    void setX(double xp);
    void setY(double yp);
    void setZ(double zp);
    double getX();
    double getY();
    double getZ();
    double distance(point& p1);
    void scale(double s);
    point operator+(const point& right);
    point operator-(const point& right);
    double operator*(const point& right);
    point operator*(const double& right);
};


#endif
