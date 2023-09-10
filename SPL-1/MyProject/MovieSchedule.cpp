#include <bits/stdc++.h>
#include <conio.h>
#include "MovieSchedule.h"
#include "movieDetails.h"
#include "TicketBooking.h"

using namespace std;

struct Movie
{
    string date;
    string day;
    string title;
    vector<string> timeSlots;
};

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
        cout<<left<<setw(15)<<"SERIAL NO."<<setw(10)<<"DATE"<<setw(15)<<"DAY"<<setw(40)<<"TITLE"<<setw(10)<<"TIME SLOTS"<<endl;
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
            char num,slot;
            cout<<"Enter serial number: ";
            cin>>num;
            cout<<"Enter time slot: ";
            cin>>slot;
            bookTicket(email,userName,num,slot);
            return;
        }
        system("cls");
    }


}
