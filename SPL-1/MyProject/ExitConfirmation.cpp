#include <bits/stdc++.h>
#include "MainMenu.h"
#include "UserMenu.h"
#include "ExitConfirmation.h"

using namespace std;

bool exitConfirmation()
{
    system("cls");
    char choice;

    cout<<"Are you sure you want to quit the program?"<<endl;
    cout<<"YES(y) or NO(n)"<<endl;
    cin>>choice;
    if(choice=='Y'||choice=='y')
    {
        return false;
    }
    else
    {
        system("cls");
        return true;
    }
}
