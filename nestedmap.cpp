#include <iostream>
#include <map>
#include <string>
 
using namespace std;
 
   typedef map<string, double> Map1; //define maps and their data type
   typedef map<string, Map1> Map2;
   typedef map<string, Map2> Map3;
   Map3 m;
 
//<!--more-->
void print(){
map<string, Map2>::iterator it_out; //outermost map
map<string, Map1>::iterator it_mid; 
map<string, double>::iterator it_in; //innermost map
 
	for(it_out = m.begin(); it_out !=m.end(); it_out++)
	{
		cout<<"{"<<(*it_out).first<<",{"; //output 1st element of Map3
		for(it_mid=(*it_out).second.begin(); it_mid !=(*it_out).second.end(); it_mid++)//second represents the value part of the key, 																													value pair
		{
			cout<<(*it_mid).first<<",";//output first element of Map2  
			for(it_in=(*it_mid).second.begin(); it_in !=(*it_mid).second.end(); it_in++)
			{
				cout<< "{"<<(*it_in).first << ","<< (*it_in).second <<"}}"<<endl; //output the 1st and 2nd elements of Map1
			}
		}
	}
}       

int main(int argc, char* argv[]){
//.insert initialize the map.
        m.insert (make_pair("el", Map2())); //States 
        m["el"].insert (make_pair("nom", Map1()));
        m["el"]["nom"].insert (make_pair("Et", 25.0));
        m["el"]["nom"].insert (make_pair("Pt", 23.20));
        m["el"]["nom"].insert (make_pair("Charge", -1));
 
        print();
 
return 0;
}
