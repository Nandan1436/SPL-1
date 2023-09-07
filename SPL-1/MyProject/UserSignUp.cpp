#include <bits/stdc++.h>
#include "UserSignUp.h"

using namespace std;

void userSignUp()
{
    system("CLS");
    string email,password,username,fullName,da;
    cout<<"WELCOME TO CINEVERSE"<<endl;
    cout<<"Enter email: ";
    cin>>email;

    int checkLowerCase=0,checkUpperCase=0,checkNum=0,checkSymbol=0,length=0;
    while(!checkLowerCase || !checkUpperCase || !checkNum || !checkSymbol || length<8)
    {
        cout<<"Enter password: your password should contain at least 8 characters, including symbols,numbers and upper and lower case letters: "<<endl;
        cin>>password;

        for(int i=0; password[i]; i++)
        {
            if(password[i]>='a' && password[i]<='z')checkLowerCase=1;
            else if(password[i]>='A' && password[i]<='Z')checkUpperCase=1;
            else if(password[i]>='0' && password[i]<='9')checkNum=1;
            else checkSymbol=1;
            length++;
        }
        if(length<8 || !checkLowerCase || !checkUpperCase || !checkNum || !checkSymbol)
        {
            cout<<"Password doesn't meet the requirements. Please enter a stronger password"<<endl;
        }
    }

    cout<<"Enter a username: "<<endl;
    cin>>username;
    cout<<"Enter your full name: "<<endl;
    cin>>fullName;

}
