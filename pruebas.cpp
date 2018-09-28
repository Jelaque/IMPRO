#include <iostream>

using namespace std;

class Polygon{
protected:
  int a,l;
public:
  Polygon(int _a, int _b): a(_a), l(_b) {}
  virtual int area() = 0;
  void printArea() { cout << area() << endl; }
};

class Triangle: public Polygon{
public:
  Triangle(int _a, int _b): Polygon(_a,_b) {}
  int area() { return a*l / 2;}
};

class Rectangle: public Polygon{
public:
  Rectangle(int _a, int _b): Polygon(_a,_b) {}
  int area() { return a*l;}
};

main(){
  Polygon* p1 = new Triangle(2,1);
  Polygon* p2 = new Rectangle(2,1);
  p1->printArea();
  p2->printArea();
}
