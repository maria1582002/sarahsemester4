

#include <iostream>
#include <iostream>
#include<stack>
#include<queue>
#include<list>
#include<string>
#include<fstream>
#include "contact.h"
# include"User.h"
#include<vector>
#define BIN_FILE_PATH "data/datafile.bin"
using namespace std;

vector<User*>returndata(string binfilepath) {
    vector<User*>usersdata;
    string lines;
    try {
        ifstream mydata(binfilepath, ios::in | ios::binary | ios::ate);
        if (mydata.is_open()) {
            streampos size = mydata.tellg();
            char* memblock = new char[size];
            mydata.seekg(0, ios::beg);
            mydata.read(memblock, size);
            mydata.close();
            long long byteindex = 0;
            while (byteindex < size) {
                User* us = (User*)(memblock + byteindex);
                usersdata.push_back(us);
                byteindex += sizeof(User);

            }


        }

    }
    catch (exception& e) {
        cout << "their is an standerd exception " << e.what() << endl;
    }
    return usersdata;
}

void  reg(User user, string binfilepath) {
    try {

        bool found = false;

        vector<User*> data = returndata(BIN_FILE_PATH);
        for (auto line = data.begin(); line != data.end(); line++) {
            User* users = *line;
            string l;
            string k;

            int i = users->username.compare(user.username);
            int j = users->password.compare(user.password);

            if (i == 0 && j == 0 && users->id == user.id) {
                found = true;
                break;
            }
        }
        if (found == true) {
            cout << "***** you are already have account*****" << endl;
        }
        else {
            ofstream mydata;
            mydata.open(binfilepath, ios::out | ios::app | ios::binary);
            mydata.write((char*)&user, sizeof(user));
            mydata.close();
            cout << "user added" << endl;
        }



    }

    catch (exception& e) {
        cout << "their is an stander exception" << e.what() << endl;
    }
}


void login() {
    string name;
    string pass;
    int id_user;
    bool found = false;
    cout << "enter your username : "<<endl;
    cin >> name;
    cout << "enter your password : "<<endl;
    cin >> pass;
    cout << "enter your id : "<<endl;
    cin >> id_user;

    vector<User*> data = returndata(BIN_FILE_PATH);
    for (auto line = data.begin(); line != data.end(); line++) {
        User* users = *line;
        string l;
            string k;
            
        int i = users->username.compare(name);
        int j = users->password.compare(pass);

        if (i == 0 && j == 0 && users->id==id_user) {
            found =true;
            break;
        }
    }
    if (found == true) {
        cout << "*****successfully logined****" << endl;
    }
    else {
        cout << " sorry wrong data please try again" << endl;
        login();
    }
}
int main()
{
    while (true) {
        int options;
        cout << "click 1 for register and 2 for login and 3 for display users :"<<endl;

        cin >> options;
        if (options == 1) {
            User user;
            int id;
            cout << "enter username : " << endl;
            std::cin >> std::ws;
            getline(cin, user.username);
            cout << "enter password : " << endl;
            getline(cin, user.password);
            cout << "enter your id numbe : " << endl;
            cin >> user.id;
            reg(user, BIN_FILE_PATH);
            cout<< "--------------------------------------------"<<endl;

        }
        else if (options == 2) {

            login();
            cout << "-----------------------------------------------"<<endl;


        }
        else if (options == 3) {
            vector<User*>filelines = returndata(BIN_FILE_PATH);
            for (auto line = filelines.begin(); line != filelines.end(); line++) {
                User* users = *line;
                cout << users->username << "\n";
                cout << users->password << "\n";
                cout << users->id << "\n";
                cout << "------------" << endl;
            }
        }
      
    }
}

