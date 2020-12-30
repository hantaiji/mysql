#include <winsock.h>
#include <iostream>  
#include <string>  
#include <mysql.h>  
using namespace std;

#pragma comment(lib, "ws2_32.lib")  
#pragma comment(lib, "libmysql.lib")  

//����ִ�У����뵥��ִ�о�ע�͵�  
#define STEPBYSTEP  

void Show_Menu();
void ExitSystem();
void Add_User();
void show_User();
void Del_User();
void Mod_User();
void Find_User();
void SQL_Option();
//�ر���һ�����ݽṹ  
MYSQL mydata;
int main() {
	cout << "****************************************" << endl;
#pragma region link
#ifdef STEPBYSTEP  
	system("pause");
#endif  

	

	//��ʼ�����ݿ�  
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

	//��ʼ�����ݽṹ  
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

	//���������ݿ�֮ǰ�����ö��������ѡ��  
	//�������õ�ѡ��ܶ࣬���������ַ����������޷���������  
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

	//�������ݿ�  
	if (NULL
		!= mysql_real_connect(&mydata, "localhost", "root", "htj1998928", "MySQL", 3306, NULL, 0))
		//����ĵ�ַ���û��������룬�˿ڿ��Ը����Լ����ص��������  
		//��ַ:localhost �û���:root ����:htj1998928 �˿�/��Ŀ��:MySQL
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

	//sql�ַ���  
	string sqlstr;
#pragma region createTable
	//����һ����  
	sqlstr = "CREATE TABLE IF NOT EXISTS user_info";
	sqlstr += "(";
	sqlstr +=
		"user_id INT  NOT NULL AUTO_INCREMENT PRIMARY KEY COMMENT '�û� ID',";
	sqlstr +=
		"user_name VARCHAR(100) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL COMMENT '�û�����',";
	sqlstr +=
		"user_second_sum INT  NOT NULL DEFAULT 0 COMMENT 'ʹ��ʱ��'";
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
		cout << "��������ѡ��" << endl;
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
	cout << "******��ӭʹ��ְ������ϵͳ******" << endl;
	cout << "******   0.�˳��������   ******" << endl;
	cout << "******   1.����ְ����Ϣ   ******" << endl;
	cout << "******   2.��ʾְ����Ϣ   ******" << endl;
	cout << "******   3.ɾ����ְְ��   ******" << endl;
	cout << "******   4.�޸�ְ����Ϣ   ******" << endl;
	cout << "******   5.����ְ����Ϣ   ******" << endl;
	cout << "******   6.SQLֱ�Ӳ���    ******" << endl;
	cout << "********************************" << endl;
}
void ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}
/////
//
//
/////
////������ֻ������һ���û� �ֶ�����id ���� Ĭ��ʱ��ΪNULL
//void Add_User121(int i)
//{}
//
//
////����һ���û� ���ֶ�����id  ���� ʱ�� �������͹� xxx��������
////����
////itrgdb:fdf
////
////fanh 
//int Add_User121666(int itrgd, int b)
//{
//	return i;
//}

