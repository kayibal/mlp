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
static const int SCREEN_HEIGHT= 600;
using namespace std;
QuadTree* tree;
//Standard Configurations
double timestep = 1;
double gravitation_constant = 6.67e-8;
int n = 1000;
int max_mass = 100000;
int seed = 1334242;
double theta = 1;
int fc = 1;
double zoomTimes = 1;
double global_x = 0;
double global_y = 0;

double zoomfacor = 0.1;

std::vector<Particle> particles(n);
void DrawCircle(double cx, double cy, double r, int num_segments)
{
	glBegin(GL_POLYGON);
	for(int ii = 0; ii < num_segments; ii++)
	{
		double theta = 2.0f * 3.1415926f * double(ii) / double(num_segments);//get the current angle
        
		double x = r * cosf(theta);//calculate the x component
		double y = r * sinf(theta);//calculate the y component
        
		glVertex2f(x + cx, y + cy);//output vertex
        
	}
	glEnd();
}

void drawParticle(point p, double r){
    //a particle will be a simple rectangle for now
    glColor3f(1.0f, 1.0f, 1.0f);
    DrawCircle(p.getX(),p.getY(),r,20);
}
void render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    point center = tree->getCenter();
    double x = center.getX();
    double y = center.getY();
    //glPopMatrix();
    glLoadIdentity();
    glTranslatef(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0);
    glScalef(1/zoomTimes , 1/zoomTimes,0);
    glTranslatef(global_x, global_y, 0);
    if (fc == 1)
        glTranslatef(-x, -y, 0);
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
        zoomTimes += zoomfacor;
    } else if (button == GLUT_RIGHT_BUTTON){
        zoomTimes -= zoomfacor;
    }
}
void move(int key, int x, int y){
    if(key == GLUT_KEY_UP){
        global_y -= 5*zoomTimes;
    } else if(key == GLUT_KEY_DOWN){
        global_y += 5*zoomTimes;
    } else if(key == GLUT_KEY_LEFT){
        global_x += 5*zoomTimes;
    } else if(key == GLUT_KEY_RIGHT){
        global_x -= 5*zoomTimes;
    }
}

int main(int argc, char * argv[])
{
    if(argc == 8){
        timestep = strtof(argv[1], NULL);
        gravitation_constant = strtof(argv[2], NULL);
        n = (int)strtof(argv[3], NULL);
        seed = (int)strtof(argv[4], NULL);
        max_mass = (int)strtof(argv[5], NULL);
        theta = strtof(argv[6], NULL);
        fc = strtof(argv[7], NULL);
        
    } else {
        char res;
        std::cout << "usage: ksh timestep gravitation_constant particle_count max_mass seed theta follow_center \n ";
        std::cout << "use standard parameters to start simulation? \n";
        std::cin >> res;
        if(res!='y')
            exit(0);
    }
    //Init OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("KugelSternHaufen");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glutDisplayFunc(render);
    glutIdleFunc(update);
    glutMouseFunc(mouse);
    glutSpecialFunc(move);
    
    //Init rand 128923842
    srand(seed);
    
    //Move coordinate system to the middle of the screen
    glTranslatef(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0);
    
    //Init Tree
    tree = new QuadTree(10000,gravitation_constant, theta, timestep);
    
    //creating random particle data
    for (int i = 0; i < particles.size(); i++){
        double r1 = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
        double r2 = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
        double r3 = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
        double r4 = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
        double x = r1 * (SCREEN_WIDTH) - SCREEN_WIDTH/2;
        double y = r2 * (SCREEN_HEIGHT) - SCREEN_HEIGHT/2;
        double mass = rand() % max_mass;
        double r = (mass / max_mass)*5;
        double vx = r3;
        double vy = r4;
        for (int j = 0; j < i; j++) {
            double x2 = particles[j].getX();
            double y2 = particles[j].getY();
            if(x == x2 && y == y2){
                std::cout << "duplicate";
            }
        }
        std::cout << x << " " << y <<"\n";
        particles[i] = Particle(x,y,0,0,mass,r);
        particles[i].setVx(vx);
        particles[i].setVy(vy);
    }
    particles[1] = Particle(-300,-200,0,0,10*max_mass,20);
    particles[0] = Particle(233,130,0,0,100*max_mass,20);
    //linking particle data to tree
    tree->setParticles(&particles);

    std::cout << "Simulation runnning \n" << "use arrow keys to move and left and right mousebutton to zoom\n";
    glutMainLoop();
    return 0;
}

