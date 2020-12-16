#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<mysql/mysql.h>
#include "testmysql.h"


MYSQL mysql;
MYSQL_RES *res;
MYSQL_ROW row;

void mysql_Show_All_User()
{

  char *query=NULL;
  int flag, t;
  mysql_init(&mysql);

  if(!mysql_real_connect(&mysql, "localhost", "root", "123456", "testdb", 0, NULL, 0)) {
	printf("Failed to connect to Mysql!\n");
	return ;
  }else {
	printf("Connected to Mysql successfully!\n");
  }
  query = "select * from user";
  //查询，成功则返回0
  flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));
  if(flag) {
	printf("Query failed!\n");
	return ;
  }else {
	printf("[%s] made...\n", query);
  }


  //mysql_store_result将全部的查询结果读取到客户端
  res = mysql_store_result(&mysql);
  unsigned int fieldcount = mysql_num_fields(res);
  MYSQL_FIELD *field = NULL;
  //打印各字段名
  unsigned int i;  
  for (i = 0; i < fieldcount; i++) {
	field = mysql_fetch_field_direct(res, i);        
	printf("%-20s",field->name);
  }
  printf("\n");
  //mysql_fetch_row检索结果集的下一行
  while((row = mysql_fetch_row(res))) {
	//mysql_num_fields返回结果集中的字段数目
	for(t=0; t<fieldcount; t++)
	{
	  printf("%-20s", row[t]);
	}
	printf("\n");
  }
  mysql_close(&mysql);	
}




void mysql_Add_One_User(char *name1,char *password1,char *functions1)
{
  char query[255];
  int flag, t;
  mysql_init(&mysql);
  if(!mysql_real_connect(&mysql, "localhost", "root", "123456", "testdb", 0, NULL, 0)) {
	printf("MySQL数据库连接失败！！！\n");
	return ;
  }
  sprintf(query,"insert into user(name,password,functions) values (\"%s\",\"%s\",\"%s\");",name1,password1,functions1);
  //插入，成功则返回0
  flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));
  if(flag) {
	printf("用户信息添加失败！\n");
  }
  strcpy(query,"select * from user order by id desc LIMIT 1;");
  //查询，成功则返回0
  flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));
  if(flag) {
	printf("查看添加用户的信息失败!\n");
	return ;
  }else {
	printf("添加的用户信息如下：\n");
  }
  //mysql_store_result将全部的查询结果读取到客户端
  res = mysql_store_result(&mysql);
  unsigned int fieldcount = mysql_num_fields(res);
  MYSQL_FIELD *field = NULL;
  //打印各字段名
  unsigned int i;  
  for (i = 0; i < fieldcount; i++) {
	field = mysql_fetch_field_direct(res, i);        
	printf("%-20s",field->name);
  }
  printf("\n");
  //mysql_fetch_row检索结果集的下一行
  row = mysql_fetch_row(res);
  //mysql_num_fields返回结果集中的字段数目
  for(t=0; t<fieldcount; t++)
  {
	printf("%-20s", row[t]);
  }
  printf("\n");
  mysql_close(&mysql);
}


void mysql_Delete_One_User(int id)
{
  //"delete from user  where id=4"
  mysql_init(&mysql);
  if(!mysql_real_connect(&mysql, "localhost", "root", "123456", "testdb", 0, NULL, 0)) {
	printf("MySQL数据库连接失败！！！\n");
	return ;
  }else {
	printf("MySQL数据库连接成功！！！\n");
  }
  char query[255];
  int flag;
  sprintf(query,"delete from user  where id=%d;",id);
  flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));
  if(flag) {
	printf("用户信息删除失败！！！\n");
  }else {
	printf("用户信息删除成功！！！\n");
  }
  mysql_close(&mysql);
}


