#include<iostream>
#include<fstream>
#include<algorithm>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<iomanip>
#include<sstream>
//#include<direct.h>
#include<windows.h>
//#include "Students.h"
using namespace std;
class Student
{
private:
	string Name,ID;
	int Rank,Num;
	double Mark[10];
public:
	Student(string s="", string a="",double ary[]=0,int n=9 ):Name(s), ID(a),Num(n){
		Rank = 0;
		memset(Mark, 0, sizeof(Mark));
		for (int i = 1; i <= Num; ++i)
		{
			Mark[i] = ary[i];
			Mark[0] += Mark[i];
		}
	};
	Student(const Student&tmp) {
		this->Name = tmp.Name;
		this->ID = tmp.ID;
		this->Rank = tmp.Rank;
		this->Num = tmp.Num;
		for (int i = 1; i <= this->Num; ++i)
			this->Mark[i] = tmp.Mark[i];
		this->Mark[0] = tmp.Mark[0];
	}
	void sum()
	{
		Mark[0] = 0;
		for (int i = 1; i <= Num; ++i)
		{
			Mark[0] += Mark[i];
		}
	}
	template <typename T>
	void change(T s,int act,int i=-1) {
		switch (act)
		{
		case 0:Name=s; break;
		case 1:ID=s; break;
		}
	}
	void change(double s, int act, int i = -1) {
		Mark[i] = s;
	}
	void display(int n = 9) {
		cout << '*' << setw(8) << Name << '*' << setw(8) << ID << '*' << setw(8) << Rank << '*';
		cout << setw(8) << n << '*';
		for (int i = 1; i <= n; ++i)
			cout << setw(8) << Mark[i] << '*';
		cout << setw(8) << Mark[0] << '*' << endl;
	}
	void fileout(fstream &f) {
		f << Name << ' ' << ID << ' ' << ' ' << Rank << ' ' << Num;
		for (int i = 1; i <= Num; ++i)
			f << ' ' << Mark[i];
		f << ' ' << Mark[0] << endl;
	}
	string get(string act) {
		char act0 = act[0]-1;
		switch (act0)
		{
		case '0':return Name; break;  
		case '1':return ID; break;
		}
	}
	double get(int act0) {
		switch (act0)
		{
		case 2:return Rank; break;
		case 3:return Mark[0]; break;
		case 4:return Num; break;
		}
	}
	template <typename T>
	friend int Find(const vector<Student> &, T, T);
	friend bool compareName(const Student &, const Student &);
	friend bool compareID(const Student &, const Student &);
	friend bool compareSum(const Student &, const Student &);
	friend void fixRank(vector<Student> &);
};

const string constName[4] = { "姓名","学号","名次","科目数" };
vector<Student> stu;
vector<int> del;
fstream outFile,inFile;
string outFileName = "C:\\PANPANPAN\\_Program\\C++大作业2\\Debug\\studentout.txt";
string inFileName = "C:\\PANPANPAN\\_Program\\C++大作业2\\Debug\\student.txt";

bool isNULL(vector<Student> &t)
{
	if (t.empty()) { cout << "记录为空！！非法操作！！" << endl; return true; }
	return false;
}

void showTableTitle(int n=9)
{
	cout << '*' << setw(8) << constName[0] << '*' << setw(8) << constName[1] << '*' << setw(8) << constName[2] << '*';
	cout << setw(8) << constName[3] << '*';
	for (int i = 1; i <= n; ++i)
		cout << setw(7) << "成绩" << i << '*';
	cout << setw(8) << "总分" << '*' << endl;
}
void ShowTableUI(vector<Student>& t)
{
	if (isNULL(t))return;
	cout << ">您已选择 显示记录" << endl;
	showTableTitle(t[0].get(4));
	for (int i = 0; i < t.size(); ++i)
		t[i].display(t[0].get(4));
}

