#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main()
{
    //using open function
    /*ofstream out;
    out.open("first.txt");
    out<<"This is me\n";
    out<<"This is also me";
    out.close();*/

    ifstream in;
    string st;
    in.open("first.txt");
    //getline(in,st);

    //keeping reading until end of file is reached
    while(in.eof()==0){
        getline(in,st);
        cout<<st<<endl;
    }

    return 0;
}
