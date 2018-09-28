#include <armadillo>
#include <iostream>
#include "olb.h"
#include "readModel.h"

using namespace arma;

class Shape{
public:
  typedef std::vector<PointD> vectorPoints;
  typedef std::vector< vector<int> > vectorFaces;
private:
  string filename;
public:
  vectorPoints m_VecPoints;
  vectorFaces m_VecFaces;
  int vertexs;
  int edges;
  int faces;
  ReadContext ReadObject;
  t_Dimension dimension;
  OLB olb;
  Shape(t_Dimension d, string _filename): filename(_filename), dimension(d) {ReadObject.SetStrategy(dimension);}
  void Read(){ ReadObject.Read(filename,vertexs,edges,faces,m_VecPoints,m_VecFaces);}
  void GetMatrix(){ olb.getOLB(m_VecPoints,m_VecFaces,dimension);}
  void Operate(int n){ olb.operate(n); }
  void Show(){ olb.show(); }
  void PrintOFF(){
		for(auto &c: m_VecPoints)
			cout << c.m_VecPoints[0] << c.m_VecPoints[1] << c.m_VecPoints[2] << endl;
		for(auto &c: m_VecFaces)
			cout << c[0] << " " << c[1] << " " << c[2] << endl;
	}
};
