#include <bits/stdc++.h>
#include <conio.h>
#include "MovieSchedule.h"
#include "movieDetails.h"

using namespace std;

struct Movie
{
    string date;
    string day;
    string title;
    vector<string> timeSlots;
};

void movieSchedule()
{
    system("CLS");

    ifstream inputFile("MovieList.txt");
    if(!inputFile.is_open())
    {
        cout<<"Error opening file!"<<endl;
        exit(0);
    }

    cout<<"MOVIE SCHEDULE"<<endl<<endl;
    cout<<"-----------------------------------------------------------------------------------"<<endl;
    cout<<left<<setw(10)<<"DATE"<<setw(15)<<"DAY"<<setw(40)<<"TITLE"<<setw(10)<<"TIME SLOTS"<<endl;
    cout<<"-----------------------------------------------------------------------------------"<<endl;

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

    for(int i=0;i<movieList.size();i++){
        cout<<setw(10)<<movieList[i].date;
        cout<<setw(15)<<movieList[i].day;
        cout<<setw(32)<<movieList[i].title;
        for(int j=0;j<movieList[i].timeSlots.size();j++){
            cout<<j+1<<". "<<movieList[i].timeSlots[j]<<"   ";
        }
        cout<<endl;
    }
    cout<<"-----------------------------------------------------------------------------------"<<endl;
    cout<<"To check the movie details, press d"<<endl;
    char x;
    x=getch();
    if(x=='d')movieDetails();
    else exit(0);

}
