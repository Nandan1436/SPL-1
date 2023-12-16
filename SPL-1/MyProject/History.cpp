#include<bits/stdc++.h>
#include "History.h"

using namespace std;

const string USERS_DIRECTORY = "Users\\";

struct movieHistory
{
    string title,date,time,hall;
    char serialNum,serialSlot;
    vector<string>seats;
    vector<string>genre;
};

void viewHistory(string email)
{
    ifstream file(USERS_DIRECTORY+email+".txt");
    for(int i=0;i<6;i++){
        string temp;
        getline(file,temp);
    }
    vector<movieHistory> movies;
    string snippet,line;
    while (getline(file, line))
    {
        movieHistory movie;
        stringstream rowString(line);

        getline(rowString, snippet, ',');
        movie.title = snippet;

        getline(rowString, snippet, ',');
        movie.date = snippet;

        getline(rowString, snippet, ',');
        movie.time = snippet;

        getline(rowString, snippet, ',');
        movie.serialNum = snippet[0];

        getline(rowString, snippet, ',');
        movie.serialSlot = snippet[0];

        getline(rowString, snippet, ',');
        movie.hall = snippet;

        getline(rowString, snippet, ',');
        stringstream seats(snippet);
        while (getline(seats, snippet, ';'))
        {
            movie.seats.push_back(snippet);
        }

        movie.genre.clear();
        while (getline(rowString, snippet, ','))
        {
            movie.genre.push_back(snippet);
        }

        movies.push_back(movie);
    }
    file.close();

    cout<<"\t\t\t\t\t*****USER HISTORY*****"<<endl;
    cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<left<<setw(10)<<"NUMBER"<<setw(40)<<"TITLE"<<setw(10)<<"DATE"<<setw(15)<<"TIME"<<setw(15)<<"Hall NO."<<setw(15)<<"SEATS"<<endl;
    cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
    for(int i=movies.size()-1;i>=0;i--)
    {
        cout<<setw(10)<<movies.size()-i;
        cout<<setw(40)<<movies[i].title;
        cout<<setw(10)<<movies[i].date;
        cout<<setw(15)<<movies[i].time;
        cout<<setw(15)<<movies[i].hall;
        for(int j=0;j<movies[i].seats.size();j++){
            cout<<movies[i].seats[j];
            if(j!=movies[i].seats.size()-1)cout<<", ";
        }
        cout<<endl;

    }
    cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;

    file.close();
    char ch;
    cout<<"Press any key to go back: ";
    cin>>ch;
    return;
}
