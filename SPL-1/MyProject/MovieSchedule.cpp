#include <bits/stdc++.h>
#include "MovieSchedule.h"
#include "movieDetails.h"

using namespace std;

struct Movie
{
    string date;
    string day;
    string title;
    vector<string>timeSlots;
};

struct ChosenMovie
{
    string email;
    string userName;
    string showTitle;
    string showDate;
    string showTime;
    char serialNum;
    char serialSlot;
    vector<string>seats;
};

void bookTicket(ChosenMovie& chosenMovie);

void movieSchedule(string email,string userName)
{
    system("cls");

    while(true)
    {
        ifstream inputFile("MovieList.txt");
        if(!inputFile.is_open())
        {
            cout<<"Error opening file!"<<endl;
            exit(0);
        }

        cout<<"MOVIE SCHEDULE"<<endl<<endl;
        cout<<"--------------------------------------------------------------------------------------------------"<<endl;
        cout<<left<<setw(15)<<"SERIAL NO."<<setw(15)<<"Hall NO."<<setw(10)<<"DATE"<<setw(15)<<"DAY"<<setw(40)<<"TITLE"<<setw(10)<<"TIME SLOTS"<<endl;
        cout<<"--------------------------------------------------------------------------------------------------"<<endl;

        vector<Movie>movieList;
        string line,snippet;
        while(getline(inputFile,line))
        {
            Movie movie;
            stringstream rowString(line);

            getline(rowString,snippet,',');
            movie.date=snippet;

            getline(rowString,snippet,',');
            movie.day=snippet;

            getline(rowString,snippet,',');
            movie.title=snippet;

            while(getline(rowString,snippet,','))
            {
                movie.timeSlots.push_back(snippet);
            }

            movieList.push_back(movie);
        }

        inputFile.close();

        for(int i=0; i<movieList.size(); i++)
        {
            cout<<setw(15)<<i+1;
            cout<<setw(10)<<movieList[i].date;
            cout<<setw(15)<<movieList[i].day;
            cout<<setw(32)<<movieList[i].title;
            for(int j=0; j<movieList[i].timeSlots.size(); j++)
            {
                cout<<j+1<<". "<<movieList[i].timeSlots[j]<<"   ";
            }
            cout<<endl;
        }
        cout<<"--------------------------------------------------------------------------------------------------"<<endl;
        cout<<endl;
        cout<<"**Press 'd' to view movie details"<<endl;
        cout<<"**Press 't' to choose serial no. and time slot of show to watch"<<endl;
        cout<<"**Press 'x' to return to User Menu"<<endl;
        char x;
        cout<<"Choose: ";
        cin>>x;
        while(x!='d' && x!='t' && x!='x')
        {
            cout<<"Please press any of the characters mentioned above: "<<endl;
            cin>>x;
        }
        if(x=='d')
        {
            movieDetails();
        }
        else if(x=='x')
        {
            return;
        }
        else
        {
            ChosenMovie chosenMovie ;
            chosenMovie.email=email;
            chosenMovie.userName=userName;
            cout<<"Enter serial number: ";
            cin>>chosenMovie.serialNum;
            cout<<"Enter time slot: ";
            cin>>chosenMovie.serialSlot;
            chosenMovie.showDate=movieList[chosenMovie.serialNum-'1'].date;
            chosenMovie.showTitle=movieList[chosenMovie.serialNum-'1'].title;
            chosenMovie.showTime=movieList[chosenMovie.serialNum-'1'].timeSlots[chosenMovie.serialSlot-'1'];
            bookTicket(chosenMovie);
            return;
        }
        system("cls");
    }

}

void printReceipt(const ChosenMovie& chosenMovie,double total,double pay)
{
    system("cls");
    cout<<"Booking successful!"<<endl<<endl;
    cout<<"BOOKING DETAILS"<<endl;
    cout<<"User Name: "<<chosenMovie.userName<<endl;
    cout<<"Email: "<<chosenMovie.email<<endl;
    cout<<"Movie Title: "<<chosenMovie.showTitle<<endl;
    cout<<"Show Date: "<<chosenMovie.showDate<<endl;
    cout<<"Show Time: "<<chosenMovie.showTime<<endl;
    cout<<"Seats booked: ";
    for(int i=0; i<chosenMovie.seats.size(); i++)
    {
        cout<<chosenMovie.seats[i]<<" ";
    }
    cout<<endl;
    cout<<"Total cost: "<<total<<endl;
    cout<<"Amount paid: "<<pay<<endl;
    cout<<"Change: "<<pay-total<<endl<<endl;
    cout<<"Enter any key to return to User Menu"<<endl;
    char ch;
    cin>>ch;
    return;

}

void makePayment(ChosenMovie& chosenMovie)
{
    system("cls");
    double total,pay;
    total=chosenMovie.seats.size()*500;
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
    printReceipt(chosenMovie,total,pay);

}

void recordBooking(ChosenMovie& chosenMovie)
{
    system("cls");
    vector<ChosenMovie>movies;
    ifstream file("BookingList.txt");
    string line,snippet;
    while(getline(file,line))
    {
        ChosenMovie m;
        stringstream rowString(line);

        getline(rowString,snippet,',');
        m.email=snippet;
        getline(rowString,snippet,',');
        m.userName=snippet;
        getline(rowString,snippet,',');
        m.showTitle=snippet;
        getline(rowString,snippet,',');
        m.showDate=snippet;
        getline(rowString,snippet,',');
        m.showTime=snippet;
        int x=0;
        while(getline(rowString,snippet,','))
        {
            m.seats.push_back(snippet);
        }
        movies.push_back(m);
    }
    cout<<"Info taken"<<endl;
    movies.push_back(chosenMovie);
    file.close();
    ofstream recordfile("BookingList.txt");
    for(int i=0; i<movies.size(); i++)
    {
        recordfile<<movies[i].email<<","<<movies[i].userName<<","<<movies[i].showTitle<<","
                  <<movies[i].showDate<<","<<movies[i].showTime<<",";
        for(int j=0; j<movies[i].seats.size(); j++)
        {
            recordfile<<movies[i].seats[j];
            if(j!=movies[i].seats.size()-1)recordfile<<",";
        }
        recordfile<<"\n";
    }
    recordfile.close();
}

void bookTicket(ChosenMovie& chosenMovie)
{
    system("cls");
    ifstream inputFile("Seats.txt");

    int i=0,j=0,k=0,seatsAvailable=0;
    string line;

    while(getline(inputFile,line))
    {
        if(line.size()==2 && line[0]==chosenMovie.serialNum && line[1]==chosenMovie.serialSlot)
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
        chosenMovie.seats.push_back(seats[i]);
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
        if(line.size()==2 && line[0]==chosenMovie.serialNum && line[1]==chosenMovie.serialSlot)
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
    cout<<"Processing your seat selection..."<<endl;
    recordBooking(chosenMovie);

    cout<<"Taking you to payment...";
    this_thread::sleep_for(chrono::seconds(2));
    makePayment(chosenMovie);
    inputFile.close();
    outputFile.close();
}
