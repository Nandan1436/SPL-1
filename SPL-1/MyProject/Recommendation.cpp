#include<bits/stdc++.h>
#include "Recommendation.h"

using namespace std;
const string USERS_DIRECTORY = "Users\\";

struct movieHistory
{
    string title,date,time,hall;
    char serialNum,serialSlot;
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
    currentMovie temp;
    while(getline(details,line))
    {
        if(line[0]=='1'){
            temp.title=line.substr(2);
        }
        else if(line[0]=='2'){
            stringstream genres(line);
            string val;
            genres>>val;
            string snippet;
            while(getline(genres,snippet,',')){
                snippet.erase(0, snippet.find_first_not_of(" "));
                snippet.erase(snippet.find_last_not_of(" ") + 1);
                temp.genre.push_back(snippet);
            }
            movies.push_back(temp);
        }
    }
    details.close();

    return movies;
}

set<string>recommedMovies(map<string,int>freq,vector<currentMovie>allGenres)
{
    vector<string>topGenres;
    set<string>topMovies;
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
                topMovies.insert(allGenres[i].title);
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

    set<string>topMovies=recommedMovies(freq,allGenres);
    if(topMovies.size()!=0){
        cout<<"Recommended movies for you: "<<endl;
        for(auto it=topMovies.begin();it!=topMovies.end();it++){
            cout<<*it<<endl;
        }
        cout<<endl;
    }
}
