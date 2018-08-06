#include <iostream>
#include <vector>
#include "shape.h"

main(){
  Shape A(3,"aaa.off");
  A.Read();
  A.PrintOFF();
  A.GetMatrix();
}
