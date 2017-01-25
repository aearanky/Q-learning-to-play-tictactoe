//Using a static vector
#include <iostream>
#include <vector>

using namespace std;

int main ()
{
  vector< vector<int> > Qmatrix ;
  int n = 4;
  std::vector< std::vector<int> > vec(n, std::vector<int>(n));

	for (int i = 0; i < n; i++) 
  		for (int j = 0; j < n; j++) 
    		(vec[i])[j] = i*n + j;

	for (int i = 0; i < n; i++) 
  		for (int j = 0; j < n; j++) 
    		cout<<(vec[i])[j]<<endl;
}
