#ifndef __ADMIN_H__
#define __TEST_H__



void Admin_Menu();//管理员菜单
void AdminUserMenu();//管理员用户信息管理菜单
void AdminMateralMenu();//管理员物料信息管理菜单

void show_One_User();//管理员查找用户信息菜单
void show_All_User();//管理员展示所有用户信息
void add_One_User();//管理员添加用户信息
void del_One_User();//管理员删除用户信息
void change_One_User();//管理员修改用户信息菜单

void id_Show_User();//通过编号查找用户
void name_Show_User();//拖过用户名查找用户
void show_All_In_Storage();//查找所有入库用户
void show_All_Out_Storage();//查找所有出库用户

void show_One_Material();
void show_All_Material();
void add_One_Material();//添加物料
void delete_One_Material();//删除物料
void change_One_Material();//修改物料



void admin_In_Storage();//入柜
void admin_Out_Storage();//出柜

#endif
