#ifndef _TESTMYSQL_H
#define _TESTMYSQL_H

//void connection_Mysql();
//void close_Mysql();
void mysql_Show_All_User();
void mysql_Add_One_User(char*,char*,char*);
void mysql_Delete_One_User(int);
void mysql_Change_One_User(char *id,char*,char*,char*);
int mysql_Show_One_User(char *attribute,char *content); 
int mysql_Judgment_User(char *id,char *password);//入库出库用户判断 
void mysql_Change_User_Password(char *password,char *user_id);







#endif
