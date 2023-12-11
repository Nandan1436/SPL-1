#include <bits/stdc++.h>
#include "UserLogIn.h"
#include "MovieSchedule.h"
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

string sha(const string& input) {
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

void userLogIn()
{
    system("cls");

    const string USERS_DIRECTORY = "Users\\";
    User user;
    int check=0;
    cout<<"LOGIN"<<endl;
    for(int i=0;i<3;i++)
    {
        cout<<"**Enter your email: ";
        cin>>user.email;

        ifstream userFile(USERS_DIRECTORY + user.email + ".txt");

        if (!userFile) {
            cout << "User does not exist. Please try again or sign up first." << endl;
            continue;
        }
        userFile.seekg(0);

        for (int j = 0; j < 4; ++j) {
            userFile.ignore(numeric_limits<streamsize>::max(), ':');
            if(j==0)userFile>>user.fullName;
            else if(j==1)userFile>>user.userName;
            else if(j==2)userFile>>user.dateOfBirth;
            else if(j==3)userFile>>user.email;
        }

        string storedHashedPassword;
        userFile.ignore(numeric_limits<streamsize>::max(), ':');
        userFile >> storedHashedPassword;
        userFile.close();

        cout << "**Enter your password: ";
        cin >> user.password;

        if (sha(user.password) == storedHashedPassword) {
            check=1;
            break;
        } else {
            cout << "Incorrect password. Please try again." << endl;
        }
    }
    if(check){
        cout << "Login successful. Welcome back!" << endl;
        cout<<"Taking you to User Menu...";
        this_thread::sleep_for(chrono::seconds(2));
        UserMenu(user.email,user.userName);
    }
    else {
        cout<<"Failed attempt three times. Exiting program.";
    }

}