// Vector Sort
inline bool compareName(const Student &A, const Student &B)
{
	if (A.Name < B.Name)return true;
	else return false;
}
inline bool compareID(const Student &A, const Student &B)
{
	if (A.ID < B.ID)return true;
	else return false;
}
inline bool compareSum(const Student &A, const Student &B)
{
	if ((A.Mark[0] > B.Mark[0]) || ((A.Mark[0] == B.Mark[0]) && (A.ID < B.ID)))return true;
	else return false;
}
void SortUI(vector<Student> &t) 
{
	if (isNULL(t))return;
	cout << ">您已选择 记录排序 " << endl;
	cout << "请选择功能：" << endl;
	cout << "|1.对“姓名”排序|2.对“学号”排序|3.对“名次”排序|0.退出功能|" << endl << ">>>";
	string act;
	while (cin >> act)
	{
		if (act[0] == '0')return;
		if ((act.size() > 1) || (act[0] > '3') || (act[0] < '1')) {
			cout << "请输入正确序号！！" << endl;
			cout << "|1.对“姓名”排序|2.对“学号”排序|3.对“名次”排序|0.退出功能|" << endl << ">>>";
			continue;
		}
		else break;
	}
	cout << "是否逆序？（y/n）" << endl << ">>>";
	char s;
	cin >> s;
	int op = 0;
	if (s == 'y')op = 1;
	int len = t.size();
	if (act[0] == '1')if (!op)sort(t.begin(), t.end(), compareName);
	else sort(t.rbegin(), t.rend(), compareName);
	if (act[0] == '2')if (!op)sort(t.begin(), t.end(), compareID);
	else sort(t.rbegin(), t.rend(), compareID);
	if (act[0] == '3')if (!op)sort(t.begin(), t.end(), compareSum);
	else sort(t.rbegin(), t.rend(), compareSum);
	cout << "排序完成！" << endl;
}
void fixRank(vector<Student> &t)
{
	sort(t.begin(), t.end(), compareSum);
	for (int i = 0; i < t.size(); ++i)
		t[i].Rank = i + 1;	
}

template <typename T>
int Find(vector<Student> &t, T s, T act)
{
	for (int i = 0; i < t.size(); ++i)
		if (s == t[i].get(act))return i;
	return -1;
}
int FindUI0(vector<Student> &t)
{
	cout << "|1.通过“姓名”查询|2.通过“学号”查询|3.通过“名次”查询|0.退出功能|" << endl << ">>>";
	string act;
	while (cin >> act)
	{
		if (act[0] == '0')return -1;
		if ((act.size() > 1) || (act[0] > '3') || (act[0] < '1')) {
			cout << "请输入正确序号！！" << endl;
			cout << "|1.通过“姓名”查询|2.通过“学号”查询|3.通过“名次”查询|0.退出功能|" << endl << ">>>";
			continue;
		}
		else break;
	}
	int act0 = (int)act[0] - 48;
	cout << "请输入需要查询的" + constName[act0 - 1] << endl << ">>>";
	string s; int tt=-1;
	while (cin >> s)
	{
		if (act[0] < '3')break;
		stringstream ss;
		ss << s;
		ss >> tt;
		if (tt == -1)cout << "请输入正确数据！" << endl << ">>>";
		else break;
		ss.clear();
	}
	int pos;
	if (act[0]<'3') pos = Find(t, s, act);
	else pos = Find(t, tt, 2);
	if (pos == -1) { cout << "记录不存在！" << endl; return -1; }
	cout << "已找到：" << endl;
	showTableTitle(t[pos].get(4));
	t[pos].display(t[pos].get(4));
	return pos;
}
void FindUI(vector<Student> &t)
{
	if (isNULL(t))return;
	cout << ">您已选择 查询记录 " << endl;
	FindUI0(t);
}

void ChangeUI(vector<Student> &t)
{
	if (isNULL(t))return;
	cout << ">您已选择 修改记录 " << endl;
	cout << "请选择以何种方式查询需修改的记录：" << endl;
	int pos=FindUI0(t);
	if (pos == -1)return;
	string act;int act0;
	cout << "请输入需修改的数据：|1.姓名|2.学号|4~9.成绩|0.退出功能|" << endl << ">>>";
	while (cin >> act)
	{
		if (act[0] == '0')return;
		if (act.size() > 1 || (act[0] == '3') || (act[0] > '9') || (act[0] < '1')) {
			cout << "请输入正确序号！！" << endl;
			cout << "|1.姓名|2.学号|4~9.成绩|0.退出功能|" << endl << ">>>";
			continue;
		}
		else break;
	}
	cout << "请输入修改后的数据" << endl << ">>>";
	double tt=-1; string s;
	while (cin >> s)
	{
		if (act[0] < '4')break;
		stringstream ss;
		ss << s;
		ss >> tt;
		if (tt == -1)cout << "请输入正确数据！" << endl << ">>>";
		else break;
		ss.clear();
	}
	act0 = (int)act[0] - 48;
	if (act0 < 4)t[pos].change(s, act0);
	else t[pos].change(tt, 5, act0);
	fixRank(t);
	cout << "修改完成！";
}

