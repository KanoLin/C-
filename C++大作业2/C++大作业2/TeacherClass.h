#pragma once
#ifndef TeacherClass
#define TeacherClass

#include"StudentClass.h"

class Teacher :protected Student
{
public:
	Teacher();
	Teacher(string, string);
	void start();//系统启动
};

bool isNULL(vector<Student> &t);//isNULL判断向量t是否为空，以保障一切需要读取向量t信息的操作得以正常进行

void showTableTitle(int);//showTableTitle用于显示表头
void ShowTableUI(vector<Student>& t);//ShowTableUI----显示记录界面

void SortUI(vector<Student> &t);//SortUI----记录排序界面

template <typename T>
int Find(vector<Student> &t, T s, T act);//Find用于在向量中查找特定信息的学生并返回在向量组中的标记
int FindUI0(vector<Student> &t);//FindUI0----查找方式界面；由于多个功能都需要在查找功能支持下才能工作，于是单独将此界面作为函数方便调用
void FindUI(vector<Student> &t);//FindUI----查询记录界面

void ChangeUI(vector<Student> &t);//ChangeUI----修改记录界面

void DeleteMark(vector<Student> &t, vector<int>&del);//DeleteMark用于标记删除对象
void DeleteShow(vector<Student> &t, vector<int> &del);//DeleteShow用于展示被标记的对象姓名
void Delete(vector<Student> &t, vector<int> &del);//Delete用于删除被标记对象
void DeleteUI(vector<Student> &t, vector<int> &del);//DeleteUI----删除记录界面

void CreatSaveFileUI(fstream &outFile, string &outFileName);//CreatSaveFileUI----建立文件界面

void ReadFileUI(vector<Student> &t, fstream &inFile, string &inFileName);//ReadFileUI----读取文件界面

void SaveFileUI(vector<Student> &t, fstream &outFile, string &outFileName);//SaveFileUI----文件存储界面

void AddOne(vector<Student> &t);//AddOne从界面中增加单条学生记录
void AddUI(vector<Student> &t, fstream &infile, string &inFileName);//AddUI----增加学生记录界面--使用了读取文件功能

void NewBuildUI(vector<Student> &t, fstream &outfile, string &outFileName);//NewBuildUI----新建学生信息界面

void displayTable();//displayTable用于显示主功能菜单界面

void UI();//UI----主菜单界面











#endif // !TeacherClass
