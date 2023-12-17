#include <bits/stdc++.h>
#include "UserSignUp.h"
#include "UserMenu.h"
#include <openssl/sha.h>

using namespace std;

struct User
{
    string fullName;
    string email;
    string password;
    string dateOfBirth;
    string userName;
};

string sha256(const string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.length());
    SHA256_Final(hash, &sha256);

    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << hex << setw(2) << setfill('0') << static_cast<int>(hash[i]);
    }

    return ss.str();
}


void userSignUp()
{
    system("cls");

    const string USERS_DIRECTORY = "Users\\";

    User user;
    string email,password,username,fullName,dateOfBirth,temp,line;
    int check=1;
    cout<<"\t\t\t\t\t\t*************************"<<endl;
    cout<<"\t\t\t\t\t\t  WELCOME TO CINEVERSE"<<endl;
    cout<<"\t\t\t\t\t\t*************************"<<endl;
    cout<<"Create an account"<<endl;
    while(check){
        cout<<"**Enter your email: ";
        cin>>user.email;
        ifstream checkFile(USERS_DIRECTORY+user.email+".txt");
        if (checkFile.good()) {
            cout<<"An account with this email already exists. Please try another email or log in\n";
            checkFile.close();
        }
        else check=0;
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
        cout<<"**Enter password(password should contain at least 8 characters, including symbols, "<<endl;
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
    string hashedPassword=sha256(user.password);

    ofstream userFile(USERS_DIRECTORY + user.email + ".txt");
    if (!userFile) {
        cout << "Error creating user file." << endl;
        return;
    }

    userFile << "Full Name: " << user.fullName << endl;
    userFile << "User Name: " << user.userName << endl;
    userFile << "Date of Birth: " << user.dateOfBirth << endl;
    userFile << "Email: " << user.email << endl;
    userFile << "Hashed Password: " << hashedPassword << endl;
    userFile << "History:" << endl;

    cout<<"Sign up successful!"<<endl;
    cout<<"Taking you to User Menu...";
    this_thread::sleep_for(chrono::seconds(2));
    UserMenu(user.email,user.userName);
}
