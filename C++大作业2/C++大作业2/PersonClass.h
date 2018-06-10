#pragma once
#ifndef PersonClass
#define PersonClass

#include<iostream>
#include<fstream>
#include<algorithm>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<iomanip>
#include<sstream>
#include<direct.h>
#include<windows.h>


using namespace std;

class Person
{
protected:
	string Name, ID;
public:
	Person(string, string);
};

#endif 
