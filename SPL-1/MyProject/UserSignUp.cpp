#include <bits/stdc++.h>
#include "UserSignUp.h"
#include "UserMenu.h"

using namespace std;

struct User
{
    string fullName;
    string email;
    string password;
    string dateOfBirth;
    string userName;
};

void userSignUp()
{
    system("cls");

    const char* filename = "UserList.txt";
    ifstream inputFile(filename);
    ofstream outputFile(filename,ios::app);
    User user;

    string email,password,username,fullName,dateOfBirth,temp,line;
    int check=0;
    cout<<"WELCOME TO CINEVERSE"<<endl;
    cout<<"Create an account"<<endl;

    cout<<"**Enter email: ";
    cin>>user.email;

    while(!check)
    {
        while(getline(inputFile,line))
        {
            stringstream rowString(line);
            getline(rowString,temp,',');
            if(temp==user.email)
            {
                cout<<"An account with this email already exists. Please try another email: ";
                cin>>user.email;
                inputFile.seekg(0,ios::beg);
            }
        }
        check=1;
    }
    cin.ignore();
    cout<<"**Enter Full Name: ";
    getline(cin,user.fullName);
    cout<<"**Enter date of Birth(dd/mm/yyyy): ";
    getline(cin,user.dateOfBirth);
    cout<<"**Enter a user Name: ";
    getline(cin,user.userName);

    int checkLowerCase=0,checkUpperCase=0,checkNum=0,checkSymbol=0,length=0;
    while(!checkLowerCase || !checkUpperCase || !checkNum || !checkSymbol || length<8)
    {
        cout<<"**Enter password(password should contain at least 8 characters, including symbols(except ',')"<<endl;
        cout<<"numbers and upper and lower case letters): ";
        cin>>user.password;

        for(int i=0; user.password[i]; i++)
        {
            if(user.password[i]>='a' && user.password[i]<='z')checkLowerCase=1;
            else if(user.password[i]>='A' && user.password[i]<='Z')checkUpperCase=1;
            else if(user.password[i]>='0' && user.password[i]<='9')checkNum=1;
            else checkSymbol=1;
            length++;
        }
        if(length<8 || !checkLowerCase || !checkUpperCase || !checkNum || !checkSymbol)
        {
            cout<<"Password doesn't meet the requirements. Please enter a stronger password"<<endl;
        }
    }

    outputFile.seekp(0,ios::end);
    outputFile<<"\n"<<user.email<<","<<user.password<<","<<user.fullName<<","<<user.dateOfBirth<<","<<user.userName;
    inputFile.close();
    outputFile.close();

    cout<<endl;
    cout<<"Sign up successful!"<<endl;
    cout<<"Taking you to User Menu...";
    this_thread::sleep_for(chrono::seconds(2));
    UserMenu(user.email,user.userName);

}
