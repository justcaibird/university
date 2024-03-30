#pragma once
#include<mysql.h>
#include<iostream>
#include<string>
#include<vector>
using namespace std;
typedef struct Student {
	int student_id;
	string student_name;
	int class_id;
}Student;
class Student_Manager {
	Student_Manager();
	~Student_Manager();
public:
	static Student_Manager* GetInstance()  //µ¥ÀýÄ£Ê½
	{
		static Student_Manager DBManager;
		return &DBManager;
	}
public:
	bool student_insert(Student& t);
	void student_del(Student& t);
	void student_update(Student& t);
	vector<Student>student_select(string condition = ""); 
private:
	MYSQL* con;
	const char* host = "127.0.0.1";
	const char* user = "root";
	const char* password = "hys123456";
	const char* database_name = "test";
	const int port = 3306;
};

class interfaces {
private:
	int choice = 0;
public:
	Student* stu = new Student;
	interfaces();
	void show();
};

class add_interface :interfaces{
public:
	add_interface();
	~add_interface();
	void show(Student* stu);
};

class delete_interface :interfaces {
public:
	delete_interface();
	~delete_interface();
	void show(Student* stu);
};

class change_interface :interfaces {
public:
	change_interface();
	~change_interface();
	void show(Student* stu);
};

class research_interface :interfaces {
public:
	research_interface();
	~research_interface();
	void show(vector<Student>res);
};