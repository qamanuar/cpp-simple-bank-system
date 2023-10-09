#include <iostream>
#include <windows.h>
#include <unistd.h>
#include <conio.h>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <bits/stdc++.h>
#include <string>
#include <sstream>
#include <cstdio>

using namespace std;

void menu(string filename);
void changepass(string filename);
void randomColor();
void banner();
void login();
void mainmenu();
void create();
void transfer(string filename);
void withdraw(string filename);
void deposit(string filename);
void logout();
void update(string recipient, int dedcution);
void transcomp();
void loading();
void settings();

void balance(string filename){
    ifstream infile(filename+".txt");
    if (infile.is_open()){
    system("cls");
    double bal;
    string pword;
    ifstream infile(filename+".txt");
    infile >> pword >> bal;
    banner();
    cout << "\tBalance: RM" << bal << endl;
    getch();
    menu(filename);
    }
    else{
        banner();
        cout<<"failed !";
    }
}

void menu(string filename){
    int selection = 1; // initialize selection to 1
    char key;
    while (true) {
        system("cls"); // clear the console
        banner();

        // display menu options
        if (selection == 1) cout << "> Display Balance" << endl;
        else cout << "  Display Balance" << endl;
        if (selection == 2) cout << "> Withdraw Money" << endl;
        else cout << "  Withdraw Money" << endl;
        if (selection == 3) cout << "> Deposit Money" << endl;
        else cout << "  Deposit Money" << endl;
        if (selection == 4) cout << "> Transfer Money" << endl;
        else cout << "  Transfer Money" << endl;
        if (selection == 5) cout << "> Logout" << endl;
        else cout << "  Logout" << endl;

        // wait for user input
        key = _getch(); // use _getch() to read a single character without echoing to the console

        // handle arrow key input
        switch (key) {
            case 72: // up arrow
                selection--;
                if (selection < 1 ) selection = 5;
                break;
            case 80: // down arrow
                selection++;
                if (selection > 5) selection = 1;
                break;
            case 13: // enter key
                //system("cls"); // clear the console
                if(selection == 1){
                    balance(filename);
                    exit(0);
                }
                else if(selection == 2){
                    withdraw(filename);
                    exit(0);
                }
                else if(selection == 3){
                    deposit(filename);
                    exit(0);
                }
                else if(selection == 4){
                    transfer(filename);
                    exit(0);
                }
                else if(selection == 5){
                    logout();
                    exit(0);
                }
                break;
            default:
                break;
        }
    }
}

void login(){
    int attempt = 3;
    string filename;
    while(attempt != 0){
    banner();
    double bal;
    cout << "Enter username : ";
    getline(cin, filename);

    ifstream infile(filename+".txt");

    if (infile.is_open()) {
        string pword,file_password;
        infile >> file_password;
        infile >> bal;
        cout<<"Enter password : ";
        char ch;
        while((ch = _getch()) != '\r') {//\r is char for enter key
        pword.push_back(ch);
        cout << '*';
        }

if (pword == file_password) {
            menu(filename);
        } else {
            system("cls");
            banner();
            cout << "\n   Incorrect username or password." << endl;
            cout<<"     You have "<<attempt-1<<" attempt(s) left";
            attempt -= 1;
            Sleep(1000);
            }
        }
    }
    int want =1;
    while(true){
        banner();
        cout<<"Do you want to change your password ?";
        if(want == 1)
        cout<<"\n\n\t   [yes]    no";
        else if(want == 2)
        cout<<"\n\n\t    yes    [no]";
        char key = _getch();

        switch(key){
            case 77: // Right arrow
                want--;
                if(want<1) want =2;
                break;
            case 75: // Right arrow
                want++;
                if(want>2) want =1;
                break;
            case 13: // enter key
                if(want == 1){
                    changepass(filename);
                    exit(0);
                }
                else if(want == 2){
                    exit(EXIT_SUCCESS);
                    exit(0);
                }
                break;
            }        }

}

void create(){
    banner();

    string filename;
    cout<<"Enter username     : ";
    cin >> filename;

    string pword;
    cout<<"Enter password     : ";
    cin>>pword;

    string code;
    cout<<"Enter Special Code : ";\
    cin>>code;

    double bal;
    cout<<"Enter balance      : RM ";
    cin>>bal;

    ofstream file(filename+".txt");
        if (file.is_open()) {
        file <<  pword << " " << bal << " " << code <<endl;
        file.close();
        system("cls");
        banner();
        cout << "   Account created successfully." << endl;
        Sleep(1000);
    } else {
        cout << "Failed to create Account." << endl;
    }
}

void banner(){
    system("cls");
    cout<<"\t+===================+"<<endl;
    cout<<"\t       Bank Ong      "<<endl;
    cout<<"\t+===================+\n"<<endl;
}

void randomColor() {
    system ("color 30");
}

void transfer(string filename){
    banner();
    fstream file(filename+".txt", ios::in | ios::out);
    if (!file.is_open()) {
        cout << "Failed to open file!\n";
    }

    // Read the current string and integer values from the file
    string str_value,recipient,code;
    int int_value;
    file >> str_value >> int_value >> code;

    // Ask the user for the value to be subtracted from the integer variable
    int deduction;
    cout << "   Your current balance is : RM " << int_value << endl;
    cout << "   How much do you want to transfer ?"<<endl;
    cout<<"\n\tRM ";
    cin >> deduction;
    cout<<"\n   Enter username of the recipient : ";
    cin>>recipient;

    // Subtract the input value from the integer value
    int_value -= deduction;

    // Move the file pointer back to the beginning of the file
    file.seekp(0);

    // Write the updated integer value back to the file
    file << str_value << " " << int_value << " " << code;

    // Close the file
    file.close();
    update(recipient,deduction);

    loading();
    transcomp();
    Sleep(1000);
    menu(filename);
}

