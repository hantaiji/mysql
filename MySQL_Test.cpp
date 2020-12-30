#include <winsock.h>
#include <iostream>  
#include <string>  
#include <mysql.h>  
using namespace std;

#pragma comment(lib, "ws2_32.lib")  
#pragma comment(lib, "libmysql.lib")  

//单步执行，不想单步执行就注释掉  
#define STEPBYSTEP  

void Show_Menu();
void ExitSystem();
void Add_User();
void show_User();
void Del_User();
void Mod_User();
void Find_User();
void SQL_Option();
//必备的一个数据结构  
MYSQL mydata;
int main() {
	cout << "****************************************" << endl;
#pragma region link
#ifdef STEPBYSTEP  
	system("pause");
#endif  

	

	//初始化数据库  
	if (0 == mysql_library_init(0, NULL, NULL)) {
		cout << "mysql_library_init() succeed" << endl;
	}
	else {
		cout << "mysql_library_init() failed" << endl;
		return -1;
	}

#ifdef STEPBYSTEP  
	system("pause");
#endif  

	//初始化数据结构  
	if (NULL != mysql_init(&mydata)) {
		cout << "mysql_init() succeed" << endl;
	}
	else {
		cout << "mysql_init() failed" << endl;
		return -1;
	}

#ifdef STEPBYSTEP  
	system("pause");
#endif  

	//在连接数据库之前，设置额外的连接选项  
	//可以设置的选项很多，这里设置字符集，否则无法处理中文  
	if (0 == mysql_options(&mydata, MYSQL_SET_CHARSET_NAME, "gbk")) {
		cout << "mysql_options() succeed" << endl;
	}
	else {
		cout << "mysql_options() failed" << endl;
		return -1;
	}

#ifdef STEPBYSTEP  
	system("pause");
#endif  

	//连接数据库  
	if (NULL
		!= mysql_real_connect(&mydata, "localhost", "root", "htj1998928", "MySQL", 3306, NULL, 0))
		//这里的地址，用户名，密码，端口可以根据自己本地的情况更改  
		//地址:localhost 用户名:root 密码:htj1998928 端口/项目名:MySQL
	{
		cout << "mysql_real_connect() succeed" << endl;
	}
	else {
		cout << "mysql_real_connect() failed" << endl;
		return -1;
	}
#pragma endregion
#ifdef STEPBYSTEP  
	system("pause");
#endif  

	//sql字符串  
	string sqlstr;
#pragma region createTable
	//创建一个表  
	sqlstr = "CREATE TABLE IF NOT EXISTS user_info";
	sqlstr += "(";
	sqlstr +=
		"user_id INT  NOT NULL AUTO_INCREMENT PRIMARY KEY COMMENT '用户 ID',";
	sqlstr +=
		"user_name VARCHAR(100) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL COMMENT '用户姓名',";
	sqlstr +=
		"user_second_sum INT  NOT NULL DEFAULT 0 COMMENT '使用时长'";
	sqlstr += ");";
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		cout << "mysql_query() create table succeed" << endl;
	}
	else {
		cout << "mysql_query() create table failed" << endl;
		mysql_close(&mydata);
		return -1;
	}
#pragma endregion
#ifdef STEPBYSTEP  
	system("pause");
#endif  

	int choice = 0;
	while (true)
	{
		Show_Menu();
		cout << "输入您的选择：" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			ExitSystem();
			break;
		case 1:
			Add_User();
			break;
		case 2:
			show_User();
			break;
		case 3:
			Del_User();
			break;
		case 4:
			Mod_User();
			break;
		case 5:
			Find_User();
			break;
		case 6:
			SQL_Option();
			break;
		default:
			system("cls");
			break;
		}
	}
	mysql_close(&mydata);
	mysql_server_end();

	system("pause");
	return 0;
}

void Show_Menu()
{
	cout << "********************************" << endl;
	cout << "******欢迎使用职工管理系统******" << endl;
	cout << "******   0.退出管理程序   ******" << endl;
	cout << "******   1.增加职工信息   ******" << endl;
	cout << "******   2.显示职工信息   ******" << endl;
	cout << "******   3.删除离职职工   ******" << endl;
	cout << "******   4.修改职工信息   ******" << endl;
	cout << "******   5.查找职工信息   ******" << endl;
	cout << "******   6.SQL直接操作    ******" << endl;
	cout << "********************************" << endl;
}
void ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
/////
//
//
/////
////新增且只能增加一个用户 手动输入id 姓名 默认时长为NULL
//void Add_User121(int i)
//{}
//
//
////新增一个用户 需手动输入id  姓名 时长 返回整型供 xxx函数调用
////功能
////itrgdb:fdf
////
////fanh 
//int Add_User121666(int itrgd, int b)
//{
//	return i;
//}

