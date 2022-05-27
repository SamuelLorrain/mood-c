#include "mood_math.h"
#include <math.h>

float fixAng(float a) {
    if(a>359) {
        a-=360;
    } else if(a<0) {
        a+=360;
    }
    return a;
}
float degToRad(float a) {
    return a*M_PI/180.0;
}

float dist(float ax, float ay, float bx, float by, float ang) {
    return sqrt((bx-ax)*(bx-ax) + (by-ay)*(by-ay));
}

