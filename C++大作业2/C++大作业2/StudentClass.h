#pragma once
#ifndef StudentClass
#define StudentClass


#include"PersonClass.h"



class Student:protected Person
{
protected:
	int Rank, Num;//Rank名次，Num科目数
	double Mark[10];//Mark[0]总成绩，Mark[1-9]成绩1-9
public:
	Student(string = "", string = "", double[] = {0}, int=0);
	Student(const Student &);//复制构造函数
	void sum();//求总成绩
	template <typename T>//用于改变学生信息
	void change(T, int, int=-1);
	void change(double, int, int=-1);
	void display(int, int);//display用于在屏幕上显示记录
	void fileout(fstream &,int);//fileout用于文件输出
	string get(string);//get用于返回学生信息，动态联编使用重载返回不同值
	double get(int);
	template <typename T>friend int Find(const vector<Student> &, T, T);//按特定方式查找学生信息
	friend bool compareName(const Student &, const Student &);//姓名排序
	friend bool compareID(const Student &, const Student &);//学号排序
	friend bool compareSum(const Student &, const Student &);//名次排序
	friend void fixRank(vector<Student> &);//重置学生名次
};

bool compareName(const Student &A, const Student &B);//姓名排序
bool compareID(const Student &A, const Student &B);//学号排序
bool compareSum(const Student &A, const Student &B);//名次排序
void fixRank(vector<Student> &t);//重置学生名次
template <typename T>int Find(vector<Student> &t, T s, T act);//按特定方式查找学生信息



#endif 
