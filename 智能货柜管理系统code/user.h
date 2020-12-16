#ifndef __USER_H__
#define __USER_H__



 struct User
{
    int id;//编号
    char name[20];//用户名
    char password[10];//密码
    char functions[10];//职能
}a;





void UserMenu();//不同用户选择登陆菜单
void InUserMenu();//入库用户菜单
void OutUserMenu();//出库用户菜单
int judgment_User();//入库出库用户判断
void change_User_Password();
void user_Show_One_Cabinet();//用户查询货柜
















#endif
