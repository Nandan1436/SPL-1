#include <bits/stdc++.h>
#include "TicketCancellation.h"
#include <chrono>
#include <ctime>

const string USERS_DIRECTORY = "Users\\";
struct userInfo
{
    string fullName;
    string email;
    string password;
    string dateOfBirth;
    string userName;
};

struct ChosenMovie
{
    string email,userName,showTitle,showDate,showTime,hall;
    char serialNum;
    char serialSlot;
    vector<string>seats,genres;
};

bool TimeDifference(string date,string time) {
    auto currentTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    tm* localTime = localtime(&currentTime);

    ostringstream oss;
    oss << put_time(localTime, "%I:%M %p");

    string currentTimeString = oss.str();

    ostringstream dateOss;
    dateOss << put_time(localTime, "%d/%m/%y");

    string currentDate = dateOss.str();

    int currTime,showTime;
    currTime=(currentTimeString[1]-'0')+10*(currentTimeString[0]-'0');
    if(currentTimeString.substr(6)=="pm")currTime+=12;
    currTime*=3600;
    currTime+=((currentTimeString[4]-'0')+(currentTimeString[3])*10);

    showTime=(time[1]-'0')+10*(time[0]-'0');
    if(time.substr(6)=="pm")currTime+=12;
    showTime*=3600;
    currTime+=((time[4]-'0')+(time[3])*10);

    if(currentDate<date || currTime+5*3600<showTime)return true;
    return false;
}

bool foundMatch(ChosenMovie& m1,ChosenMovie& m2)
{
    if(m1.email!=m2.email || m1.userName!=m2.userName || m1.showTitle!=m2.showTitle
            || m1.showDate!=m2.showDate || m1.showTime!=m2.showTime)return false;
    return true;
}

