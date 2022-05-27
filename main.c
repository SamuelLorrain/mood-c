#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "mood_math.h"
#include "map.h"
#include "view.h"

#define WIDTH 1024
#define HEIGHT 510

typedef struct {
    int z,q,s,d;
} ButtonKeys;
ButtonKeys Keys;

float px,py,pdx,pdy,pa; //player position
extern int map[];


void drawPlayer() {
    glColor3f(1,1,0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(px,py);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(px,py);
    glVertex2i(px+pdx*5, py+pdy*5);
    glEnd();
}

void display() {
    if (Keys.q == 1) { pa -=0.1; if(pa<0) { pa+=2*M_PI; } pdx=cos(pa)*5; pdy=sin(pa)*5; }
    if (Keys.d == 1) { pa +=0.1; if(pa>2*M_PI) { pa-=2*M_PI; } pdx=cos(pa)*5; pdy=sin(pa)*5; }
    if (Keys.z == 1) { px+=pdx; py+=pdy; }
    if (Keys.s == 1) { px-=pdx; py-=pdy; }
    glutPostRedisplay();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawMap2D();
    drawRays();
    drawPlayer();
    glutSwapBuffers();
}

void ButtonDown(unsigned char key, int x, int y) {
    if (key == 'q') { Keys.q = 1; }
    if (key == 'd') { Keys.d = 1; }
    if (key == 'z') { Keys.z = 1; }
    if (key == 's') { Keys.s = 1; }
    glutPostRedisplay();
}

void ButtonUp(unsigned char key, int x, int y) {
    if (key == 'q') { Keys.q = 0; }
    if (key == 'd') { Keys.d = 0; }
    if (key == 'z') { Keys.z = 0; }
    if (key == 's') { Keys.s = 0; }
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glutReshapeWindow(WIDTH,HEIGHT);
}

void init() {
    glClearColor(.3, .3, .3, 0);
    gluOrtho2D(0, WIDTH, HEIGHT, 0);
    px = 300;
    py = 300;
    pa = 1;
    pdx=cos(pa)*5;
    pdy=sin(pa)*5;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutInitWindowPosition(200,200);
    glutCreateWindow("test");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(ButtonDown);
    glutKeyboardUpFunc(ButtonUp);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
