#include <bits/stdc++.h>
#include "TicketCancellation.h"

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

bool foundMatch(ChosenMovie& m1,ChosenMovie& m2)
{
    if(m1.email!=m2.email || m1.userName!=m2.userName || m1.showTitle!=m2.showTitle
            || m1.showDate!=m2.showDate || m1.showTime!=m2.showTime)return false;
    return true;
}

void cancelTicket(string email,string userName)
{
    system("cls");
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

    ifstream inputFile2("BookingList.txt");

    ChosenMovie chosenMovie ;
    chosenMovie.email=email;
    chosenMovie.userName=userName;
    cout<<"Enter the following info for cancellation"<<endl;
    cout<<"Enter serial number: ";
    cin>>chosenMovie.serialNum;
    cout<<"Enter time slot: ";
    cin>>chosenMovie.serialSlot;
    chosenMovie.showDate=movieList[chosenMovie.serialNum-'1'].date;
    chosenMovie.showTitle=movieList[chosenMovie.serialNum-'1'].title;
    chosenMovie.showTime=movieList[chosenMovie.serialNum-'1'].timeSlots[chosenMovie.serialSlot-'1'];

    vector<ChosenMovie>movies;
    int foundBooking=-1,lineNum=0;
    while(getline(inputFile2,line))
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
        if(foundMatch(m,chosenMovie))foundBooking=lineNum;
        movies.push_back(m);
        lineNum++;
    }

    while(true)
    {
        if(foundBooking!=-1)break;
        cout<<"Could not find your booking record. Please try again."<<endl;
        cout<<"Enter serial number: ";
        cin>>chosenMovie.serialNum;
        cout<<"Enter time slot: ";
        cin>>chosenMovie.serialSlot;
        chosenMovie.showDate=movieList[chosenMovie.serialNum-'1'].date;
        chosenMovie.showTitle=movieList[chosenMovie.serialNum-'1'].title;
        chosenMovie.showTime=movieList[chosenMovie.serialNum-'1'].timeSlots[chosenMovie.serialSlot-'1'];

        for(int i=0; i<movies.size(); i++)
        {
            if(foundMatch(movies[i],chosenMovie))
            {
                foundBooking=i;
                break;
            }
        }
    }
    for(int i=0;i<movies[foundBooking].seats.size();i++){
        chosenMovie.seats.push_back(movies[foundBooking].seats[i]);
    }

    /*for(int i=0;i<chosenMovie.seats.size();i++){
        cout<<chosenMovie.seats[i]<<" ";
    }*/

    vector<ChosenMovie>::iterator it=movies.begin()+foundBooking;
    movies.erase(it);

    inputFile2.close();

    string allInfo[132],seatArr[10][10];
    ifstream inputFile3("Seats.txt");
    string temp;

    int pos=0,check=0,check2=0,i=0,k=0,z=0;
    for(i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            seatArr[i][j]="";
        }
    }
    i=0;
    while(getline(inputFile3,temp))
    {
        if(temp.size()==2 && temp[0]==chosenMovie.serialNum && temp[1]==chosenMovie.serialSlot)
        {
            check=1;
        }
        if(temp.size()>2 && check && !check2)
        {
            for(int j=0; j<temp.size(); j++)
            {
                if(temp[j]!=' ')
                {
                    seatArr[i][k]+=temp[j];
                }
                else k++;
            }
            i++;
            k=0;
            if(i>=10)check2=1;
        }
        if(!check)pos++;
        allInfo[z++]=temp;
    }
    inputFile3.close();

    cout<<endl;
    /*for(i=0;i<10;i++){
        for(int j=0;j<10;j++){
            cout<<seatArr[i][j]<<" ";
        }
        cout<<endl;
    }*/
    for(i=0; i<chosenMovie.seats.size(); i++)
    {
        //seatArr[chosenMovie.seats[i][0]-'A'][chosenMovie.seats[i][1]-'1'].clear();
        seatArr[chosenMovie.seats[i][0]-'A'][chosenMovie.seats[i][1]-'1']=chosenMovie.seats[i];
    }
    /*for(i=0;i<10;i++){
        for(int j=0;j<10;j++){
            cout<<seatArr[i][j]<<" ";
        }
        cout<<endl;
    }*/

    ofstream outputFile("Seats.txt");
    for(i=0; i<132; i++)
    {
        if(i>pos && i<=pos+10)
        {
            for(int j=0; j<10; j++)
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
    outputFile.close();
    ofstream outputFile2("BookingList.txt");
    for(int i=0; i<movies.size(); i++)
    {
        outputFile2<<movies[i].email<<","<<movies[i].userName<<","<<movies[i].showTitle<<","
                   <<movies[i].showDate<<","<<movies[i].showTime<<",";
        for(int j=0; j<movies[i].seats.size(); j++)
        {
            outputFile2<<movies[i].seats[j];
            if(j!=movies[i].seats.size()-1)outputFile2<<",";
        }
        outputFile2<<"\n";
    }
    outputFile2.close();

    cout<<"Ticket canceled successfully!"<<endl;
    this_thread::sleep_for(chrono::seconds(2));
    char x;
    cout<<endl<<"Enter any key to return: ";
    cin>>x;

}