int mysql_Show_One_User(char *attribute,char *content)
{
  //"select from user  where id=4"
  mysql_init(&mysql);
  if(!mysql_real_connect(&mysql, "localhost", "root", "123456", "testdb", 0, NULL, 0)) {
	printf("MySQL数据库连接失败！！！\n");
	return 0;
  }else {
	printf("MySQL数据库连接成功！！！\n");
  }
  char query[255];
  int flag,t;
  sprintf(query,"select * from user where %s=\"%s\";",attribute,content);
  flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));
  if(flag) {
	printf("用户信息查询失败！！！\n");
	return 0;
  }else {
	printf("用户信息查询成功！！！\n");
  }

  //mysql_store_result将全部的查询结果读取到客户端
  res = mysql_store_result(&mysql);
  if(!mysql_num_rows(res))
  {
	printf("查无此人！！！\n");
	return 0;
  }
  unsigned int fieldcount = mysql_num_fields(res);
  MYSQL_FIELD *field = NULL;
  //打印各字段名
  unsigned int i;  
  for (i = 0; i < fieldcount; i++) {
	field = mysql_fetch_field_direct(res, i);        
	printf("%-20s",field->name);
  }
  printf("\n");

  //mysql_fetch_row检索结果集的下一行
  while((row = mysql_fetch_row(res)))
  {
	//mysql_num_fields返回结果集中的字段数目
	for(t=0; t<fieldcount; t++)
	{
	  printf("%-20s", row[t]);
	}
	printf("\n");
  }
  mysql_close(&mysql);
  return 1;
}



void mysql_Change_One_User(char *id,char *name,char *password,char *functions)
{
  //update user set name = "likun", password = "10", functions = "10" where (id = "2");
  mysql_init(&mysql);
  if(!mysql_real_connect(&mysql, "localhost", "root", "123456", "testdb", 0, NULL, 0)) {
	printf("MySQL数据库连接失败！！！\n");
	return ;
  }else {
	printf("MySQL数据库连接成功！！！\n");
  }
  char query[255];
  int flag;
  sprintf(query,"update user set name=\"%s\",password=\"%s\",functions=\"%s\" where (id=\"%s\");",name,password,functions,id);
  flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));
  if(flag) {
	printf("用户信息更改失败！！！\n");
	return ;
  }else {
	printf("用户信息更改成功！！！\n");
  }
  mysql_close(&mysql);
}


int mysql_Judgment_User(char *id,char *password)
{
 mysql_init(&mysql);
  if(!mysql_real_connect(&mysql, "localhost", "root", "123456", "testdb", 0, NULL, 0)) {
	printf("MySQL数据库连接失败！！！\n");
	return -3;
  }else {
	printf("MySQL数据库连接成功！！！\n");
  }
  char query[255];
  sprintf(query,"select functions from user where id=\"%s\" and password=\"%s\"",id,password); 
  int flag = mysql_real_query(&mysql,query, (unsigned int)strlen(query)); 
  if(flag) {
		printf("数据库查询失败！！！\n"); return -3; 
  }
  else {
	//printf("用户信息核对成功！！！\n");
  }
  res = mysql_store_result(&mysql);
  if(!mysql_num_rows(res))
  {
	//printf("查无此人！！！\n");
	return -1;
  }
  else {
	row=mysql_fetch_row(res);
	if(strcmp(row[0],"入库")==0) return 1;
	else if(strcmp("出库",row[0])==0) return 0;
	else {
	 // printf("不属于入库和出库人员！！！\n");
	  return -2;
	}
  }
  mysql_close(&mysql);
  //return 1;
}


void mysql_Change_User_Password(char *password,char *id)
{
 mysql_init(&mysql);
  if(!mysql_real_connect(&mysql, "localhost", "root", "123456", "testdb", 0, NULL, 0)) {
	printf("MySQL数据库连接失败！！！\n");
	return ;
  }else {
	printf("MySQL数据库连接成功！！！\n");
  }
  char query[255];
	//update user set name = "likun", password = "10", functions = "10" where (id = "2");
  sprintf(query,"update user set password=\"%s\" where (id=\"%s\");",password,id); 
  int flag = mysql_real_query(&mysql,query, (unsigned int)strlen(query)); 
  if(flag) {
		printf("用户密码更改失败！！！\n"); return ; 
  }
  else {
	//printf("用户密码更改成功！！！\n");
  }
}