void DeleteMark(vector<Student> &t,vector<int>&del)
{
	cout << "请选择以何种方式查询需删除的记录：" << endl;
	int pos = FindUI0(t);
	if (pos == -1)return;
	del.push_back(pos);
	cout << "记录已标记！" << endl;
}
void DeleteShow(vector<Student> &t, vector<int> &del)
{
	if (del.empty()) { cout << "标记为空！！" << endl; return; }
	cout << "已被标记的名字为：" << endl;
	for (auto i : del)
	{
		cout << t[i].get("1")<<' ';
	}
	cout << endl;
}
void Delete(vector<Student> &t, vector<int> &del)
{
	if (del.empty()) { cout << "标记为空！！" << endl; return; }
	string s;
	while (1)
	{
		cout << "确认删除" << del.size() << "条记录？(y/n)" << endl << ">>>";
		if ((s.size() > 1) || (s[0] != 'y') || (s[0] != 'n')) { cout << "请输入y/n！！" << endl; continue; }
		else break;
	}
	if (s[0] == 'n') { cout << "取消删除！" << endl; return; }
	for (int i = 0; i < t.size(); ++i)
		t.erase(t.begin() + del[i] - 1);
	del.clear();
	cout << "删除完成！标记已清空！" << endl;
	fixRank(t);
}
void DeleteUI(vector<Student> &t,vector<int> &del)
{
	if (isNULL(t))return;
	cout << ">您已选择 删除记录 " << endl;
	cout << "请选择功能：" << endl;
	cout << "|1.选择方式标记记录|2.显示已被标记的记录名字|3.删除被标记的记录|4.清空标记|0.退出功能|" << endl << ">>>";
	string act;
	while (cin >> act)
	{
		if (act[0] == '0')return;
		if (act.size() > 1 || (act[0] > '4') || (act[0] < '1')) {
			cout << "请输入正确序号！！" << endl;
			cout << "|1.选择方式标记记录|2.显示已被标记的记录名字|3.删除被标记的记录|4.清空标记|0.退出功能|" << endl << ">>>";
			continue;
		}
		char act0 = act[0];
		switch (act0)
		{
		case '1':DeleteMark(t, del); break;
		case '2':DeleteShow(t, del); break;
		case '3':Delete(t, del); break;
		case '4':del.clear(); cout << "标记已清空！" << endl; break;
		}
		cout << "|1.选择方式标记记录|2.显示已被标记的记录名字|3.删除被标记的记录|4.清空标记|0.退出功能|" << endl << ">>>";
	}	
}

void CreatSaveFileUI(fstream &outFile,string &outFileName)
{
	cout << ">您已选择 建立文件 " << endl;
	cout << "请选择功能：" << endl;
	cout << "|1.使用默认文件名建立存储文件|2.使用指定文件名建立存储文件|0.退出功能|" << endl;
	cout << "当前默认文件：" << outFileName << endl << ">>>";
	string act;
	
	while (cin >> act)
	{
		if (act[0] == '0')return;
		if ((act.size() > 1) || (act[0] > '2') || (act[0] < '1')) {
			cout << "请输入正确序号！！" << endl;
			cout << "|1.使用默认文件名建立存储文件|2.使用指定文件名建立存储文件|0.退出功能|" << endl << ">>>";
			continue;
		}
		else break;
	}
	char select = act[0];
	switch ( select)
	{
	case '1':outFile.open(outFileName,ios::out); break;
	case '2':cout << "请输入指定文件路径：\n>>>";
			 cin >> outFileName;
			 outFile.open(outFileName,ios::out);
			 break;
	}
	if (outFile.is_open())cout << "文件已建立！地址：" << outFileName << endl;
	else cout << "文件建立失败！将退出当前功能！" << endl;
}

void ReadFileUI(vector<Student> &t, fstream &inFile, string &inFileName)
{
	cout << ">您已选择 读取文件 " << endl;
	cout << "请选择功能：" << endl;
	cout << "|1.使用当前默认文件名读取文件|2.使用指定文件名读取文件|0.退出功能|" << endl;
	cout << "当前默认文件：" << inFileName << endl << ">>>";
	string act;
	while (cin >> act)
	{
		if (act[0] == '0')return;
		if ((act.size() > 1) || (act[0] > '2') || (act[0] < '1')) {
			cout << "请输入正确序号！！" << endl;
			cout << "|1.使用当前默认文件名读取文件|2.使用指定文件名读取文件|0.退出功能|" << endl << ">>>";
			continue;
		}
		else break;
	}
	char select = act[0];
	switch (select)
	{
	case '1':inFile.open(inFileName,ios::in); break;
	case '2':cout << "请输入指定文件路径：\n>>>";
		cin >> inFileName;
		inFile.open(inFileName,ios::in);
		break;
	}
	if (inFile.is_open())cout << "文件已打开！地址：" << inFileName << endl;
	else { cout << "文件打开失败！将退出当前功能！" << endl; return; }
	string s;
	getline(inFile, s);
	while (!inFile.eof())
	{
		string name, id;
		int rank, num;
		double ary[10],sum;
		inFile >> name >> id >> rank >> num;
		for (int i = 1; i <= num; ++i)inFile >> ary[i];
		t.push_back(Student(name, id, ary, num));
		inFile >> sum;
	}
	fixRank(t);
	cout << "文件读取完毕！当前已有记录：" << t.size() << endl;
	inFile.close();
}