///
//新增一个用户 用户可选新增数量 需手动输入id  姓名 时长
void Add_User()
{
 

	//Add_User121666(5);
	cout << "请输入添加的用户的数量：" << endl;
	int addNum = 0;
	cin >> addNum;
	for (int i = 0; i < addNum; i++)
	{
		string id;
		string name;
		string dSecond;
		string sqlstr;
		cout << "请输入第" << i + 1 << "个新职工编号：" << endl;
		cin >> id;
		cout << "请输入第" << i + 1 << "个新职工姓名：" << endl;
		cin >> name;
		cout << "请输入第" << i + 1 << "个新职工使用时长：" << endl;
		cin >> dSecond;

		//向表中插入数据  
		sqlstr =
			"INSERT INTO user_info VALUES('";
		sqlstr += id;
		sqlstr += "','";
		sqlstr += name;
		sqlstr += "','";
		sqlstr += dSecond;
		sqlstr += "');";
		cout << sqlstr;
		/*sqlstr =
			"INSERT INTO user_info(user_name) VALUES('公司名称'),('一级部门'),('二级部门'),('开发小组'),('姓名');";*/
		if (0 == mysql_query(&mydata, sqlstr.c_str())) {
			cout << "mysql_query() insert data succeed" << endl;
		}
		else {
			cout << "mysql_query() insert data failed" << endl;
			//mysql_close(&mydata);
			system("pause");
			system("cls");
		}
	}
}

