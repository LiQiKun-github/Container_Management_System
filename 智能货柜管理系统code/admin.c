#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "testmysql.h"
#include "menu.h"
#include "user.h"
#include "admin.h"
#include "material_mysql.h"
#include "io_storage.h"
#include "storage_mysql.h"

//管理员菜单
void Admin_Menu()
{
    const char password[7]="123456";
    int flag=0;
    char password0[20];

    while(flag<=3)
    {
        printf("请输入管理员密码：");
        //gets(password0,20);
		scanf("%s",password0);
        clear_flush();
        if(strcmp(password0,password)==0)
        {
            break;
        }
        else printf("密码输入错误！！！\n");
        flag++;
        if(flag==3)
        {
            printf("管理员密码输入错误次数过多!!!\n");
            //		system("pause") ;
            return ;
        }
    }

    char sel;
    int count=0;
    while(1)
    {
        printf("\n%s",ADMINMENU);
        scanf("%c",&sel);
        clear_flush();
        if(sel<'1'||sel>'3')
        {
            count++;
            printf("你已经连续输入%d次,注意哦！！！\n",count);
            system("pause");
        }
        switch(sel)
        {
        case '1':
            AdminUserMenu();//管理员管理用户菜单
            break;

        case '2':
            AdminMateralMenu();//管理员管理物料菜单
            break;

        case '3':
            return;
        }
    }
}

//管理员管理用户菜单
void AdminUserMenu()
{
    char sel;
    int count=0;
    while(1)
    {
        printf("\n%s",ADMINUSERMENU);
        scanf("%c",&sel);
        clear_flush();
        if(sel<'1'||sel>'6')
        {
            count++;
            printf("你已经连续输入%d次,注意哦！！！\n",count);
            system("pause");
        }
        switch(sel)
        {
        case '1':
            show_One_User();//单个出入库用户查询
            //system("pause");
            break;

        case '2':
            show_All_User();//显示所有用户
            //system("pause");
            break;

        case '3':
            add_One_User();//添加一个用户
            //system("pause");
            break;

        case '4':
            del_One_User();//删除一个用户
            //system("pause");
            break;

        case '5':
            change_One_User();//修改一个用户
            //system("pause");
            break;

        case '6':
            return;
        }
    }
}

//管理员管理物料菜单
void AdminMateralMenu()
{
    char sel;
    int count=0;
    while(1)
    {
        printf("\n%s",ADMINMATERIALMENU);
        scanf("%c",&sel);
        clear_flush();
        if(sel<'1'||sel>'8')
        {
            count++;
            printf("\t\t\t\t你已经连续输入%d次,注意哦！！！\n",count);//system("pause");
        }
        switch(sel)
        {
        case '1':
            show_One_Material();
            //system("pause");
            break;

        case '2':
			show_All_Material();
            //system("pause");
            break;

        case '3':
            add_One_Material();
            //system("pause");
            break;

        case '4':
            delete_One_Material();
            //system("pause");
            break;

        case '5':
            change_One_Material();
            //system("pause");
            break;

        case '6':
            admin_In_Storage();
            //system("pause");
            break;

        case '7':
            admin_Out_Storage();
            //system("pause");
            break;

			case '8':
            return;
        }
    }
}

//显示一个用户信息
void show_One_User()
{
    char sel;
    int count=0;
    while(1)
    {
        printf("\n%s",USERINFORMATIONMENU);
        scanf("%c",&sel);
        clear_flush();
        if(sel<'1'||sel>'5')
        {
            count++;
            printf("\t\t\t\t你已经连续输入%d次,注意哦！！！\n",count);
        }
        switch(sel)
        {
        case '1':
            id_Show_User();//按用户编号查找
            //system("pause");
            break;

        case '2':
            name_Show_User();//按用户名查找
            //system("pause");
            break;

        case '3':
            show_All_In_Storage();//查找所有入库用户
            //system("pause");
            break;

        case '4':
            show_All_Out_Storage();//查找所有出库用户
            //system("pause");
            break;

        case '5':
            return;
        }
    }
}

//显示所有用户信息
void show_All_User()
{
  mysql_Show_All_User();
}

//添加一个用户信息
void add_One_User()
{
    printf("请输入添加的用户名：");
	scanf("%s",a.name);//gets(a.name,32);
	printf("\n");
	clear_flush();
	
    printf("请输入添加的用户密码：");
scanf("%s",a.password);//	gets(a.password,32);
	printf("\n");
	clear_flush();

    printf("请输入添加的用职能：");
scanf("%s",a.functions);	//gets(a.functions,32);
	printf("\n");
	clear_flush();

	mysql_Add_One_User(a.name,a.password,a.functions);
}

//管理员删除一个用户
void del_One_User()
{
  printf("请输入要删除的用户编号：");
  int id;
  scanf("%d",&id);
  clear_flush();
  mysql_Delete_One_User(id);
}


//通过编号查找用户
void id_Show_User()
{
  char id[20];
  char attribute[50]="id";
  printf("请输入你要查找的用户编号：");
  //scanf("%s\n",id);
scanf("%s",id);//  gets(id,20);
  clear_flush();

  mysql_Show_One_User(attribute,id);
}

