#include <iostream>
#include<fstream>

using namespace std;

int main()
{
    //Connecting our file with hout stream
    //ofstream hout("first.txt");

    //Creating a name string and filling it with string entered by the user
    //cout<<"Enter your name:";
    //string name;
    //cin>>name;
    //hout<<"My name is "+name;

    //hout.close();

    ifstream hin("first.txt");
    string content;
    getline(hin,content);
    cout<<"The content of this file is: "<<content;

    hin.close();
    return 0;
}
