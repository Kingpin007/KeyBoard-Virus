#define _WIN32_WINNT 0x0501
#include <windows.h>
#include <iostream>
#include <cstdio>
#include <process.h>
#include <cstdlib>
#include <fstream>
#include <cctype>

using namespace std;
/*
    Some General Guide lines:
    E = Enter
    D=Down Arrow
    U=Up Arrow
    R=Right Arrow
    L=Left Arrow
    f1=F1
    All codes will be in lower case
    Input the system of keys and then Print it in a file.
*/
void PressKey(char c)
{
    Sleep(400);
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.wVk = c;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));
}
void ReleseKey(char c)
{
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.wVk = c;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));
	Sleep(50);
}
void Sendchar(char c)
{
    Sleep(50);
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.wVk = c;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));

}
char keys[100];
char ch,loop='y';
int x;
void apply()
{
    int runs;
    cout<<"Enter The number of times you want to run this loop: ";
    cin>>runs;
    cout<<"\n\nYou Have 5 seconds to switch to your desired window!!!\n\n";
    Sleep(5500);
    for(int j=0;j<runs;j++)
    {
        for(int i=0;keys[i]!='\0';i++)
        {
            if(islower(keys[i]))
                Sendchar(toupper(keys[i]));
            else if(isdigit(keys[i]))
                Sendchar(keys[i]);
            else if(isupper(keys[i]))
            {
                if(keys[i]=='E')
                    PressKey(VK_RETURN);
                else if(keys[i]=='F')
                    PressKey(VK_F2);
                else if(keys[i]=='D')
                    PressKey(VK_DOWN);
                else if(keys[i]=='U')
                    PressKey(VK_UP);
                else if(keys[i]=='R')
                    PressKey(VK_RIGHT);
                else if(keys[i]=='L')
                    PressKey(VK_LEFT);
                else
                    Sendchar(keys[i]);
            }
        }
    }
    cout<<"Want to go back to menu (y/n)?: ";
    cin>>loop;
}
void input()
{
    cout<<"Enter The keys: "<<endl;
    ch='y';
    for(int i=0;ch=='y'||ch=='Y';i++)
    {
        cout<<"Enter Key "<<i+1<<" : ";
        cin>>keys[i];
        cout<<"Want to enter another (y/n) : ";
        cin>>ch;
        if(ch=='n'||ch=='N')
            keys[i+1]='\0';
    }
    ofstream fout("Keys.txt",ios::out|ios::app);
    fout<<keys<<'\n';
    apply();
}
void file()
{
    ifstream fin("Keys.txt");
    int i=1;
    char choice,nl;
    while(!fin.eof())
    {
        fin>>keys>>nl;
        cout<<"Key Set "<<i++<<" : "<<keys<<endl<<"Want to use this (y/n): ";
        cin>>choice;
        if(choice=='y'||choice=='Y')
        {
            apply();
            break;
        }
        if(fin.eof())
            cout<<"End of file reached!";
    }
    cout<<"End of file want to go back to menu (y/n)?: ";
    cin>>loop;
}
void display()
{
    system("cls");
    cout<<"1.Use Existing file \n2.Input fresh values \nEnter your Choice: ";
    cin>>x;
    if(x==1)
        file();
    else if(x==2)
        input();
    else
    {
        cout<<"Error! Wrong Input! Try again (y/n): ";
        cin>>loop;
    }
}
int main()
{
    while(loop=='Y'||loop=='y')
        display();
	return 0;
}
