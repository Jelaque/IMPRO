#include "shape.h"
#include <fstream>
#define PATH_SOURCE "../animales/"
#define result "result"
using namespace std;

main(){
  string file;
  cin>>file;
  Shape A(3,file);
  A.Read();
  A.PrintOFF();
  A.GetMatrix();
  A.Operate(1);
  A.Show();
  /*int n;
  cin>>n;
  string filename;
  ifstream filedb("../db.txt");
  vector<vector<double> > VectorAverages;
  int i = 0;
  while(filedb >> filename){
    cout << filename << endl;
    Object A(PATH_SOURCE + filename,n);
    VectorAverages.push_back(A.GPS());
  }
  filedb.close();
  size_t size = VectorAverages.size();
  for(int j = 0; j < size; ++i){
    filename = "../result/result" + to_string(j);
    ofstream fileresult(filename);
  }
  */
}
