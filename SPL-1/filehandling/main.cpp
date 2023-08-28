#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string st="Nandan";
    string st2;
    //opening files using constructor and writing it
    //ofstream out("first.txt");//write operation
    //out<<st;

    //Opening files using constructor and reading it
    ifstream in("first.txt");//Read operation
    //in>>st2;
    getline(in,st2);//to read the entire line
    cout<<st2<<endl;
    getline(in,st2);
    cout<<st2;

    return 0;
}
