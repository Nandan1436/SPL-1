#include<bits/stdc++.h>
#include "Recommendation.h"

using namespace std;
const string USERS_DIRECTORY = "Users\\";

struct movieHistory
{
    string title,date,time,hall;
    char serialNum;
    char serialSlot;
    vector<string>seats;
    vector<string>genre;
};

struct currentMovie
{
    string title;
    vector<string>genre;
};

vector<movieHistory> UserHistory(string email)
{
    ifstream file(USERS_DIRECTORY+email+".txt");
    for(int i=0;i<5;i++){
        string temp;
        getline(file,temp);
    }
    vector<movieHistory>movies;
    string line,snippet;
    while(getline(file,line))
    {
        movieHistory movie;
        stringstream rowString(line);
        getline(rowString,snippet,',');
        movie.title=snippet;

        getline(rowString,snippet,',');
        movie.date=snippet;

        getline(rowString,snippet,',');
        movie.time=snippet;

        getline(rowString,snippet,',');
        movie.serialNum=snippet[0];

        getline(rowString,snippet,',');
        movie.serialSlot=snippet[0];

        getline(rowString,snippet,',');
        movie.hall=snippet;

        getline(rowString,snippet,',');
        movie.title=snippet;

        getline(rowString,snippet,',');
        stringstream seats(snippet);
        while(getline(seats,snippet,';')){
            movie.seats.push_back(snippet);
        }

        while(getline(rowString,snippet,','))
        {
            movie.genre.push_back(snippet);
        }

        movies.push_back(movie);
    }
    file.close();

    return movies;
}

map<string,int> findFreq(vector<movieHistory>& movies)
{
    map<string,int>freq;

    for(int i=0;i<movies.size();i++){
        for(int j=0;j<movies[i].genre.size();j++){
            freq[movies[i].genre[j]]++;
        }
    }

    return freq;
}



void recommendation(string email)
{
    vector<movieHistory>movies=UserHistory(email);
    map<string,int>freq=findFreq(movies);


}


