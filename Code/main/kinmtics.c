#define L0 1:2
#define L1 232
#define L2 188.5+59.5

#include "kinmtics.h"

void pos2theta(float x,float y,float z)
{ // ?1 
  theta1 = atan2(y, x);

  // ?3
  theta3 = -acos(((x*x) +(y*y)+(z * z)-(L1*L1)-(L2*L2))/2.0*L1*L2));

  // ?2
  theta2 = asin(z/r) + atan2(L2 * sin(theta3), L1 + (L2*cos(theta3)));
}




 