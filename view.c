#include <math.h>
#include <GL/glut.h>
#include "mood_math.h"
#include "view.h"
#include "map.h"

extern float px,py,pa;
extern int map[];

void drawRays() {
    int r, mx,my,mp,dof;
    float rx,ry,ra,xo,yo,disT;

    glColor3f(0,1,1); glBegin(GL_QUADS); glVertex2i(526,  0); glVertex2i(1006,  0); glVertex2i(1006,160); glVertex2i(526,160); glEnd();
    glColor3f(0,0,1); glBegin(GL_QUADS); glVertex2i(526,160); glVertex2i(1006,160); glVertex2i(1006,320); glVertex2i(526,320); glEnd();

    ra=pa-DR*30; if(ra<0) { ra+=2*M_PI; } if (ra>2*M_PI) { ra-=2*M_PI; }
    for(r=0;r<60;r++) {
        //horizontal lines
        dof=0;
        float disH=1000000,hx=px,hy=py;
        float aTan=-1/tan(ra);
        if(ra>M_PI) { ry=(((int)py>>6)<<6)-0.0001; rx=(py-ry)*aTan+px; yo=-64; xo=-yo*aTan; }
        else if(ra<M_PI) { ry=(((int)py>>6)<<6)+64; rx=(py-ry)*aTan+px; yo=64; xo=-yo*aTan; }
        else { rx=px; ry=py; dof=8; }
        while(dof<8) {
            mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;
            if(mp>0 && mp<mapX*mapY && map[mp]==1) {
                hx=rx;
                hy=ry;
                disH=dist(px,py,hx,hy,ra);
                dof=8;
            } else { rx+=xo; ry+=yo; dof+=1; }
        }

        // vertical lines
        dof=0;
        float disV=1000000,vx=px,vy=py;
        float nTan=-tan(ra);
        if(ra>P2 && ra<P3) { rx=(((int)px>>6)<<6)-0.0001; ry=(px-rx)*nTan+py; xo=-64; yo=-xo*nTan; }
        else if(ra<P2 || ra>P3) { rx=(((int)px>>6)<<6)+64; ry=(px-rx)*nTan+py; xo=64; yo=-xo*nTan; }
        else { rx=px; ry=py; dof=8; }
        while(dof<8) {
            mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;
            if(mp>0 && mp<mapX*mapY && map[mp]==1) {
                vx=rx;
                vy=ry;
                disV=dist(px,py,vx,vy,ra);
                dof=8;
            } else { rx+=xo; ry+=yo; dof+=1; }
        }

        if(disV<disH) { rx=vx; ry=vy; disT=disV; glColor3f(0.9,0,0); }
        else if(disH<disV) { rx=hx; ry=hy; disT=disH; glColor3f(0.7,0,0); }
        glLineWidth(1); glBegin(GL_LINES); glVertex2i(px,py); glVertex2i(rx,ry); glEnd();

        // 3D walls 320*160
        float ca = pa-ra; if (ca<0) { ca+=2*M_PI; } if (ca>2*M_PI) { ca-=2*M_PI; } disT=disT*cos(ca);
        float lineH=(mapS*320)/disT; if(lineH>320) { lineH=320; }
        float lineOff = 160 - (lineH/2);
        glLineWidth(8);
        glBegin(GL_LINES);
        glVertex2i(r*8+530,lineOff);
        glVertex2i(r*8+530,lineH+lineOff);
        glEnd();
        ra+=DR;if(ra<0) { ra+=2*M_PI; } if (ra>2*M_PI) { ra-=2*M_PI; }
    }
}
