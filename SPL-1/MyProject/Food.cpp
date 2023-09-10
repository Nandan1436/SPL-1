#include <bits/stdc++.h>
#include <conio.h>
#include "UserMenu.h"
#include "Food.h"

using namespace std;

void food()
{
    system("cls");

    cout<<left<<setw(30)<<"ITEM"<<setw(10)<<"Price in Taka"<<endl;
    cout<<"--------------------------------------------"<<endl;

    ifstream file("FoodAndDrink.txt");
    string line;
    while(getline(file,line))
    {
        string item,price,temp;
        stringstream rowString(line);
        getline(rowString,temp,',');
        item=temp;
        getline(rowString,temp,',');
        price=temp;
        cout<<setw(33)<<item<<setw(10)<<price<<endl;

    }
    cout<<"--------------------------------------------"<<endl;
    file.close();
    cout<<endl;
    cout<<"Press any key to return to User Menu."<<endl;
    char input;
    input=getch();
    return;

}
