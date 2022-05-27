#ifndef MOOD_MATH_H
#define MOOD_MATH_H
#include <math.h>

#define DR 0.0174533 //one degree in radians
#define P2 M_PI/2
#define P3 (3*M_PI)/2

float fixAng(float a);
float degToRad(int a);
float dist(float ax, float ay, float bx, float by, float ang);

#endif
