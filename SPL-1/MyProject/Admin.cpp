#include <bits/stdc++.h>
#include "Admin.h"
//#include "TicketBooking.h"

using namespace std;

void Admin()
{
    system("cls");

    ifstream input("AdminInfo.txt");
    string email,password,temp,snippet;
    int check;
    cout<<"ADMIN LOGIN"<<endl;

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




}
