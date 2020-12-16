#include<stdio.h>
#include<mysql/mysql.h>
#include"material_mysql.h"
#include<string.h>

MYSQL mysql;
MYSQL_RES *res;
MYSQL_ROW row;

int mysql_Show_One_Material(int id)
{
  mysql_init(&mysql);
  if(!mysql_real_connect(&mysql, "localhost", "root", "123456", "testdb", 0, NULL, 0)) {
    printf("MySQL数据库连接失败！！！\n");
    return -1;
  }
  char query[255];
  int flag,t;
  sprintf(query,"select * from material where id=\"%d\";",id);
  flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));
  if(flag) {
    printf("物品信息查询失败！！！\n");
    return -1;
  }
  //mysql_store_result将全部的查询结果读取到客户端
  res = mysql_store_result(&mysql);
  if(!mysql_num_rows(res))
  {
    //printf("查无此物！！！\n");
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


void mysql_Add_One_Material(int id,char *name,int weight,int quantity)
{

  char query[255];
  int flag;
  mysql_init(&mysql);
  if(!mysql_real_connect(&mysql, "localhost", "root", "123456", "testdb", 0, NULL, 0)) {
    printf("MySQL数据库连接失败！！！\n");
    return ;
  }
  sprintf(query,"insert into material(id,name,weight,quantity) values (\"%d\",\"%s\",\"%d\",\"%d\");",id,name,weight,quantity);
  //插入，成功则返回0
  flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));
  if(flag) {
    printf("物料信息添加失败！\n");
  }
  else printf("物料信息添加成功！！！");
  mysql_close(&mysql);
}


void mysql_Show_All_Material()
{
  char query[255]="select * from material;";
  int flag, t;
  mysql_init(&mysql);
  if(!mysql_real_connect(&mysql, "localhost", "root", "123456", "testdb", 0, NULL, 0)) {
    printf("Failed to connect to Mysql!\n");
    return ;
  }else {
    printf("Connected to Mysql successfully!\n");
  }
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



void mysql_Delete_One_Material(int id)
{
  mysql_init(&mysql);
  if(!mysql_real_connect(&mysql, "localhost", "root", "123456", "testdb", 0, NULL, 0)) {
    printf("MySQL数据库连接失败！！！\n");
    return ;
  }
  char query[255];
  int flag;
  sprintf(query,"delete from material  where id=%d;",id);
  flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));
  if(flag) {
    printf("物料信息删除失败！！！\n");
  }else {
    printf("物料信息删除成功！！！\n");
  }
  mysql_close(&mysql);
}




void mysql_Change_One_Material(int id,char *name,int weight,int quantity)
{
  mysql_init(&mysql);
  if(!mysql_real_connect(&mysql, "localhost", "root", "123456", "testdb", 0, NULL, 0)) {
    printf("MySQL数据库连接失败！！！\n");
    return ;
  }
  char query[255];
  int flag;
  sprintf(query,"update material set name=\"%s\",weight=\"%d\",quantity=\"%d\" where (id=\"%d\");",name,weight,quantity,id);
  flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));
  if(flag) {
    printf("物料信息更改失败！！！\n");
    return ;
  }else {
    printf("物料信息更改成功！！！\n");                                                              
  }
  mysql_close(&mysql);

}