void cancelTicket(string email,string userName)
{
    system("cls");
    userInfo user;

    ifstream file(USERS_DIRECTORY+email+".txt");
    for (int j = 0; j < 5; ++j) {
        file.ignore(numeric_limits<streamsize>::max(), ':');
        if(j==0)file>>user.fullName;
        else if(j==1)file>>user.userName;
        else if(j==2)file>>user.dateOfBirth;
        else if(j==3)file>>user.email;
        else if(j==4)file>>user.password;
    }
    vector<ChosenMovie> userBooking;
    string snippet,line;
    getline(file,line);
    getline(file,line);
    while (getline(file, line))
    {
        ChosenMovie movie;
        stringstream rowString(line);

        getline(rowString, snippet, ',');
        movie.showTitle = snippet;

        getline(rowString, snippet, ',');
        movie.showDate = snippet;

        getline(rowString, snippet, ',');
        movie.showTime = snippet;

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

        movie.genres.clear();
        while (getline(rowString, snippet, ','))
        {
            movie.genres.push_back(snippet);
        }

        userBooking.push_back(movie);
    }
    file.close();

    cout<<"\t\t\t\t\t*****USER HISTORY*****"<<endl;
    cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<left<<setw(10)<<"NUMBER"<<setw(40)<<"TITLE"<<setw(10)<<"DATE"<<setw(15)<<"TIME"<<setw(15)<<"Hall NO."<<setw(15)<<"SEATS"<<endl;
    cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
    for(int i=userBooking.size()-1;i>=0;i--)
    {
        cout<<setw(10)<<userBooking.size()-i;
        cout<<setw(40)<<userBooking[i].showTitle;
        cout<<setw(10)<<userBooking[i].showDate;
        cout<<setw(15)<<userBooking[i].showTime;
        cout<<setw(15)<<userBooking[i].hall;
        for(int j=0;j<userBooking[i].seats.size();j++){
            cout<<userBooking[i].seats[j];
            if(j!=userBooking[i].seats.size()-1)cout<<", ";
        }
        cout<<endl;

    }
    cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;

    file.close();

    ifstream inputFile2("BookingList.txt");

    ChosenMovie chosenMovie ;
    chosenMovie.email=email;
    chosenMovie.userName=userName;

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
        while(getline(rowString,snippet,','))
        {
            m.seats.push_back(snippet);
        }
        if(foundMatch(m,chosenMovie))foundBooking=lineNum;
        movies.push_back(m);
        lineNum++;
    }
    int bookingNum;
    while(true)
    {

        cout<<"Enter booking number to cancel: ";
        cin>>bookingNum;
        bookingNum=userBooking.size()-bookingNum;
        chosenMovie.showTitle=userBooking[bookingNum].showTitle;
        chosenMovie.showDate=userBooking[bookingNum].showDate;
        chosenMovie.showTime=userBooking[bookingNum].showTime;
        chosenMovie.hall=userBooking[bookingNum].hall;
        chosenMovie.serialNum=userBooking[bookingNum].serialNum;
        chosenMovie.serialSlot=userBooking[bookingNum].serialSlot;
        for(int i=0;i<userBooking[bookingNum].seats.size();i++){
            chosenMovie.seats.push_back(userBooking[bookingNum].seats[i]);
        }
        for(int i=0;i<userBooking[bookingNum].genres.size();i++){
            chosenMovie.genres.push_back(userBooking[bookingNum].genres[i]);
        }
        if(!TimeDifference(chosenMovie.showDate,chosenMovie.showTime)){
            cout<<"This booking cannot be canceled. Please try another."<<endl;
            continue;
        }
        for(int i=0; i<movies.size(); i++)
        {
            if(foundMatch(movies[i],chosenMovie))
            {
                foundBooking=i;
                break;
            }
        }
        if(foundBooking!=-1)break;
        cout<<"Could not find your booking record. Please try again."<<endl;
    }
    for(int i=0;i<movies[foundBooking].seats.size();i++){
        chosenMovie.seats.push_back(movies[foundBooking].seats[i]);
    }

    vector<ChosenMovie>::iterator it=movies.begin()+foundBooking;
    movies.erase(it);
    it=userBooking.begin()+bookingNum;
    userBooking.erase(it);

    inputFile2.close();

    string seatArr[10][10];
    vector<string>allInfo;
    ifstream inputFile3("Seats.txt");
    string temp;

    int pos=0,check=0,check2=0,i=0,k=0;
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
        allInfo.push_back(temp);
    }
    inputFile3.close();

    cout<<endl;

    for(i=0; i<chosenMovie.seats.size(); i++)
    {
        seatArr[chosenMovie.seats[i][0]-'A'][chosenMovie.seats[i][1]-'1']=chosenMovie.seats[i];
    }

    ofstream outputFile("Seats.txt");
    for(i=0; i<allInfo.size(); i++)
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

    ofstream userFile(USERS_DIRECTORY+email+".txt");
    userFile << "Full Name: " << user.fullName << endl;
    userFile << "User Name: " << user.userName << endl;
    userFile << "Date of Birth: " << user.dateOfBirth << endl;
    userFile << "Email: " << user.email << endl;
    userFile << "Hashed Password: " << user.password << endl;
    userFile << "History:" << endl;

    for(int k=0;k<userBooking.size();k++){
        userFile<<userBooking[k].showTitle<<","<<userBooking[k].showDate<<","<<userBooking[k].showTime<<","<<userBooking[k].serialNum<<","<<
        userBooking[k].serialSlot<<","<<userBooking[k].hall<<",";
        for(int i=0;i<userBooking[k].seats.size();i++){
            userFile<<userBooking[k].seats[i];
            if(i!=userBooking[k].seats.size()-1)userFile<<";";
            else userFile<<",";
        }
        for(int i=0;i<userBooking[k].genres.size();i++){
            userFile<<userBooking[k].genres[i];
            if(i!=userBooking[k].genres.size()-1)userFile<<",";
        }
        userFile<<"\n";
    }

    cout<<"Please enter phone number on which you want to receive the refund: ";
    string phone;
    cin>>phone;
    cout<<"Refund sent"<<endl;
    this_thread::sleep_for(chrono::seconds(2));
    cout<<"Ticket canceled successfully!"<<endl;
    char x;
    cout<<endl<<"Enter any key to return: ";
    cin>>x;

}
