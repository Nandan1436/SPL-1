#include <bits/stdc++.h>
#include <conio.h>
#include "UserLogIn.h"
#include "MovieSchedule.h"
#include "UserMenu.h"

using namespace std;

void userLogIn()
{
    system("cls");

    ifstream input("UserList.txt");
    string email,password,userName="",temp,snippet;
    int check;
    cout<<"LOGIN"<<endl;
    for(int i=0; i<3; i++)
    {
        cout<<"**Enter your email: ";
        cin>>email;
        cout<<"**Enter your password: ";
        cin>>password;

        check=0;
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
        if(!check && i<2)
        {
            cout<<"Incorrect email or password! Please try again!"<<endl;
            input.clear();
            input.seekg(0,ios::beg);
        }
        else if(!check && i==2){
            cout<<"Login failed after 3 attempts!";
            exit(0);
        }
        else break;
    }

    for(int i=temp.size()-1;temp[i]!=',';i--){
        userName+=temp[i];
    }
    int a=0,b=userName.size()-1;
    while(a<=b){
        char temp=userName[a];
        userName[a]=userName[b];
        userName[b]=temp;
        a++;
        b--;
    }
    input.close();
    cout<<endl;
    cout<<"Log in successful!"<<endl;
    cout<<"Taking you to User Menu...";
    this_thread::sleep_for(chrono::seconds(2));
    UserMenu(email,userName);

}
