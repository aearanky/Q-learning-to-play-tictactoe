// inserting into a vector
#include <iostream>
#include <vector>

using namespace std;

int main ()
{
  vector<int> myvector (3,100); //3 elements with value 100
  vector<int>::iterator it;

  it = myvector.begin();
  it = myvector.insert ( it , 200 ); //insert at first location 200 and then we have 200 100 100 100

  myvector.insert (it,2,300); //insert 2 elements of 300 at the beginning and then we have 300 300 200 100 100 100

  // "it" no longer valid, get a new one:
  it = myvector.begin();

  vector<int> anothervector (2,400); //new vector with 2 elements with value 400
  myvector.insert (it+2,anothervector.begin(),anothervector.end());//start after the first 2 elements which are 300 and then we have 300 300 400 400 200 100 100 100

  int myarray [] = { 501,502,503 };
  myvector.insert (myvector.begin(), myarray, myarray+3); //First 3 elements of myvector are filled with 501,502,503 so we have 501 502 503 300 300 400 400 200 100 100 100

  cout << "myvector contains:";
  for (it=myvector.begin(); it<myvector.end(); it++)
    cout << ' ' << *it;
  cout << '\n';
	
  return 0;
}
