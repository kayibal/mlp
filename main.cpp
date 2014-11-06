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
#include "QuadTree.h"
#include "particle.h"

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
QuadTree* tree;


//Configurations
float timestep = 1;
float gravitation_constant = 6.67e-8;
int n = 1000;
int max_mass = 100000;
int seed = 1334242;
float theta = 0.5;
//Integration method 1 is more accurate 0 is faster
int mode = 0;

float zoomfacor = 1.1;


std::vector<Particle> particles(n);
void DrawCircle(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_POLYGON);
	for(int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
        
		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component
        
		glVertex2f(x + cx, y + cy);//output vertex
        
	}
	glEnd();
}

void drawParticle(point p, float r){
    //a particle will be a simple rectangle for now
    glColor3f(1.0f, 1.0f, 1.0f);
    DrawCircle(p.getX(),p.getY(),r,20);
}
void render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    for(std::vector<Particle>::iterator i = particles.begin(); i != particles.end(); i++){
        drawParticle(*i,i->getRadius());
    }
    glFlush();
    glutPostRedisplay();
}

void update(){
    tree->forward();
}
void mouse(int button, int state, int x, int y)
{
    // Wheel reports as button 3(scroll up) and button 4(scroll down)
    if(button == GLUT_LEFT_BUTTON){
        glScalef(zoomfacor,zoomfacor,0);
    } else if (button == GLUT_RIGHT_BUTTON){
        glScalef(1/zoomfacor,1/zoomfacor,0);
    }
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
    glutIdleFunc(update);
    glutMouseFunc(mouse);
    
    //Init rand 128923842
    srand(seed);
    
    //Move coordinate system to the middle of the screen
    glTranslatef(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0);
    
    //Init Tree
    tree = new QuadTree(10000,gravitation_constant, theta, timestep);
    
    //creating random particle data
    for (int i = 0; i < particles.size(); i++){
        float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float x = r1 * (SCREEN_WIDTH) - SCREEN_WIDTH/2;
        float y = r2 * (SCREEN_HEIGHT) - SCREEN_HEIGHT/2;
        float mass = rand() % max_mass;
        //float r = 3;
        for (int j = 0; j < i; j++) {
            float x2 = particles[j].getX();
            float y2 = particles[j].getY();
            if(x == x2 && y == y2){
                std::cout << "duplicate";
            }
        }
        std::cout << x << " " << y <<"\n";
        particles[i] = Particle(x,y,0,0,mass,2);
    }
    particles[1] = Particle(-300,-200,0,0,100*max_mass,20);
    particles[0] = Particle(233,130,0,0,100*max_mass,20);
    //linking particle data to tree
    tree->setParticles(&particles);
    tree->forward();
    tree->forward();
    Node* n = (tree->getRoot());
    glutMainLoop();
    return 0;
}

