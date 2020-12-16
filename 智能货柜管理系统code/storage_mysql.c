#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>
#include"storage_mysql.h"



MYSQL mysql;
MYSQL_RES *res;
MYSQL_ROW row;

int string_to_int(char *n)
{
	int l=strlen(n);
	int i=0,m=0;
	while(i<l)
	{
		m=m*10+n[i]-'0';
		i++;
	}
	return m;
}

int mysql_In_Storage_Judgment(char *id,int num)
{
  
  mysql_init(&mysql);
  if(!mysql_real_connect(&mysql, "localhost", "root", "123456", "testdb", 0, NULL, 0)) {
    printf("MySQL数据库连接失败！！！\n");
    return -1; 
  }
  char query[255];
  int flag,t;
  sprintf(query,"select * from material where id=\"%s\";",id);
  flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));
  if(flag) {
    printf("物品信息查询失败！！！\n");
    return -1; 
  }
  //mysql_store_result将全部的查询结果读取到客户端
  res = mysql_store_result(&mysql);
  if(!mysql_num_rows(res))
  {
    printf("查无此物！！！\n");
    return 0;
  }
  unsigned int fieldcount = mysql_num_fields(res);
  MYSQL_FIELD *field = NULL;
  //打印各字段名
  printf("仓库库存如下：\n");
  unsigned int i;
  for (i = 0; i < fieldcount; i++) {
    field = mysql_fetch_field_direct(res, i); 
    printf("%-20s",field->name);
  }
  printf("\n");
  //mysql_fetch_row检索结果集的下一行
  int weight;
  int _num;
  if((row = mysql_fetch_row(res)))
  {
    //mysql_num_fields返回结果集中的字段数目
    for(t=0; t<fieldcount; t++)
    {   
      printf("%-20s", row[t]);
    }
	weight=string_to_int(row[2]);
	_num=string_to_int(row[3]);
    printf("\n");
  }
	if(num>_num){printf("数量太大，别闹！！！\n");return 0;}
  mysql_close(&mysql);
  return weight;
}


void mysql_Inrefresh_Tables(char *id,int num,int no_num,int no_id)
{
//  printf("OK!\n");
  mysql_init(&mysql);
  if(!mysql_real_connect(&mysql, "localhost", "root", "123456", "testdb", 0, NULL, 0)) {
    printf("MySQL数据库连接失败！！！\n");
    return ;
  }
  char query[255];
  int flag;
  sprintf(query,"update container set name=\"%s\",quantity=quantity+\"%d\" where(id=\"%d\");",id,num,no_num*100+no_id);
  flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));
  if(flag) {
    printf("container表更新失败！！！\n");
    return ;
  }
char query1[64];

//update score_manage set  score = score - 积分 where id =1;
sprintf(query1,"update material set quantity=quantity-\"%d\" where (id=\"%s\");",num,id);
  flag = mysql_real_query(&mysql, query1, (unsigned int)strlen(query));
  if(flag) {
    printf("material表更新失败！！！\n");
    return ;
  }

  mysql_close(&mysql);

}

void mysql_Outrefresh_Tables(char *id,int num,int no_num,int no_id)
{
  
  mysql_init(&mysql);
  if(!mysql_real_connect(&mysql, "localhost", "root", "123456", "testdb", 0, NULL, 0)) {
    printf("MySQL数据库连接失败！！！\n");
    return ;
  }
  char query[255];
  int flag;
  sprintf(query,"update container set quantity=quantity-\"%d\" where(id=\"%d\");",num,no_num*100+no_id);
  flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));
  if(flag) {
    printf("container表更新失败！！！\n");
    return ;
  }
}
