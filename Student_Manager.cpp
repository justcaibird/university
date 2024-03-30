#include "Student_Manager.h"

//链接数据库
Student_Manager::Student_Manager()
{
	con = mysql_init(NULL);
	mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");
	if (!mysql_real_connect(con, host, user, password, database_name, port, NULL, 0)) {
		cout << "1111";
		exit(1);
	}
}

Student_Manager::~Student_Manager()
{
	mysql_close(con);
}


//初始界面
interfaces::interfaces() {

}
void interfaces::show() {
	cout << "Student Info Manager" << endl;
	cout << "choose your operation" << endl;
	cout << "1.add new" << endl;
	cout << "2.delete" << endl;
	cout << "3.update" << endl;
	cout << "4.research" << endl;
	cin >> choice;
	switch (choice)
	{
	case 1:
	{
		add_interface add;
		break;
	}
	case 2:
	{
		delete_interface dele;
		break;
	}
	case 3:
	{
		change_interface change;
		break;
	}
	case 4:
	{
		research_interface research;
		break;
	}
	default:
		break;
	}
}
//增加模块
bool Student_Manager::student_insert(Student& t)
{
	char sql[1024];
	sprintf_s(sql, "insert into students(student_id,student_name,class_id) values(%d,'%s',%d)", t.student_id, t.student_name.c_str(), t.class_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to INSERT data:Error:%s\n", mysql_error(con));
		return false;
	}
	return true;
}
add_interface::add_interface() {

	cout << "please enter the Info" << endl;
	cout << "student id" << endl;
	cin >> stu->student_id;
	cout << "name" << endl;
	cin >> stu->student_name;
	cout << "class id" << endl;
	cin >> stu->class_id;
	show(stu);
}
void add_interface::show(Student* stu) {
	Student_Manager::GetInstance()->student_insert(*stu);
}
add_interface::~add_interface() {
	delete stu;
}

//删除模块
void Student_Manager::student_del(Student& t)
{
	char sql[1024];
	sprintf_s(sql, "DELETE FROM students WHERE student_id='%d'"
		, t.student_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to DELETE data:Error:%s\n", mysql_error(con));
	}
}
delete_interface::delete_interface() {

	cout << "please enter the Info" << endl;
	cout << "student id" << endl;
	cin >> stu->student_id;
	show(stu);
}
void delete_interface::show(Student* stu) {
	Student_Manager::GetInstance()->student_del(*stu);
}
delete_interface::~delete_interface() {
	delete stu;
}

//修改模块
void Student_Manager::student_update(Student& t)
{
	char sql[1024];
	sprintf_s(sql, "UPDATE students SET student_name='%s',class_id='%d'"
		"where student_id='%d' ", t.student_name.c_str(), t.class_id, t.student_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to UPDATE data:Error:%s\n", mysql_error(con));
	}
}
change_interface::change_interface() {

	cout << "please enter the Info" << endl;
	cout << "student id" << endl;
	cin >> stu->student_id;
	cout << "name" << endl;
	cin >> stu->student_name;
	cout << "class id" << endl;
	cin >> stu->class_id;
	show(stu);
}
void change_interface::show(Student* stu) {
	Student_Manager::GetInstance()->student_update(*stu);
}
change_interface::~change_interface() {
	delete stu;
}

//查询模块
vector<Student> Student_Manager::student_select(string condition)
{
	vector<Student> stulist;
	char sql[1024];
	sprintf_s(sql, "SELECT* FROM students %s"
		, condition.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to update data:Error:%s\n", mysql_error(con));
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res)) {
		Student stu;
		stu.student_id = atoi(row[0]);
		stu.student_name = row[1];
		stu.class_id = atoi(row[2]);
		stulist.push_back(stu);
	}
	return stulist;
}
research_interface::research_interface() {
	cout << "input student id" << endl;
	cin >> stu->student_id;
	vector<Student> result = Student_Manager::GetInstance()->student_select("where student_id=" + std::to_string(stu->student_id));
	show(result);
}

void research_interface::show(vector<Student> res) {
	for (int i = 0; i < res.size(); i++) {
		cout << res[i].student_id << endl;
		cout << res[i].student_name << endl;
		cout << res[i].class_id << endl;
	}
}
research_interface::~research_interface() {
	delete stu;
}