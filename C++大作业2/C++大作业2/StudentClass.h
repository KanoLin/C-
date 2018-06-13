#pragma once
#ifndef StudentClass
#define StudentClass


#include"PersonClass.h"



class Student:protected Person
{
protected:
	//string Name, ID;
	int Rank, Num;
	double Mark[10];
public:
	Student(string = "", string = "", double[] = {0}, int=0);
	Student(const Student &);
	void sum();
	template <typename T>
	void change(T, int, int=-1);
	void change(double, int, int=-1);
	void display(int,int);
	void fileout(fstream &,int);
	string get(string);
	double get(int);
	template <typename T>friend int Find(const vector<Student> &, T, T);
	friend bool compareName(const Student &, const Student &);
	friend bool compareID(const Student &, const Student &);
	friend bool compareSum(const Student &, const Student &);
	friend void fixRank(vector<Student> &);
};

bool compareName(const Student &A, const Student &B);
bool compareID(const Student &A, const Student &B);
bool compareSum(const Student &A, const Student &B);
void fixRank(vector<Student> &t); template <typename T>int Find(vector<Student> &t, T s, T act);



#endif 
