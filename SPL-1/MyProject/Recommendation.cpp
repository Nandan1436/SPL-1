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
    for(int i=0;i<6;i++){
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

vector<currentMovie> getGenres()
{
    vector<currentMovie> movies;
    ifstream details("MovieDetails.txt");
    string line;
    while(getline(details,line))
    {
        currentMovie temp;
        if(line[0]=='1'){
            temp.title=line;
        }
        else if(line[0]=='2'){
            stringstream genres(line);
            string val;
            genres>>val;
            string snippet;
            while(getline(genres,snippet,',')){
                temp.genre.push_back(snippet);
            }
        }
    }
    details.close();

    return movies;
}

vector<string>recommedMovies(map<string,int>freq,vector<currentMovie>allGenres)
{
    vector<string>topMovies,topGenres;
    vector<pair<string,int>>sortedGenre(freq.begin(),freq.end());
    sort(sortedGenre.begin(), sortedGenre.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    for (int i=0;i<2 && i<sortedGenre.size();i++) {
        topGenres.push_back(sortedGenre[i].first);
    }

    for(int i=0;i<allGenres.size();i++){
        for(int j=0;j<allGenres[i].genre.size();j++){
            if(find(topGenres.begin(),topGenres.end(),allGenres[i].genre[j])!=topGenres.end()){
                topMovies.push_back(allGenres[i].genre[j]);
            }
        }
    }

    return topMovies;
}

void recommendation(string email)
{
    vector<movieHistory>movies=UserHistory(email);
    map<string,int>freq=findFreq(movies);
    vector<currentMovie>allGenres=getGenres();

    vector<string>topMovies=recommedMovies(freq,allGenres);
    if(topMovies.size()!=0){
        cout<<"Recommended movies for you: "<<endl;
        for(int i=0;i<topMovies.size();i++){
            cout<<topMovies[i]<<endl;
        }
    }

}


