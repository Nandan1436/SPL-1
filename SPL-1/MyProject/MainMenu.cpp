#include<bits/stdc++.h>
#include "MainMenu.h"
#include "UserLogIn.h"
#include "UserSignUp.h"
#include "MovieSchedule.h"
#include "Admin.h"
#include "ExitConfirmation.h"

using namespace std;

void mainMenu(){
    char choice;
    cout<<"Welcome"<<endl;
    cout<<"1.User Login"<<endl;
    cout<<"2.User Sign Up"<<endl;
    cout<<"3.Show movie schedule"<<endl;
    cout<<"4.Admin Login"<<endl;
    cout<<"5.Exit"<<endl;
    cout<<"Enter choice: ";
    cin>>choice;

    while(choice>'5' || choice<'1')
    {
        cout<<"Wrong key entered. Please try again"<<endl;
        cout<<"\nEnter choice: ";
        cin>>choice;
    }

    switch(choice){
    case '1':
        userLogIn();
        break;
    case '2':
        userSignUp();
        break;
    case '3':
        movieSchedule();
        break;
    case '4':
        Admin();
        break;
    case '5':
        exitConfirmation();
        break;
    }

}
