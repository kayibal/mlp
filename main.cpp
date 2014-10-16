//
//  main.cpp
//  ParticleSystem
//
//  Created by Alan Höng on 16/10/14.
//  Copyright (c) 2014 Alan Höng. All rights reserved.
//

//Cross PLattform OpenGL include :)
#include <stdlib.h>
#include <iostream>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

static const int SCREEN_WIDTH = 900;
static const int SCREEN_HEIGHT = 600;

using namespace std;
void drawParticle(float x, float y, float r){
    //a particle will be a simple rectangle for now
    glColor3f(1.0f, 1.0f, 1.0f);
    glRectf(x,y,x+r,y+r);
}
void render(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    //Move coordinate system to the middle of the screen
    glTranslatef(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0);
    
    for (int i = 0; i < 10000; i++){
        float x = (rand() % (SCREEN_WIDTH)) - SCREEN_WIDTH/2;
        float y = (rand() % (SCREEN_HEIGHT)) - SCREEN_HEIGHT/2;
        
        float r = rand() % 3;
        
        drawParticle(x, y, r);
    }
    
    glFlush();
}
int main(int argc, char * argv[])
{
    //Init OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Particle Simulation");
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);
    glutDisplayFunc(render);
    
    //Init rand
    srand(128923842);
    
    glutMainLoop();
    return 0;
}

