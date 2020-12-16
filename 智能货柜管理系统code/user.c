#include<stdio.h>
#include<stdlib.h>
#include"menu.h"
#include"user.h"
#include"testmysql.h"
#include"admin.h"
#include"io_storage.h"

static char user_id[20]="2";
void UserMenu()
{
	char sel;
	int count=0;
	while(1) {
		printf("%s",USERMENU);
		scanf("%c",&sel);
		clear_flush();
		if(sel<'1'||sel>'3') {
			count++;
			printf("你已经连续输入%d次,注意哦！！！\n",count);
		}
		switch(sel) {
			case '1':
				InUserMenu();//入库用户菜单
				break;

			case '2':
				OutUserMenu();//出库用户菜单
				break;

			case '3':
				return;
		}
	}
 }

void InUserMenu() { //入库用户菜单
	char sel;
	int count=0;
	while(1) {
		printf("%s",INUSERMENU);
		scanf("%c",&sel);
		clear_flush();
		if(sel<'1'||sel>'4') {
			count++;
			printf("你已经连续输入%d次,注意哦！！！\n",count);
		}
		switch(sel) {
			case '1':
			    change_User_Password();//更改用户密码
				break;

			case '2':
				user_Show_One_Cabinet();//用户查询货柜
				break;

			case '3':
				admin_In_Storage();
				break;

			case '4':
				return;
		}
	}
}
void OutUserMenu() { //出库用户菜单
	char sel;
	int count=0;
	while(1) {
		printf("%s",OUTUSERMENU);
		scanf("%c",&sel);
		clear_flush();
		if(sel<'1'||sel>'4') {
			count++;
			printf("你已经连续输入%d次,注意哦！！！\n",count);
		}
		switch(sel) {
			case '1':
			  change_User_Password();
				break;

			case '2':
				user_Show_One_Cabinet();//用户查询货柜
				break;

			case '3':
				admin_Out_Storage();
				break;

			case '4':
				return;
		}
	}
}




int judgment_User()
{
  int n=0;
  while(n!=3){
  printf("请输入你的编号：");
  char user_id[20];
 scanf("%s",user_id);// gets(user_id);
  clear_flush();
  printf("请输入你的密码：");
  char password[32];
  scanf("%s",password);//gets(password);
  clear_flush();
  int flag=mysql_Judgment_User(user_id,password);
  if(1==flag) return 1;
  else if(0==flag) return 0;
  else if(-1==flag){
	printf("用户或密码错误%d次！！！\n\n\n",++n);
  }
  else if(-2==flag){
	  printf("用户不属于入库出库用户！！！请到管理员那里核对信息！！！\n");
	  printf("按任意建继续！！！");
	  getchar();
	  clear_flush();
	  return -1;
  }
  else printf("数据库操作错误！！！");
  }
  return -1;
}


void change_User_Password()
{
  printf("请输入你要修改后的密码：");
  char password[32];
  scanf("%s",password);
  //char user_id[20]="2";
  mysql_Change_User_Password(password,user_id);
}

void user_Show_One_Cabinet()
{ 
  printf("输入储物箱号：");
  int id;scanf("%d",&id);clear_flush();
  Testn m;
  printf("输入货柜号：");
  scanf("%d",&m.data0);clear_flush();
  show_One_Cabinet(m,id);
}