void show_User()
{
	string sqlstr;
	sqlstr = "SELECT * FROM user_info";
	MYSQL_RES *result = NULL;
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		cout << "mysql_query() select data succeed" << endl;

		//一次性取得数据集  
		result = mysql_store_result(&mydata);
		//取得并打印行数  
		int rowcount = mysql_num_rows(result);
		cout << "row count: " << rowcount << endl;

		//取得并打印各字段的名称  
		unsigned int fieldcount = mysql_num_fields(result);
		MYSQL_FIELD *field = NULL;
		for (unsigned int i = 0; i < fieldcount; i++) {
			field = mysql_fetch_field_direct(result, i);
			cout << field->name << "\t\t";
		}
		cout << endl;
		/*#ifdef STEPBYSTEP
		system("pause");
		#endif*/
		//打印各行  
		MYSQL_ROW row = NULL;
		row = mysql_fetch_row(result);
		while (NULL != row) {
			for (int i = 0; i < fieldcount; i++) {
				cout << row[i] << "\t\t\t";
			}
			cout << endl;
			row = mysql_fetch_row(result);
		}

	}
	else {
		cout << "mysql_query() select data failed" << endl;
		//mysql_close(&mydata);
		system("pause");
		system("cls");
	}
}
void Del_User()
{
	string id;
	string name;
	string sqlstr;
	sqlstr = "delete  from user_info where ";
	//sqlstr = "SELECT * FROM user_info";
	int a;
	cout << "按id删除请按1，按姓名删除请按2" << endl;
	cin >> a;
	switch(a)
	{
	case 1:
		cout << "请输入要删除人员的id:" << endl;
		cin >> id;
		sqlstr += "user_id=";
		sqlstr += id;
		sqlstr += ";";
		cout << sqlstr << endl;
		break;
	case 2:
		cout << "请输入要删除人员的姓名:" << endl;
		cin >> name;
		sqlstr += "user_name='";
		sqlstr += name;
		sqlstr += "';";
		cout << sqlstr << endl;
		break;
	default:
		system("cls");
		break;
	}
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		cout << "mysql_query() delete data succeed" << endl;

	}
	else {
		cout << "mysql_query() delete data failed" << endl;
		//mysql_close(&mydata);
		system("pause");
		system("cls");
	}
}
void Mod_User()
{
	string id;
	string name;
	string dSecond;
	string sqlstr;
	sqlstr = "update user_info set  ";
	cout << "请输入要修改人员的id：" << endl;
	cin >> id;
	int a;
	cout << "修改姓名请按1，修改使用时间请按2" << endl;
	cin >> a;
	switch (a)
	{
	case 1:
		cout << "请输入新姓名:" << endl;
		cin >> name;
		sqlstr += "user_name='";
		sqlstr += name;
		sqlstr += "' where user_id=";
		sqlstr += id;
		sqlstr += ";";
		cout << sqlstr << endl;
		break;
	case 2:
		cout << "请输入新时间:" << endl;
		cin >> dSecond;
		sqlstr += "user_second_sum='";
		sqlstr += dSecond;
		sqlstr += "' where user_id=;";
		sqlstr += id;
		sqlstr += ";";
		cout << sqlstr << endl;
		break;
	default:
		system("cls");
		break;
	}
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		cout << "mysql_query() insert data succeed" << endl;
	}
	else {
		cout << "mysql_query() insert data failed" << endl;
		//mysql_close(&mydata);
		system("pause");
		system("cls");
	}
	/*cout << "输入要修改的id" << endl;
	sqlstr = "update user_info set user_name=' ";
	cin >> name;
	sqlstr += name;
	sqlstr += "';";*/
}
void Find_User()
{
	string id;
	string name;
	string sqlstr;
	sqlstr = "select * from user_info where ";
	//sqlstr = "SELECT * FROM user_info";
	int a;
	cout << "按id查找请按1，按姓名查找请按2" << endl;
	cin >> a;
	switch (a)
	{
	case 1:
		cout << "请输入要查找人员的id:" << endl;
		cin >> id;
		sqlstr += "user_id=";
		sqlstr += id;
		sqlstr += ";";
		cout << sqlstr << endl;
		break;
	case 2:
		cout << "请输入要查找人员的姓名:" << endl;
		cin >> name;
		sqlstr += "user_name='";
		sqlstr += name;
		sqlstr += "';";
		cout << sqlstr << endl;
		break;
	default:
		system("cls");
		break;
	}
	MYSQL_RES *result = NULL;
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
	//if (0 == mysql_query(&mydata, a)) {
		cout << "mysql_query() select data succeed" << endl;

		//一次性取得数据集  
		result = mysql_store_result(&mydata);//这里“增删改查”都能执行到
		//取得并打印行数  
		int rowcount = mysql_num_rows(result);//貌似只有查找不会引发bug，可能是只有select会返回“数据集”，才能执行下面的结果，其他update insert delete不返回“数据集”，这条语句执行不下去
		cout << "row count: " << rowcount << endl;

		//取得并打印各字段的名称  
		unsigned int fieldcount = mysql_num_fields(result);
		MYSQL_FIELD *field = NULL;
		for (unsigned int i = 0; i < fieldcount; i++) {
			field = mysql_fetch_field_direct(result, i);
			cout << field->name << "\t\t";
		}
		cout << endl;
		/*#ifdef STEPBYSTEP
		system("pause");
		#endif*/
		//打印各行  
		MYSQL_ROW row = NULL;
		row = mysql_fetch_row(result);
		if (row == NULL)
		{
			cout << "记录为空！" << endl;
		}
		else
		{
			while (NULL != row) {
				for (int i = 0; i < fieldcount; i++) {
					cout << row[i] << "\t\t\t";
				}
				cout << endl;
				row = mysql_fetch_row(result);
			}
		}

	}
	else {
		cout << "mysql_query() select data failed" << endl;
		//mysql_close(&mydata);
		system("pause");
		system("cls");
	}
}
//void Find_User()
//{
//	//char a[50];
//	string sqlstr;
//	cout << "请输入查询语句"<< endl;
//	getchar();//之前按的回车会留在缓存区， cin的结束符，结束后，结束符还在缓存区；
//	//getchar()/getline()结束后，结束符不放入缓存区,因此加入该行防止下一行getline将之前的回车读入，导致直接跳过输入
//	getline(cin,sqlstr);
//	//cin.get(a, 50);
//	cout << sqlstr << endl;
//	MYSQL_RES *result = NULL;
//	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
//	//if (0 == mysql_query(&mydata, a)) {
//		cout << "mysql_query() select data succeed" << endl;
//
//		//一次性取得数据集  
//		result = mysql_store_result(&mydata);
//		//取得并打印行数  
//		int rowcount = mysql_num_rows(result);
//		cout << "row count: " << rowcount << endl;
//
//		//取得并打印各字段的名称  
//		unsigned int fieldcount = mysql_num_fields(result);
//		MYSQL_FIELD *field = NULL;
//		for (unsigned int i = 0; i < fieldcount; i++) {
//			field = mysql_fetch_field_direct(result, i);
//			cout << field->name << "\t\t";
//		}
//		cout << endl;
//		/*#ifdef STEPBYSTEP
//		system("pause");
//		#endif*/
//		//打印各行  
//		MYSQL_ROW row = NULL;
//		row = mysql_fetch_row(result);
//		if (row == NULL)
//		{
//			cout << "记录为空！" << endl;
//		}
//		else
//		{
//			while (NULL != row) {
//				for (int i = 0; i < fieldcount; i++) {
//					cout << row[i] << "\t\t\t";
//				}
//				cout << endl;
//				row = mysql_fetch_row(result);
//			}
//		}
//
//	}
//	else {
//		cout << "mysql_query() select data failed" << endl;
//		//mysql_close(&mydata);
//		system("pause");
//		system("cls");
//	}
//}
void SQL_Option()
{
	string sqlstr;
	cout << "请输入SQL语句"<< endl;
	getchar();//之前按的回车会留在缓存区， cin的结束符，结束后，结束符还在缓存区；
	//getchar()/getline()结束后，结束符不放入缓存区,因此加入该行防止下一行getline将之前的回车读入，导致直接跳过输入
	getline(cin,sqlstr);
	//cin.get(a, 50);
	cout << sqlstr << endl;
	//MYSQL_RES *result = NULL;
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		cout << "mysql_query() insert data succeed" << endl;
		show_User();
	}
	else {
		cout << "mysql_query() insert data failed" << endl;
		//mysql_close(&mydata);
		system("pause");
		system("cls");
	}
}