#include<bits/stdc++.h>
#include <conio.h>
#include "UserMenu.h"
#include "MovieSchedule.h"
#include "Food.h"
#include "MainMenu.h"

using namespace std;

void UserMenu(string email,string userName)
{
    system("cls");
    cout<<"Welcome, "<<userName<<"!"<<endl<<endl;
    while(true)
    {
        char input;
        cout<<"USER MENU"<<endl;
        cout<<"1.Book a ticket"<<endl;
        cout<<"2.View Food and Drinks available in the cinema"<<endl;
        cout<<"3.Log out"<<endl;
        cout<<"Select a number: ";
        input=getch();
        while(input>'3' && input<'1')
        {
            cout<<"Incorrect input!Please try again."<<endl;
            cout<<"Select a number: ";
            input=getch();
        }
        if(input=='1')
        {
            movieSchedule(email,userName);
        }
        else if(input=='2')
        {
            food();
        }
        else
        {
            system("cls");
            return;
        }
        system("cls");
    }

}