void changepass(string filename){
    banner();
    fstream file(filename+".txt", ios::in | ios::out);
    if (!file.is_open()) {
        cout << "Failed to open file!\n";
    }

    // Read the current string and integer values from the file
    string str_value,recipient,code, test, newpass;
    int int_value;
    file >> str_value >> int_value >> code;

    // Ask the user for the value to be subtracted from the integer variable
    int deduction;
    cout<<"\tEnter your special code : ";
    cout<<"\n\n\t";
    cin >> test;

if(test == code){
        banner();
        cout<<"Your special code is correct !"<<endl;
        cout<<"Enter your new password : ";
        cin>>newpass;
        loading();
        banner();
        cout<<"Your password has successfully changed !";
        file.seekp(0);

    // Write the updated integer value back to the file
    file << newpass << " " << int_value << " " << code;
    }
    else{
        cout<<"\n    Your special code is incorrect !"<<endl;
        exit(EXIT_SUCCESS);
    }

    // Close the file
    file.close();
    Sleep(1000);
    login();
}

void update(string recipient, int deduction){
    fstream file(recipient+".txt", ios::in | ios::out);
    if (!file.is_open()) {
        cout << "Failed to open file!\n";
    }

    // Read the current string and integer values from the file
    string str_value2, code;
    int int_value2;
    file >> str_value2 >> int_value2 >> code ;
    // Add the input value to the integer value
    int_value2 += deduction;

    // Move the file pointer back to the beginning of the file
    file.seekp(0);

    // Write the updated integer value back to the file
    file << str_value2 << " " << int_value2 << " " << code;

    // Close the file
    file.close();
}

void transcomp(){
    banner();
    cout<<"\n\tTransaction complete !";
}

void loading(){
    banner();
    cout<<"\n\n\t     ";
    for(int i=0; i<11; i++){
        cout<<"$";
        Sleep(100);
    }
}

void withdraw(string filename){
    banner();
    fstream file(filename+".txt", ios::in | ios::out);
    if (!file.is_open()) {
        cout << "Failed to open file!\n";
    }

    // Read the current string and integer values from the file
    string str_value, code;
    int int_value;
    file >> str_value >> int_value >> code;

    // Ask the user for the value to be subtracted from the integer variable
    int deduction;
    cout << "   Your current balance is : RM " << int_value << endl;
    cout << "   How much do you want to withdraw ?"<<endl;
    cout<<"\n\tRM ";
    cin >> deduction;

    // Subtract the input value from the integer value
    int_value -= deduction;

    // Move the file pointer back to the beginning of the file
    file.seekp(0);

    // Write the updated integer value back to the file
    file << str_value << " " << int_value << " " << code;

    // Close the file
    file.close();

    loading();
    transcomp();
    Sleep(1000);
    menu(filename);
}

void deposit(string filename){
    fstream file(filename+".txt", ios::in | ios::out);
    if (!file.is_open()) {
        cout << "Failed to open file!\n";
    }

    // Read the current string and integer values from the file
    string str_value, code;
    int int_value;
    file >> str_value >> int_value >> code;

    // Ask the user for the value to be added to the integer variable
    int addition;
    banner();
    cout << "   Enter the amount that"<<endl;
    cout<<"   you want to deposit : RM ";
    cin >> addition;

    // Add the input value to the integer value
    int_value += addition;

    // Move the file pointer back to the beginning of the file
    file.seekp(0);

    // Write the updated integer value back to the file
    file << str_value << " " << int_value << " " << code;

    // Close the file
    file.close();
    loading();
    transcomp();
    Sleep(1000);
    menu(filename);
}

void logout(){
    mainmenu();
}

void mainmenu(){
    start :
    int selection = 1; // initialize selection to 1
    char key;

    while (true) {
        system("cls"); // clear the console
        banner();

        // balance menu options
        if (selection == 1) cout << "> Login" << endl;
        else cout << "  Login" << endl;
        if (selection == 2) cout << "> Create Account" << endl;
        else cout << "  Create Account" << endl;
        if (selection == 3) cout << "> Settings" << endl;
        else cout << "  Settings" << endl;

        // wait for user input
        key = _getch(); // use _getch() to read a single character without echoing to the console

// handle arrow key input
        switch (key) {
            case 72: // up arrow
                selection--;
                if (selection < 1 ) selection = 3;
                break;
            case 80: // down arrow
                selection++;
                if (selection > 3) selection = 1;
                break;
            case 13: // enter key
                if(selection == 1){
                    login();
                }
                else if(selection == 2){
                    create();
                }
                else if(selection == 3){
                    settings();
                }
                break;
            default:
                break;
        }
    }
}
void settings(){
    banner();
    int colour[6] = {70,30,27,60,57,80};
    int num;
    cout<<"What colour would you like ?"<<endl;
    cout<<"1. Blue"<<endl;
    cout<<"2. Green"<<endl;
    cout<<"3. Yellow"<<endl;
    cout<<"4. Purple"<<endl;
    cout<<"5. Grey\n"<<endl;
    cin>>num;
    string cmd = "color " + to_string(colour[num]);
    system(cmd.c_str());
}

int main() {
    mainmenu();
}
