#include <math.h>
#include <iostream>
#define PI 3.14159265
using namespace std;
float value, theta;

int main(int argc, char** argv){
  for (value = -1; value <= 1; value +=0.001){
  	theta = atan(value) * 180 / PI;
    cout << "Theta : " << theta <<endl;
  }
  
  while (1){
  
  }
}