void SaveFileUI(vector<Student> &t, fstream &outFile, string &outFileName)
{
	if (isNULL(t))return;
	if (!outFile.is_open()) { cout << "文件未打开！" << endl; return; }
	cout << ">您已选择 文件存储" << endl;
	outFile << "姓名   " << "学号      " << "名次   " << "科目数 ";
	for (int i = 1; i <= (double)t[0].get(4); ++i)
		outFile << "成绩" << i << " ";
	outFile << "总成绩" << endl;
	for (int i = 0; i < t.size(); ++i)
		t[i].fileout(outFile);
	cout << "记录已保存于" << outFileName << endl;
}


void AddOne(vector<Student> &t)
{
	cout << "请输入学生姓名、学号：" << endl << ">>>";
	string s1, s2; int num; double ary[10];
	cin >> s1 >> s2;
	cout << "请输入科目数：" << endl << ">>>";
	cin >> num;
	cout << "请输入" << num << "科成绩：" << endl << ">>>";
	memset(ary, 0, sizeof(ary));
	for (int i = 1; i <= num; ++i)
		cin >> ary[i];
	t.push_back(Student(s1, s2, ary, num));
	cout << "信息已添加完成！" << endl;
	fixRank(t);
}
void AddUI(vector<Student> &t, fstream &infile, string &inFileName)
{
	cout << ">您已选择 增加学生记录" << endl;
	cout << "请选择功能：" << endl;
	cout << "|1.增加新学生记录|2.使用文件追加记录|0.退出功能|" << endl << ">>>";
	string s;
	while (cin>>s)
	{
		char act = s[0];
		switch (act)
		{
		case '0':return; break;
		case '1':AddOne(t); break;
		case '2':ReadFileUI(t, inFile, inFileName); return; break;
		default:cout << "请输入正确序号！" << endl;break;
		}
		cout << "|1.增加新学生记录|2.使用文件追加记录|0.退出功能|" << endl << ">>>";
	}
}

void NewBuildUI(vector<Student> &t, fstream &outfile, string &outFileName)
{
	cout << "您已选择 新建学生信息" << endl;
	if (t.empty()) { cout << "记录为空！无需新建！" << endl; return; }
	cout << "当前记录不为空！是否以追加方式记录（y/n）" << endl << ">>>";
	string s;
	cin >> s;
	if (s[0] == 'y') { cout << "记录未更改！将继续追加！" << endl; return; }
	cout << "是否保存已有记录（y/n）" << endl << ">>>";
	cin >> s;
	if (s[0] == 'y') { cout << "自动跳转至文件存储功能！" << endl; SaveFileUI(t,outfile, outFileName); }
	cout << "是否删除现有记录（y/n）" << endl << ">>>";
	cin >> s;
	if (s[0] == 'y') { t.clear(); cout << "记录已删除！！！" << endl; return; }
	if (s[0] == 'n') { cout << "记录未更改！" << endl; }
}

void displayTable()
{
	cout << endl;
	cout << "-------------------------主菜单-------------------------" << endl;
	cout << "|1.建立文件|2.读取文件       |3.新建学生信息|4.文件存储|" << endl;
	cout << "|5.显示记录|6.增加学生记录   |7.删除记录    |8.修改记录|" << endl;
	cout << "|9.查询记录|10.对记录进行排序|              |0.退出程序|" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << ">>>";
}

void UI()
{
	string act;
	cout << "---------欢迎使用学生成绩管理系统！---------" << endl;
	cout << "请输入功能对应的序号进行操作：" << endl;
	displayTable();
	while (cin >> act)
	{
		//char select = act[0];
		int select=-1;
		stringstream ss;
		ss << act;ss >> select;
		ss.clear();
		switch (select)
		{
		case 1:CreatSaveFileUI(outFile, outFileName); break;
		case 2:ReadFileUI(stu, inFile, inFileName); break;
		case 3:NewBuildUI(stu, outFile, outFileName); break;
		case 4:SaveFileUI(stu, outFile, outFileName); break;
		case 5:ShowTableUI(stu); break;
		case 6:AddUI(stu, inFile, inFileName); break;
		case 7:DeleteUI(stu, del); break;
		case 8:ChangeUI(stu); break;
		case 9:FindUI(stu); break;
		case 10:SortUI(stu); break;
		case 0:cout << "再见！" << endl; inFile.close(); outFile.close(); stu.clear(); del.clear(); return; break;
		default:cout << "请输入正确序号！！" << endl; displayTable(); continue; break;
		}


		displayTable();
	}
}

int main()
{
	UI();
	//Sleep(1000);
	return 0;

}