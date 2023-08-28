#include <bits/stdc++.h>
#include "MainMenu.h"
#include "ExitConfirmation.h"

using namespace std;

void exitConfirmation(){
    system("CLS");
    char choice;
    cout<<"Are you sure you want to quit?"<<endl;
    cout<<"YES(y) or NO(n)"<<endl;
    cin>>choice;

    if(choice=='Y'||choice=='y'){
        exit(0);
    }
    else {
        system("CLS");
        mainMenu();
    }
}
