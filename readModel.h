#include <stdexcept>
#include <fstream>
#include <algorithm>
#include "point.h"

using namespace std;

class ReadStrategy;

class ReadContext{
private:
  ReadStrategy* strategy;
public:
  ReadContext(): strategy(nullptr) {}
  void SetStrategy(t_Dimension);
  void Read(const string &, int &, int &, int &, vector< PointD > &, vector< vector <int> > &);
  ~ReadContext() = default;
};

class ReadStrategy{
public:
  ReadStrategy(const int _dimension): dimension(_dimension){}
  virtual void ReadFile(const string &, int &, int &, int &, vector< PointD > &, vector< vector <int> > &) = 0;
protected:
  int dimension;
};

class ReadOFF: public ReadStrategy{
public:
  ReadOFF(const int _dimension): ReadStrategy(_dimension) {}
  void ReadFile(const string &filename, int &vertexs, int &edges, int &faces, vector< PointD > &m_Vertexs, vector< vector <int> > &m_Faces){
		ifstream file(filename);
		int t;
		string trash;
		file>>trash;
		file>>vertexs>>faces>>edges;
    int i = 0;
		while(i < vertexs){
      vector<double> p(dimension);

			if(file>>p[0]>>p[1]>>p[2]){
				m_Vertexs.push_back(PointD(dimension,p));
			}
			else
				break;
			++i;
		}
		i = 0;
		while(i < faces){
      vector<int> v(dimension);

			if(file>>t>>v[0]>>v[1]>>v[2]){
				sort(v.begin(), v.end());
				m_Faces.push_back(v);
			}
			else
				break;
			++i;
		}
	}
};

//ReadStrategy functions
void ReadContext::SetStrategy(t_Dimension D){
  delete strategy;
  switch (D) {
    case 3:
      strategy = new ReadOFF(D);
      break;
    default:
      break;
  }
}
void ReadContext::Read(const string &filename, int &vertexs, int &edges, int &faces, vector< PointD > &m_Vertexs, vector< vector <int> > &m_Faces){
  (strategy) ? strategy->ReadFile(filename,vertexs,edges,faces,m_Vertexs,m_Faces) : throw runtime_error("No strategy set");
}
