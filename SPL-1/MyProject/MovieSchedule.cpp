#include <bits/stdc++.h>
#include "MovieSchedule.h"
#include "movieDetails.h"
#include "Recommendation.h"

using namespace std;

const string USERS_DIRECTORY = "Users\\";

struct Movie
{
    string date;
    string day;
    string hall;
    string title;
    vector<string>timeSlots;
};

struct ChosenMovie
{
    string email,userName,showTitle,showDate,showTime,hall;
    char serialNum;
    char serialSlot;
    vector<string>seats,genres;
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
        cout<<"\t\t\t\t\t\t******************************"<<endl;
        cout<<"\t\t\t\t\t\t  M O V I E  S C H E D U L E"<<endl;
        cout<<"\t\t\t\t\t\t******************************"<<endl;
        cout<<"------------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<left<<setw(15)<<"SERIAL NO."<<setw(10)<<"DATE"<<setw(15)<<"DAY"<<setw(15)<<"Hall NO."<<setw(40)<<"TITLE"<<setw(10)<<"TIME SLOTS"<<endl;
        cout<<"------------------------------------------------------------------------------------------------------------------"<<endl;

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
            movie.hall=snippet;

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
            cout<<setw(15)<<movieList[i].hall;
            cout<<setw(32)<<movieList[i].title;
            for(int j=0; j<movieList[i].timeSlots.size(); j++)
            {
                cout<<j+1<<". "<<movieList[i].timeSlots[j]<<"   ";
            }
            cout<<endl;
        }
        cout<<"------------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<endl;
        recommendation(email);

        cout<<"Ticket price for hall-1: 450"<<endl;
        cout<<"Ticket price for hall-2: 550"<<endl;

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
            chosenMovie.hall=movieList[chosenMovie.serialNum-'1'].hall;
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
    cout<<"Hall number: "<<chosenMovie.hall<<endl;
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
    total=chosenMovie.seats.size();
    if(chosenMovie.hall=="hall-1")total*=450;
    else total*=550;
    cout<<"Total amount: "<<total<<endl;
    cout<<"Please pay the amount: "<<endl;
    cin>>pay;
    while(pay<total)
    {
        cout<<"Not enough paid, please pay "<<total<<": "<<endl;
        cin>>pay;
    }
    cout<<"Payment successful! Press any key to continue..."<<endl;
    char ch;
    cin>>ch;
    printReceipt(chosenMovie,total,pay);

}

void recordBooking(ChosenMovie& chosenMovie)
{
    system("cls");
    ofstream recordfile("BookingList.txt",std::ios::app);
    recordfile<<chosenMovie.email<<","<<chosenMovie.userName<<","<<chosenMovie.showTitle<<","
                  <<chosenMovie.showDate<<","<<chosenMovie.showTime<<",";
        for(int j=0; j<chosenMovie.seats.size(); j++)
        {
            recordfile<<chosenMovie.seats[j];
            if(j!=chosenMovie.seats.size()-1)recordfile<<",";
        }
        recordfile<<"\n";
    recordfile.close();

    vector<string>genres;
    ifstream details("MovieDetails.txt");
    int found=0;
    string line,snippet;
    while(getline(details,line))
    {
        if(line[0]=='1' && line.find(chosenMovie.showTitle)!=string::npos){
            found=1;
        }
        if(line[0]=='2' && found){
            string val;
            stringstream genreStream(line);
            genreStream>>val;
            while(getline(genreStream,snippet,',')){
                snippet.erase(0, snippet.find_first_not_of(" "));
                snippet.erase(snippet.find_last_not_of(" ") + 1);
                genres.push_back(snippet);
            }
            break;
        }
    }
    details.close();

    ofstream userFile(USERS_DIRECTORY+chosenMovie.email+".txt",std::ios::app);
    userFile<<"\n";
    userFile<<chosenMovie.showTitle<<","<<chosenMovie.showDate<<","<<chosenMovie.showTime<<","<<chosenMovie.serialNum<<","<<
        chosenMovie.serialSlot<<","<<chosenMovie.hall<<",";
    for(int i=0;i<chosenMovie.seats.size();i++){
        userFile<<chosenMovie.seats[i];
        if(i!=chosenMovie.seats.size()-1)userFile<<";";
        else userFile<<",";
    }
    for(int i=0;i<genres.size();i++){
        userFile<<genres[i];
        if(i!=genres.size()-1)userFile<<",";
    }
    userFile.close();
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

    cout<<"\t\t*****************************************************************************************"<<endl;
    cout<<"\t\t                                 S    C    R    E    E    N                           "<<endl;
    cout<<"\t\t*****************************************************************************************"<<endl<<endl;

    for(i=0; i<10; i++)
    {
        cout<<"\t\t  ";
        for(j=0; j<10; j++)
        {
            if(seatArr[i][j]=="X")
            {
                cout << "\033[31m";
                cout<<left<<setw(9)<<seatArr[i][j];
                cout << "\033[0m";
            }
            else
            {
                cout << "\033[32m";
                cout<<left<<setw(9)<<seatArr[i][j];
                cout << "\033[0m";
                seatsAvailable++;
            }
        }
        cout<<endl;
        cout<<"\t\t........................................................................................."<<endl;
    }
    cout<<endl;
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

    string seats[numOfTickets];
    vector<string>allInfo;
    for(i=0; i<numOfTickets; i++)
    {
        int error=1;
        while(error){
            cout<<"Enter seat number: ";
            cin>>seats[i];
            if(seats[i].size()>=2 && seats[i].size()<=3){
                if(seats[i][0]>='A' && seats[i][0]<='J'){
                    string num=seats[i].substr(1);
                    int n=stoi(num);
                    if(n>=1 && n<=10){
                        error=0;
                        break;
                    }
                }
            }
            if(error)cout<<"Invalid seat entered. Please try again."<<endl;
        }
        error=1;
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
        allInfo.push_back(line);
    }

    input.close();
    k=0;
    ofstream outputFile("Seats.txt");
    for(i=0; i<allInfo.size(); i++)
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
    recordBooking(chosenMovie);
    makePayment(chosenMovie);
    inputFile.close();
    outputFile.close();
}
