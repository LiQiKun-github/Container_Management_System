#ifndef  _MATERIAL_MYSQL_H
#define  _MATERIAL_MYSQL_H

void mysql_Show_All_Material();

int mysql_Show_One_Material(int id);
void mysql_Add_One_Material(int id,char *name,int weight,int quantity);//添加物料
void mysql_Delete_One_Material(int id);//删除物料

void mysql_Change_One_Material(int id,char*,int,int);//修改物料信息


#endif
