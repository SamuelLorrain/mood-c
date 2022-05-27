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
    glVertex2i(px+pdx*20, py+pdy*20);
    glEnd();
}

float frame1, frame2,fps;
void display() {
    frame2=glutGet(GLUT_ELAPSED_TIME);
    fps=(frame2-frame1);
    frame1=glutGet(GLUT_ELAPSED_TIME);

    // set direction
    if (Keys.q == 1) { pa -=0.005*fps; if(pa<0) { pa+=2*M_PI; } pdx=cos(pa); pdy=sin(pa); }
    if (Keys.d == 1) { pa +=0.005*fps; if(pa>2*M_PI) { pa-=2*M_PI; } pdx=cos(pa); pdy=sin(pa); }

    int xo=0; if(pdx<0) { xo=-20; } else { xo=20; }
    int yo=0; if(pdy<0) { yo=-20; } else { yo=20; }
    int ipx=(int)px>>6, ipx_add_xo=(int)(px+xo)>>6, ipx_sub_xo=(int)(px-xo)>>6;
    int ipy=(int)py>>6, ipy_add_yo=(int)(py+yo)>>6, ipy_sub_yo=(int)(py-yo)>>6;

    if (Keys.z == 1) {
        if(map[ipy*mapX + ipx_add_xo] == 0) { px+=pdx*0.15*fps; }
        if(map[ipy_add_yo*mapX + ipx] == 0) { py+=pdy*0.15*fps; }
    }
    else if (Keys.s == 1) {
        if(map[ipy*mapX + ipx_sub_xo] == 0) { px-=pdx*0.15*fps; }
        if(map[ipy_sub_yo*mapX + ipx] == 0) { py-=pdy*0.15*fps; }
    }
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
    if (key == 'i') { exit(0); }
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glutReshapeWindow(WIDTH,HEIGHT);
}

void init() {
    glClearColor(.3, .3, .3, 0);
    gluOrtho2D(0, WIDTH, HEIGHT, 0);
    px = 200;
    py = 200;
    pa = 1;
    pdx=cos(pa)*0.1;
    pdy=sin(pa)*0.1;
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
