#include <bits/stdc++.h>
#include <conio.h>
#include "UserLogIn.h"
#include "MovieSchedule.h"

using namespace std;

void userLogIn()
{
    system("CLS");
    for(int i=0; i<3; i++)
    {
        string email,password;
        cout<<"LOGIN"<<endl;
        cout<<"Enter your email: ";
        cin>>email;
        cout<<"Enter your password: ";
        cin>>password;

        string temp,snippet;
        int check=0;
        ifstream input("UserList.txt");
        while(getline(input,temp))
        {
            string emailCheck,passwordCheck;
            stringstream ss(temp);

            getline(ss,snippet,',');
            emailCheck=snippet;
            getline(ss,snippet,',');
            passwordCheck=snippet;

            if(email==emailCheck && password==passwordCheck)
            {
                check=1;
                break;
            }
        }
        input.close();
        if(!check && i<2)
        {
            cout<<"Incorrect email or password! Please try again!"<<endl;
            check=0;
        }
        else if(!check && i==2){
            cout<<"Login failed after 3 attempts!";
            exit(0);
        }
        else break;
    }
    movieSchedule();

}
