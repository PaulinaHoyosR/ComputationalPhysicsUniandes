#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float func_prime_0(float x, float y_0, float y_1){
  return y_1;
}

float func_prime_1(float x, float y_0, float y_1){
  return -4.0*sin(y_0);
}

float* RungeKuttaFourthOrderStep(float h, float x_old, float y_0_old, float y_1_old){
  
  /* Get K1 */
  float k1_0;
  float k1_1;

  k1_0 = func_prime_0(x_old, y_0_old, y_1_old);
  k1_1 = func_prime_1(x_old, y_0_old, y_1_old);


  /* Move to the middle of the interval using k1*/

  float x_middle_1;
  float y_0_middle_1;
  float y_1_middle_1;

  x_middle_1 = x_old + (h/2.0);
  y_0_middle_1 = y_0_old + (h/2.0) * k1_0;
  y_1_middle_1 = y_1_old + (h/2.0) * k1_1;

  
  /* Get K2 */
  
  float k2_0;
  float k2_1;

  k2_0 = func_prime_0(x_middle_1, y_0_middle_1, y_1_middle_1);
  k2_1 = func_prime_1(x_middle_1, y_0_middle_1, y_1_middle_1);


  /* Move to the middle of the interval using k2 */
  
  float x_middle_2;
  float y_0_middle_2;
  float y_1_middle_2;

  x_middle_2 = x_old + (h/2.0);
  y_0_middle_2 = y_0_old + (h/2.0) * k2_0;
  y_1_middle_2 = y_1_old + (h/2.0) * k2_1;


  /* Get k3 */

  float k3_0;
  float k3_1;

  k3_0 = func_prime_0(x_middle_2, y_0_middle_2, y_1_middle_2);
  k3_1 = func_prime_1(x_middle_2, y_0_middle_2, y_1_middle_2);

  /* Move at the end of the interval using k3 */
  
  float x_end;
  float y_0_end;
  float y_1_end;

  x_end = x_old + h;
  y_0_end = y_0_old + h*k3_0;
  y_1_end = y_1_old + h*k3_1;


  /* Get k4 */

  float k4_0 = func_prime_0(x_end, y_0_end, y_1_end);
  float k4_1 = func_prime_1(x_end, y_0_end, y_1_end);


  /* Get K_average */

  float k_average_0;
  float k_average_1;

  k_average_0 = (1.0/6.0) * (k1_0 + 2.0*k2_0 + 2.0*k3_0 + k4_0);
  k_average_1 = (1.0/6.0) * (k1_1 + 2.0*k2_1 + 2.0*k3_1 + k4_1);


  /* Get new x, y_o, y_1 */

  float x_new = x_old + h;
  float y_0_new = y_0_old + h*k_average_0;
  float y_1_new = y_1_old + h*k_average_1;

  float array_new[3];
  array_new[0] = x_new;
  array_new[1] = y_0_new;
  array_new[2] = y_1_new;

  return array_new;  
}

int main(){

  
  
  return 0;
}
