#include"StudentClass.h"


Student::Student(string s , string a , double ary[] , int n ) :Person(s, a), Num(n) {
	Rank = 0;
	memset(Mark, 0, sizeof(Mark));
	for (int i = 1; i <= Num; ++i)
	{
		Mark[i] = ary[i];
		Mark[0] += Mark[i];
	}
}
Student::Student(const Student&tmp):Person(tmp.Name, tmp.ID){
	//this->Name = tmp.Name;
	//this->ID = tmp.ID;
	this->Rank = tmp.Rank;
	this->Num = tmp.Num;
	for (int i = 1; i <= this->Num; ++i)
		this->Mark[i] = tmp.Mark[i];
	this->Mark[0] = tmp.Mark[0];
}
void Student::sum()
{
	Mark[0] = 0;
	for (int i = 1; i <= Num; ++i)
	{
		Mark[0] += Mark[i];
	}
}

//display用于在屏幕上显示记录
void Student::display(int n = 9) {
	cout << '*' << setw(8) << Name << '*' << setw(8) << ID << '*' << setw(8) << Rank << '*';
	cout << setw(8) << n << '*';
	for (int i = 1; i <= n; ++i)
		cout << setw(8) << Mark[i] << '*';
	cout << setw(8) << Mark[0] << '*' << endl;
}

//fileout用于文件输出
void Student::fileout(fstream &f) {
	f << ' ' << setw(8) << Name << ' ' << setw(8) << ID << ' ' << setw(8) << Rank << ' ' << setw(8) << Num;
	for (int i = 1; i <= Num; ++i)
		f << ' ' << setw(8) << Mark[i];
	f << ' ' << setw(8) << Mark[0] << endl;
}

//get用于返回学生信息，动态联编使用重载返回不同值
string Student::get(string act) {
	char act0 = act[0] - 1;
	switch (act0)
	{
	case '0':return Name; break;
	case '1':return ID; break;
	}
}
double Student::get(int act0) {
	switch (act0)
	{
	case 2:return Rank; break;
	case 3:return Mark[0]; break;
	case 4:return Num; break;
	}
}

