#pragma once
#include <iostream>
#include<stack>
#include<queue>
#include<list>
#include<string>
#include "contact.h"
using namespace std;


class User
{
public:
	string username;
	string password;
	int id;
	stack<string>sentmessages;
	stack<string>recivedmessages;
	queue<string>myfavouritmessages;
	list<contact>mycontact;

public:
	User(string name, string pass);
	User( );

};

