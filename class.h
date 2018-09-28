#include <igl/eigs.h>
#include <igl/cotmatrix.h>
#include <igl/massmatrix.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/parula.h>
#include <igl/read_triangle_mesh.h>
#include <Eigen/Sparse>
#include <iostream>
#include <queue>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class Object{
  string filename;
  int eign;

  Eigen::MatrixXd V; // vertexs
  Eigen::MatrixXi F; // faces

  Eigen::SparseMatrix<double> L; // Laplacian Matrix
  Eigen::SparseMatrix<double> M; // Weight Matrix

  Eigen::MatrixXd U; // eigenfunction
  Eigen::VectorXd S; // eigenvalue

  vector<vector<double> > G; // GPS "k" average
public:
  Object(string f,int n): filename(f), eign(n) {operate();}
  vector<double> GPS(){
    size_t n = F.size();
    size_t k = S.size();
    G.reserve(n);
    vector<double> Average(n);
    double ave;
    double r;
    for(int i = 0; i < n; ++i){
      ave = 0;
      for(int j = 0; j < k; ++j){
        r = U(i,j)/sqrt(S(j));
        ave += r;
        G[i].push_back(r);
      }
      Average[i] = ave/k;
    }
    sort(Average.begin(),Average.end());
    return Average;
  }
  void operate(){
    igl::readOFF(filename,V,F);
    igl::cotmatrix(V,F,L);
    igl::massmatrix(V,F,igl::MASSMATRIX_TYPE_DEFAULT,M);
    L = (-L).eval();
    igl::eigs(L,M,eign,igl::EIGS_TYPE_SM,U,S);
  }
  void view(){
    igl::opengl::glfw::Viewer viewer;
    viewer.data().set_mesh(V,F);
    viewer.launch();
  }
};
