#include<bits/stdc++.h>
#include "UserMenu.h"
#include "MovieSchedule.h"
#include "Food.h"
#include "MainMenu.h"
#include "TicketCancellation.h"
#include "History.h"

using namespace std;

void UserMenu(string email,string userName)
{
    system("cls");
    while(true)
    {
        char input;
        cout<<"\t\t\t\t\t\t************************"<<endl;
        cout<<"\t\t\t\t\t\t   U S E R   M E N U"<<endl;
        cout<<"\t\t\t\t\t\t************************"<<endl<<endl;
        cout<<"Welcome, "<<userName<<"!"<<endl<<endl;
        cout<<"1.Book a ticket"<<endl;
        cout<<"2.View Food and Drinks available in the cinema"<<endl;
        cout<<"3.Cancel a Ticket"<<endl;
        cout<<"4.View history"<<endl;
        cout<<"5.Log out"<<endl;
        cout<<"Select a number: ";
        cin>>input;
        while(input>'5' && input<'1')
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
        else if(input=='4'){
            viewHistory(email);
        }
        else
        {
            system("cls");
            return;
        }
        system("cls");
    }

}
