#include<bits/stdc++.h>
#include <conio.h>
#include "UserMenu.h"
#include "MovieSchedule.h"
#include "Food.h"
#include "MainMenu.h"
#include "TicketCancellation.h"

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
        cout<<"3.Cancel a Ticket"<<endl;
        cout<<"4.Log out"<<endl;
        cout<<"Select a number: ";
        cin>>input;
        while(input>'4' && input<'1')
        {
            cout<<"Incorrect input!Please try again."<<endl;
            cout<<"Select a number: ";
            cin>>input;
        }
        if(input=='1')
        {
            movieSchedule(email,userName);
        }
        else if(input=='2')
        {
            food();
        }
        else if(input=='3')
        {
            cancelTicket(email,userName);
        }
        else
        {
            system("cls");
            return;
        }
        system("cls");
    }

}