//拖过用户名查找用户
void name_Show_User()
{
  char content[20];
  char attribute[10]="name";
  printf("请输入要查找的用户：");
scanf("%s",content);//  gets(content,20);
  clear_flush();
  mysql_Show_One_User(attribute,content);
}

//查找所有入库用户
void show_All_In_Storage()
{

  char content[20]="入库";
  char attribute[50]="functions";
  //printf("请输入你要查找的用户编号：");
  //scanf("%s\n",id);
  //gets(id);
  //clear_flush();
  mysql_Show_One_User(attribute,content);
}

//查找所有出库用户
void show_All_Out_Storage()
{
  char content[20]="出库";
  char attribute[50]="functions";
  mysql_Show_One_User(attribute,content);
}

//管理员修改用户信息
void change_One_User()
{
  char id[20];
  char name[16];
  char password[32];
  char functions[50];
  printf("输入你要修改的用户编号：");
 scanf("%s",id);// gets(id,20);
  printf("查询修改的用户信息如下：\n");
 if(!mysql_Show_One_User("id",id))
 {
   return ;
 }
  printf("请输入更改后的用户名：");
 scanf("%s",name);// gets(name,16);
  clear_flush();
  printf("请输入更改后的用户密码：");
  scanf("%s",password);//gets(password,32);
  clear_flush();
  printf("请输入更改后的用户职能：");
  scanf("%s",functions);//gets(functions,50);
  clear_flush();


  mysql_Change_One_User(id,name,password,functions);
}


//显示物料信息
void show_One_Material()
{
  int id;
  printf("请输入你要查询的物料编号：");
  scanf("%d",&id);
  clear_flush();
  if(!mysql_Show_One_Material(id)) printf("查无此物！！！");
}


//显示所有；物料信息
void show_All_Material()
{
  mysql_Show_All_Material();
}

//添加一种物料
void add_One_Material()
{
  printf("请输入你要添加的物料编号：");
  int id;
  scanf("%d",&id);
  clear_flush();
  if(mysql_Show_One_Material(id))
  {
	printf("所添加的物料已经存在");
	return ;
  }
  else {
	char name[45];
	int weight;
	int quantity;
	printf("请输入物料名称：");scanf("%s",name); clear_flush();printf("\n");
	printf("请输入物料重量：");scanf("%d",&weight); clear_flush();printf("\n");
	printf("请输入物料数量：");scanf("%d",&quantity); clear_flush();printf("\n");
    mysql_Add_One_Material(id,name,weight,quantity);
  } 
}


//删除物料
void delete_One_Material()
{
  printf("请输入你要删除的物料编号：");
  int id;
  scanf("%d",&id);
  clear_flush();
  if(!mysql_Show_One_Material(id))
  {
	printf("要删除的物料不存在！！！");
	return ;
  }
  else {
	mysql_Delete_One_Material(id);
  }
  
}


//改变物料信息
void change_One_Material()
{
  printf("请输入你要修改的物料编号：");
  int id;
  scanf("%d",&id);
  clear_flush();
  if(!mysql_Show_One_Material(id))
  {
	printf("要修改的物料不存在！！！");
	return ;
  }
  printf("请输入你要修改后名称：");
  char name[45];
  scanf("%s",name);//gets(name);
  clear_flush();

  printf("请输入你要修改后总量：");
  int weight;
  scanf("%d",&weight);
  clear_flush();

  printf("请输入你要修改后数量：");
  int quantity;
  scanf("%d",&quantity);
  clear_flush();
  mysql_Change_One_Material(id,name,weight,quantity);
}

//管理员执行入柜操作
void admin_In_Storage()
{
  inData m;
  printf("请输入你要入柜物料的编号：");
  scanf("%s",m.name);;clear_flush();
  printf("请输入你要入柜物料的数量：");
  scanf("%d",&m.num);clear_flush();
  //MyData m={2,"12580",10,3};
  int flag=mysql_In_Storage_Judgment(m.name,m.num);
  if(flag>0) {
	m.widget=flag;
  }
  else return;
  printf("请输入你要入柜的箱号：");
  int no_num;scanf("%d",&no_num);clear_flush();
  printf("请输入你要入柜的柜号：");
  scanf("%d",&m.id);clear_flush();
  if(in_Storage(m,no_num)) {
	mysql_Inrefresh_Tables(m.name,m.num,no_num,m.id);

  }
  //else printf("串口通信错误！！！！\n");
}

//管理员执行出柜操作
void admin_Out_Storage()
{
  outData m;
  printf("请输入你要出柜物料的编号：");
  scanf("%s",m.name);clear_flush();
  printf("请输入你要出柜物料的数量：");
  scanf("%d",&m.num);clear_flush();
  //MyData m={2,"12580",10,3};
  printf("请输入你要出柜的箱号：");
  int no_num;scanf("%d",&no_num);clear_flush();
  printf("请输入你要出柜的柜号：");
  scanf("%d",&m.id);clear_flush();
  if(out_Storage(m,no_num))
  {
	mysql_Outrefresh_Tables(m.name,m.num,no_num,m.id);
  }
}


