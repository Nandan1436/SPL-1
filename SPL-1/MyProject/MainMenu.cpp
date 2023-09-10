#include <bits/stdc++.h>
#include <conio.h>
#include "MainMenu.h"
#include "UserLogIn.h"
#include "UserSignUp.h"
#include "MovieSchedule.h"
#include "Admin.h"
#include "ExitConfirmation.h"
#include "TicketBooking.h"

using namespace std;

void mainMenu()
{
    char choice;
    bool quit=true;
    while(quit)
    {
        cout<<"WELCOME"<<endl;
        cout<<"1.Admin"<<endl;
        cout<<"2.User"<<endl;
        cout<<"3.Quit"<<endl;
        cout<<"Enter choice: ";
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
            system("cls");
            cout<<"1.Login"<<endl;
            cout<<"2.Sign Up"<<endl;
            cout<<"Press '1' to login in if you already have an account."<<endl;
            cout<<"Press '2' to create a new account."<<endl;
            cout<<"Enter choice: ";
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
            quit=exitConfirmation();
        }
    }
}
