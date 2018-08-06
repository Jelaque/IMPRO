#ifndef POINT_H
#define POINT_H
#include <vector>
#include <stdexcept>
#include <iostream>

using namespace std;

typedef int t_Dimension;

class PointD{
public:
  t_Dimension dimension;
  typedef double t_Point;
  vector<t_Point> m_VecPoints;
  PointD(t_Dimension D): dimension(D) { m_VecPoints.reserve(D); }
  PointD(t_Dimension D, vector<t_Point> v): dimension(D) {
    if(v.size() != D)
      throw runtime_error("Invalid operation for copying into a different dimensional point");
    m_VecPoints = v;
  }
  //PointD(PointD &o): dimension(o.dimension) {m_VecPoints = o.m_VecPoints;}
  PointD operator+(const PointD &o){
    if(o.m_VecPoints.size() != dimension)
      throw runtime_error("Invalid operation for copying into a different dimensional point");
    PointD newPoint(dimension);
    for(int i = 0; i < dimension; ++i)
      newPoint.m_VecPoints[i] = this->m_VecPoints[i] + o.m_VecPoints[i];
    return newPoint;
  }
  PointD operator-(const PointD &o){
    if(o.m_VecPoints.size() != dimension)
      throw runtime_error("Invalid operation for copying into a different dimensional point");
    PointD newPoint(dimension);
    for(int i = 0; i < dimension; ++i)
      newPoint.m_VecPoints[i] = this->m_VecPoints[i] - o.m_VecPoints[i];
    return newPoint;
  }
  /*void operator=(PointD o){
    for(int i = 0; i < this->dimension; ++i){
      this->m_VecPoints[i] = o.m_VecPoints[i];
      cout << this->m_VecPoints[i] << '\n';
    }
  }*/
  friend std::ostream& operator<<(std::ostream& o, PointD &p){
    o << "( ";
    for(int i = 0; i < p.dimension; ++i)
      o << p.m_VecPoints[i] << " ";
    o << ")";
  }
};
#endif
