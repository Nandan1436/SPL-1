#include <bits/stdc++.h>
#include "movieDetails.h"
#include "MovieSchedule.h"

using namespace std;

void movieDetails()
{
    system("cls");
    ifstream details("MovieDetails.txt");
    cout<<"\t\t\t\t\t\t********************************"<<endl;
    cout<<"\t\t\t\t\t\t    M O V I E  D E T A I L S"<<endl;
    cout<<"\t\t\t\t\t\t********************************"<<endl<<endl;
    string line;
    while(getline(details,line))
    {
        if(line.size()==2 && line[0]=='*' && line[1]=='*')
        {
            continue;
        }
        else if(line[0]=='4')
        {
            int i,count=0;
            cout<<"DESCRIPTION:"<<endl;
            for(i=2; line[i]; i++)
            {
                count++;
                if(count>70 && (line[i]==' ' || line[i]=='.'))
                {
                    count=0;
                    cout<<endl;
                }
                else cout<<line[i];
            }
            cout<<endl<<endl;
        }
        else
        {
            if(line[0]=='1')cout<<"TITLE: ";
            else if(line[0]=='2')cout<<"GENRE: ";
            else cout<<"RELEASE DATE: ";
            for(int i=2; line[i]; i++)
            {
                cout<<line[i];
            }
            cout<<endl;
        }

    }
    details.close();
    cout<<"To go back to Movie Schedule, enter any key."<<endl;
    char ch;
    cin>>ch;
    system("cls");
    return;

}
