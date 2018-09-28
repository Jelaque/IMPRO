#include <armadillo>
#include "point.h"
#include <cmath>
#include <bitset>
#define pi 3.1415

using namespace arma;
using namespace std;

class OLB{
public:
  string output;
  vec eigval;
  mat eigvec;
  sp_mat WeightMatrix;
  OLB(){}
  bool findOcurrence(vector<int> &v1, vector<int> &v2, int &a, int &b, t_Dimension d){
    bool found;
    int times = 0;
    bitset<3> Ocurrences;
    for (int i = 0; i < 3; ++i){
      found = false;
      for(int j = 0; j < 3; ++j){
        if(v1[i] == v2[j]){
          found = true;
          Ocurrences[j] = 1;
        }
      }
      if(!found){
        ++times;
        a = v1[i];
      }
      if(times > 1)
        return false;
    }
    if(times == 1){
      for(int i = 0; i < 3; ++i){
        if(Ocurrences[i] == 0){
          b = v2[i];
          return true;
        }
      }
    }
    return false;
	}
  double GetWeight(vector<int> &v1, vector<int> &v2,const int &a,const int &b, t_Dimension d, vector< PointD > &m_Points){
		vector<PointD> v;
		for(int i = 0, j = 0; i < v1.size(); ++i){
			if(v1[i] != a){
				v.push_back(m_Points[v1[i]]);
				++j;
			}
		}
		double r1 = 0,r2 = 0, d1 = 1, d2 = 1,t1,t2;
		v.push_back(v[0] - m_Points[a]);
		v.push_back(v[1] - m_Points[a]);
    //cout << v[0] << "," << v[1] << endl;
    for(int i = 0; i < d; ++i)
      r1 += v[2].m_VecPoints[i] * v[3].m_VecPoints[i];
    for(int ii = 2; ii < 4; ++ii){
      t1 = 0;
      for(int i = 0; i < d; ++i){
        t1 += pow(v[ii].m_VecPoints[i],2);
      }
      d1 *= sqrt(t1);
    }
    //cout << acos(r1/d1)*180/pi <<  '\n';
		v[2] = v[0] - m_Points[b];
		v[3] = v[1] - m_Points[b];
    for(int i = 0; i < d; ++i)
      r2 += v[2].m_VecPoints[i] * v[3].m_VecPoints[i];

    for(int ii = 2; ii < 4; ++ii){
      t2 = 0;
      for(int i = 0; i < d; ++i){
        t2 += pow(v[ii].m_VecPoints[i],2);
      }
      d2 *= sqrt(t2);
    }
    //cout << acos(r2/d1)*180/pi <<'\n';
    r1 = 1/tan(acos(r1/d1));
    r2 = 1/tan(acos(r2/d2));
    return (r1 + r2)/2;
	}
  void getOLB(vector<PointD> &vecPoints, vector< vector<int> > &vecFaces, t_Dimension d){
    size_t size = vecFaces.size();
    WeightMatrix.set_size(size,size);
    vector<int> aux1(3);
    vector<int> aux2(3);
    int a,b;
    double v;
    for(int i = 0; i < size; ++i){
      aux1 = vecFaces[i];
      //v = 0;
      for(int j = i+1; j < size; ++j){
        aux2 = vecFaces[j];
        if(findOcurrence(aux1,aux2,a,b,d)){
          double r = GetWeight(aux1,aux2,a,b,d,vecPoints);
          //v += r;
          WeightMatrix(i,j) = WeightMatrix(j,i) = r;
          //cout << "(" << a << "," << b << ") = " << r << endl;
        }
      }
      WeightMatrix(i,i) = -v;
    }
    for(int i = 0; i < size; ++i){
      v = 0;
      for(int j = 0; j < size; ++j)
        v += WeightMatrix(i,j);
      WeightMatrix(i,i) = -v;
    }
    cout << WeightMatrix << endl;
  }
  void operate(int n){
    eigs_sym(this->eigval, this->eigvec, this->WeightMatrix, n);
  }
  void show(){
    cout << this->eigval << endl;
    cout << this->eigvec << endl;
  }
};
