#include <vector>
#include <cstdlib>
using namespace std;
class Board:public vector<vector<bool> >{
public:
	int n;
	Board(int a):vector<vector<bool> >(a){
		n = a;
		for (vector<vector<bool> >::iterator i = this->begin(); i != this->end(); ++i){
			*i = vector<bool>();
			for (int j=0; j < a; j++){
				float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				i->push_back((0.3 > r));
			}
		}
	}
	bool getCell(int a, int b){
		if (a < 0 || a >= n) return false;
		if (b < 0 || b >= n) return false;
		return at(a)[b];
	}
};