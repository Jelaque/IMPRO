#include<iostream>
#include<armadillo>
#include<fstream>
#include<map>
#include<vector>
#include<cmath>

using namespace std;
using namespace arma;

class PointXYZ{
public:
	typedef double t_point;
	t_point x;
	t_point y;
	t_point z;
	PointXYZ(): x(0), y(0), z(0){}
	PointXYZ(t_point _x, t_point _y, t_point _z): x(_x), y(_y), z(_z) {}
	PointXYZ operator+(PointXYZ &o){ return PointXYZ(x+o.x,y+o.y,z+o.z);}
	PointXYZ operator-(PointXYZ &o){ return PointXYZ(x-o.x,y-o.y,z-o.z);}
	void operator+=(PointXYZ &o){
		x = x + o.x;
		y = y + o.y;
		z = z + o.z;
	}
	void operator-=(PointXYZ &o){
		x = x - o.x;
		y = y - o.y;
		z = z - o.z;
	}
};

class GetMatrix{
public:
	vector< tuple<int,int,int> > m_Faces;
	vector<PointXYZ> m_Vertexs;
	PointXYZ::t_point vertexs;
	PointXYZ::t_point edges;
	sp_mat m_EigenMatrix;
	vec m_EigenVector;
	void readOFF(string filename){
		ifstream file(filename);
		int faces,t;
		double x,y,z;
		vector<int> v(3);
		string trash;
		file>>trash;
		file>>vertexs>>edges>>faces;
		int i = 0;
		while(i < vertexs){
			if(file>>x>>y>>z){
				m_Vertexs.push_back(PointXYZ(x,y,z));
			}
			else
				break;
			++i;
		}
		i = 0;
		while(i < edges){
			if(file>>t>>v[0]>>v[1]>>v[2]){
				sort(v.begin(), v.end());
				m_Faces.push_back(make_tuple(v[0],v[1],v[2]));
			}
			else
				break;
			++i;
		}
	}
	void printOFF(){
		for(auto &c: m_Vertexs)
			cout << c.x << c.y << c.z << endl;
		for(auto &c: m_Faces)
			cout << get<0>(c) << " " << get<1>(c) << " " << get<2>(c) << endl;
	}
	bool findOcurrence(vector<int> &v1, vector<int> &v2, int &a, int &b){
		int oc = 1;
		bool e;
		int j;
		for(int i = 0; i < 3; ++i){
			e = false;
			for(j = 0; j < 3; ++j)
				if(v2[j] == v1[i])
					e = true;
			if(e == false){
				if(oc == 0)
					return false;
				else{
					--oc;
					a = i;
					b = j;
				}
			}
		}
		return true;
	}
	double GetWeight(vector<int> &v1, vector<int> &v2, int &a, int &b){
		vector<PointXYZ> v(4);
		for(int i = 0, j = 0; i < 3; ++i){
			if(i != a){
				v[j] = v1[i];
				++j;
			}
		}
		double r1,r2;
		v[2] = v[0] - v1[a];
		v[3] = v[1] - v1[a];
		r1 = (v[2].x * v[3].x) + (v[2].y * v[3].y) + (v[2].z * v[3].z);
		r1 /= sqrt(pow(v[2].x,2) + pow(v[3].x,2))*sqrt(pow(v[2].x,2) + pow(v[3].x,2))*sqrt(pow(v[2].x,2) + pow(v[3].x,2));
		v[2] = v[0] - v1[b];
		v[3] = v[1] - v1[b];
		r2 = (v[2].x * v[3].x) + (v[2].y * v[3].y) + (v[2].z * v[3].z);
		r2 /= sqrt(pow(v[2].x,2) + pow(v[3].x,2))*sqrt(pow(v[2].x,2) + pow(v[3].x,2))*sqrt(pow(v[2].x,2) + pow(v[3].x,2));
		return 1/r1 + 1/r2;
	}
	void getMatrix(){
		vector<int> v1(3);
		vector<int> v2(3);
		int a,b;
		for(int i = 0; i < vertexs; ++i){
			v1[0] = get<0>(m_Faces[i]);
			v1[1] = get<1>(m_Faces[i]);
			v1[2] = get<2>(m_Faces[i]);
			for(int j = i; j < vertexs; ++j){
				if(i != j){
					v2[0] = get<0>(m_Faces[j]);
					v2[1] = get<1>(m_Faces[j]);
					v2[2] = get<2>(m_Faces[j]);
					if(findOcurrence(v1,v2,a,b)){
						double r = GetWeight(v1,v2,a,b);
						m_EigenMatrix[i][j] = m_EigenMatrix[j][i] = r/2;
					}
				}
			}
		}
	}
};

main(){
	GetMatrix A;
	A.readOFF("aaa.off");
	A.printOFF();
	A.getMatrix();
	return 0;
}
/*
if (a == 0)
	cout << get<0>(m_Faces[i]);
else if (a == 1)
	cout << get<1>(m_Faces[i]);
else
	cout << get<2>(m_Faces[i]);
cout << " ";
if (b == 0)
	cout << get<0>(m_Faces[j]);
else if (b == 1)
	cout << get<1>(m_Faces[j]);
else
	cout << get<2>(m_Faces[j]);
cout << endl;
// generate sparse matrix
sp_mat A = sprandu<sp_mat>(1000, 1000, 0.1);
sp_mat B = A.t()*A;

vec eigval;
mat eigvec;

eigs_sym(eigval, eigvec, B, 5);  // find 5 eigenvalues/eigenvectors
*/
