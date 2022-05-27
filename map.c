#include <GL/glut.h>
#include "map.h"

int map[] = {
    1,1,1,1,1,1,1,1,
    1,0,1,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,1,0,0,0,0,1,
    1,0,0,0,1,0,0,1,
    1,0,0,0,0,1,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,
};

void drawMap2D() {
    int x,y,xo,yo;
    for(y=0; y<mapY;y++) {
        for(x=0; x<mapX;x++) {
            if(map[y*mapX+x] == 1) {
                glColor3f(1,1,1);
            } else {
                glColor3f(0,0,0);
            }
            xo=x*mapS;
            yo=y*mapS;
            glBegin(GL_QUADS);
            glVertex2i(xo     +1,yo     +1);
            glVertex2i(xo     +1,yo+mapS-1);
            glVertex2i(xo+mapS-1,yo+mapS-1);
            glVertex2i(xo+mapS-1,yo     +1);
            glEnd();

            glColor3f(1,0,0);
            glPointSize(5);
            glBegin(GL_POINTS);
            glVertex2i(0,0);
            glEnd();
        }
    }
}
