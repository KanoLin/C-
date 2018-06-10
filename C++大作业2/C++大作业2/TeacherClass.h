#pragma once
#ifndef TeacherClass
#define TeacherClass

#include"StudentClass.h"

class Teacher :protected Student
{
public:
	Teacher();
	Teacher(string, string);
	void start();
};

bool isNULL(vector<Student> &t);

void showTableTitle(int);
void ShowTableUI(vector<Student>& t);

void SortUI(vector<Student> &t);

template <typename T>
int Find(vector<Student> &t, T s, T act);
int FindUI0(vector<Student> &t);
void FindUI(vector<Student> &t);

void ChangeUI(vector<Student> &t);

void DeleteMark(vector<Student> &t, vector<int>&del);
void DeleteShow(vector<Student> &t, vector<int> &del);
void Delete(vector<Student> &t, vector<int> &del);
void DeleteUI(vector<Student> &t, vector<int> &del);

void CreatSaveFileUI(fstream &outFile, string &outFileName);

void ReadFileUI(vector<Student> &t, fstream &inFile, string &inFileName);

void SaveFileUI(vector<Student> &t, fstream &outFile, string &outFileName);

void AddOne(vector<Student> &t);
void AddUI(vector<Student> &t, fstream &infile, string &inFileName);

void NewBuildUI(vector<Student> &t, fstream &outfile, string &outFileName);

void displayTable();

void UI();











#endif // !TeacherClass