///
//����һ���û� �û���ѡ�������� ���ֶ�����id  ���� ʱ��
void Add_User()
{
 

	//Add_User121666(5);
	cout << "��������ӵ��û���������" << endl;
	int addNum = 0;
	cin >> addNum;
	for (int i = 0; i < addNum; i++)
	{
		string id;
		string name;
		string dSecond;
		string sqlstr;
		cout << "�������" << i + 1 << "����ְ����ţ�" << endl;
		cin >> id;
		cout << "�������" << i + 1 << "����ְ��������" << endl;
		cin >> name;
		cout << "�������" << i + 1 << "����ְ��ʹ��ʱ����" << endl;
		cin >> dSecond;

		//����в�������  
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
			"INSERT INTO user_info(user_name) VALUES('��˾����'),('һ������'),('��������'),('����С��'),('����');";*/
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

		//һ����ȡ�����ݼ�  
		result = mysql_store_result(&mydata);
		//ȡ�ò���ӡ����  
		int rowcount = mysql_num_rows(result);
		cout << "row count: " << rowcount << endl;

		//ȡ�ò���ӡ���ֶε�����  
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
		//��ӡ����  
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
	cout << "��idɾ���밴1��������ɾ���밴2" << endl;
	cin >> a;
	switch(a)
	{
	case 1:
		cout << "������Ҫɾ����Ա��id:" << endl;
		cin >> id;
		sqlstr += "user_id=";
		sqlstr += id;
		sqlstr += ";";
		cout << sqlstr << endl;
		break;
	case 2:
		cout << "������Ҫɾ����Ա������:" << endl;
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
	cout << "������Ҫ�޸���Ա��id��" << endl;
	cin >> id;
	int a;
	cout << "�޸������밴1���޸�ʹ��ʱ���밴2" << endl;
	cin >> a;
	switch (a)
	{
	case 1:
		cout << "������������:" << endl;
		cin >> name;
		sqlstr += "user_name='";
		sqlstr += name;
		sqlstr += "' where user_id=";
		sqlstr += id;
		sqlstr += ";";
		cout << sqlstr << endl;
		break;
	case 2:
		cout << "��������ʱ��:" << endl;
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
	/*cout << "����Ҫ�޸ĵ�id" << endl;
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
	cout << "��id�����밴1�������������밴2" << endl;
	cin >> a;
	switch (a)
	{
	case 1:
		cout << "������Ҫ������Ա��id:" << endl;
		cin >> id;
		sqlstr += "user_id=";
		sqlstr += id;
		sqlstr += ";";
		cout << sqlstr << endl;
		break;
	case 2:
		cout << "������Ҫ������Ա������:" << endl;
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

		//һ����ȡ�����ݼ�  
		result = mysql_store_result(&mydata);//�����ɾ�Ĳ顱����ִ�е�
		//ȡ�ò���ӡ����  
		int rowcount = mysql_num_rows(result);//ò��ֻ�в��Ҳ�������bug��������ֻ��select�᷵�ء����ݼ���������ִ������Ľ��������update insert delete�����ء����ݼ������������ִ�в���ȥ
		cout << "row count: " << rowcount << endl;

		//ȡ�ò���ӡ���ֶε�����  
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
		//��ӡ����  
		MYSQL_ROW row = NULL;
		row = mysql_fetch_row(result);
		if (row == NULL)
		{
			cout << "��¼Ϊ�գ�" << endl;
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
//	cout << "�������ѯ���"<< endl;
//	getchar();//֮ǰ���Ļس������ڻ������� cin�Ľ������������󣬽��������ڻ�������
//	//getchar()/getline()�����󣬽����������뻺����,��˼�����з�ֹ��һ��getline��֮ǰ�Ļس����룬����ֱ����������
//	getline(cin,sqlstr);
//	//cin.get(a, 50);
//	cout << sqlstr << endl;
//	MYSQL_RES *result = NULL;
//	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
//	//if (0 == mysql_query(&mydata, a)) {
//		cout << "mysql_query() select data succeed" << endl;
//
//		//һ����ȡ�����ݼ�  
//		result = mysql_store_result(&mydata);
//		//ȡ�ò���ӡ����  
//		int rowcount = mysql_num_rows(result);
//		cout << "row count: " << rowcount << endl;
//
//		//ȡ�ò���ӡ���ֶε�����  
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
//		//��ӡ����  
//		MYSQL_ROW row = NULL;
//		row = mysql_fetch_row(result);
//		if (row == NULL)
//		{
//			cout << "��¼Ϊ�գ�" << endl;
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
	cout << "������SQL���"<< endl;
	getchar();//֮ǰ���Ļس������ڻ������� cin�Ľ������������󣬽��������ڻ�������
	//getchar()/getline()�����󣬽����������뻺����,��˼�����з�ֹ��һ��getline��֮ǰ�Ļس����룬����ֱ����������
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