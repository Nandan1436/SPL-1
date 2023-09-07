#include <bits/stdc++.h>
#include <conio.h>
#include "MainMenu.h"
#include "UserLogIn.h"
#include "UserSignUp.h"
#include "MovieSchedule.h"
#include "Admin.h"
#include "ExitConfirmation.h"

using namespace std;

void mainMenu()
{
    char choice;
    cout<<"WELCOME"<<endl;
    cout<<"1.Admin"<<endl;
    cout<<"2.User"<<endl;
    cout<<"3.Quit"<<endl;
    choice=getch();

    while(choice>'3' || choice<'1')
    {
        cout<<"Wrong key entered. Please try again"<<endl;
        cout<<"\nEnter choice: ";
        choice=getch();
    }

    if(choice=='1')
    {
        Admin();
    }
    else if(choice=='2')
    {
        system("CLS");
        cout<<"1.Login"<<endl;
        cout<<"2.Sign Up"<<endl;
        choice=getch();
        while(choice>'2' || choice<'1')
        {
            cout<<"Wrong key entered. Please try again"<<endl;
            cout<<"\nEnter choice: ";
            choice=getch();
        }
        if(choice=='1')userLogIn();
        else userSignUp();
    }
    else
    {
        exitConfirmation();
    }

}
