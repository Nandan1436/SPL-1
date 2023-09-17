#include<bits/stdc++.h>
#include <conio.h>
#include "TicketBooking.h"
#include "MovieSchedule.h"
#include "UserMenu.h"

using namespace std;

void printReceipt(string email,string userName,double total,double pay)
{
    system("cls");
    cout<<"Booking successful!"<<endl<<endl;
    cout<<"BOOKING DETAILS"<<endl;
    cout<<"User Name: "<<userName<<endl;
    cout<<"Email: "<<email<<endl;
    cout<<"Amount paid: "<<pay<<endl;
    cout<<"Change: "<<pay-total<<endl<<endl;
    cout<<"Enter any key to return to User Menu";
    char ch;
    cin>>ch;
    return;

}

void makePayment(string email,string userName,int n)
{
    system("cls");
    double total,pay;
    total=n*500.00;
    cout<<"Total amount: "<<total<<endl;
    cout<<"Please pay the amount: "<<endl;
    cin>>pay;
    while(pay<total)
    {
        cout<<"Not enough paid, please pay "<<total<<": "<<endl;
        cin>>pay;
    }
    cout<<"Payment successful! Please wait for completion of ticket booking..."<<endl;
    this_thread::sleep_for(chrono::seconds(2));
    printReceipt(email,userName,total,pay);

}

void bookTicket(string email,string userName,char num,char slot)
{
    system("cls");
    ifstream inputFile("Seats.txt");

    int i=0,j=0,k=0,seatsAvailable=0;
    string line;

    while(getline(inputFile,line))
    {
        if(line.size()==2 && line[0]==num && line[1]==slot)
        {
            break;
        }
    }
    string seatArr[10][10];

    for(i=0; i<10; i++)
    {
        for(j=0; j<10; j++)
        {
            seatArr[i][j]="";
        }
    }
    i=0,k=0;
    while(getline(inputFile,line) && line.size()>2)
    {
        for(j=0; j<line.size(); j++)
        {
            if(line[j]!=' ')
            {
                seatArr[i][k]+=line[j];
            }
            else k++;
        }
        i++;
        k=0;
    }

    cout<<"-------------------------------------------------------------------"<<endl;
    cout<<"                     S   C   R   E   E   N                           "<<endl;
    cout<<"-------------------------------------------------------------------"<<endl;
    cout<<"-------------------------------------------------------------------"<<endl;

    for(i=0; i<10; i++)
    {
        for(j=0; j<10; j++)
        {
            //cout<<seatArr[i][j]<<"     ";
            if(seatArr[i][j]=="X")
            {
                cout << "\033[31m";
                cout<<left<<setw(7)<<seatArr[i][j];
                cout << "\033[0m";

            }
            else
            {
                cout << "\033[32m";
                cout<<left<<setw(7)<<seatArr[i][j];
                cout << "\033[0m";
                seatsAvailable++;
            }

        }
        cout<<endl;
        cout<<"-------------------------------------------------------------------"<<endl;
    }
    int numOfTickets,check=0;
    cout<<"Enter number of tickets to buy(Maximum 5): ";
    cin>>numOfTickets;
    while(!check)
    {
        if(numOfTickets>5)
        {
            cout<<"More than 5 tickets selected! Please enter correct number: ";
            cin>>numOfTickets;
        }
        else if(numOfTickets>seatsAvailable)
        {
            cout<<numOfTickets<<" seats are not available! Please enter correct number: ";
            cin>>numOfTickets;
        }
        else check=1;
    }

    string seats[numOfTickets],allInfo[132];
    for(i=0; i<numOfTickets; i++)
    {
        cout<<"Enter seat number: ";
        cin>>seats[i];
    }


    for(i=0; i<numOfTickets; i++)
    {
        int row=seats[i][0]-65,column=seats[i][1]-49;
        seatArr[row][column]="X";
    }
    inputFile.close();
    ifstream input("Seats.txt");

    int pos=0;
    check=0,i=0;
    while(getline(input,line))
    {
        if(line.size()==2 && line[0]==num && line[1]==slot)
        {
            check=1;
        }
        if(!check)pos++;
        allInfo[i++]=line;

    }

    input.close();
    k=0;
    ofstream outputFile("Seats.txt");
    for(i=0; i<132; i++)
    {
        if(i>pos && i<=pos+10)
        {
            for(j=0; j<10; j++)
            {
                outputFile<<seatArr[k][j]<<" ";
            }
            outputFile<<"\n";
            k++;
        }
        else
        {
            outputFile<<allInfo[i]<<"\n";
        }
    }
    cout<<"Processing your seat selection...";
    this_thread::sleep_for(chrono::seconds(2));
    makePayment(email,userName,numOfTickets);
    inputFile.close();
    outputFile.close();

}
