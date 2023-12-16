#include <bits/stdc++.h>
#include "MainMenu.h"
#include "UserLogIn.h"
#include "UserSignUp.h"
#include "MovieSchedule.h"
#include "Admin.h"
#include "UserMenu.h"
#include "ExitConfirmation.h"
#include "History.h"

using namespace std;

void mainMenu()
{
    bool quit=true;
    char choice;
    while(quit)
    {
        cout<<"WELCOME"<<endl;
        cout<<"1.Login"<<endl;
        cout<<"2.Sign Up"<<endl;
        cout<<"3.Exit"<<endl;
        cout<<"Press '1' to login in if you already have an account."<<endl;
        cout<<"Press '2' to create a new account."<<endl;
        cout<<"Press '3' to exit."<<endl;
        cout<<"Enter choice: ";
        cin>>choice;
        while(choice>'3' || choice<'1')
        {
            cout<<"Wrong key entered. Please try again"<<endl;
            cout<<"\nEnter choice: ";
            cin>>choice;
        }
        if(choice=='1')userLogIn();
        else if(choice=='2')userSignUp();
        else {
            if(!exitConfirmation())quit=false;
        }
    }
}
