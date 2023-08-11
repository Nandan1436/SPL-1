#include <bits/stdc++.h>

using namespace std;

void userSignIn(){
    system("CLS");
    string email,password;
    cout<<"Welcome to Cineverse!"<<endl;
    cout<<"Enter your email: ";
    cin>>email;
    cout<<"Set a password: the password should have at least 8 characters"<<endl;
    cin>>password;

}

void userSignUp(){
    string email,password;
    cout<<"Enter email: ";
    cin>>email;
    cout<<"Enter password: ";
    cin>>password;
}

void User(){
    int choice;
    cout<<"1.Sign in"<<endl;
    cout<<"2.Sign up"<<endl;
    if(choice==1)userSignIn();
    else userSignUp();

}

void Admin(){

}

void mainMenu(){
    int choice;
    cout<<"Welcome"<<endl;
    cout<<"1.User"<<endl;
    cout<<"2.Admin"<<endl;
    cout<<"Choose: ";
    cin>>choice;
    if(choice==1)User();
    else Admin();


}

int main()
{
    mainMenu();

    return 0;
}
