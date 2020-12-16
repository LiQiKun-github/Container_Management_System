#include "menu.h"
#include "user.h"
#include "admin.h"
#include <stdio.h>
#include <stdlib.h>
#include<stdio_ext.h>

void clear_flush()
{
  __fpurge(stdin);//清除缓存区
}


void MainMenu()
{
  char sel;
  int count=0;
  while(1)
  {
	system("clear");
  	printf("%s",MAINMENU);
	scanf("%c",&sel);
	clear_flush();
	if(sel<'1'||sel>'3')
	{
	  count++;
	  printf("你已经连续输入%d次,注意哦！！！\n",count);
	}
	int flag=-1;
	switch(sel)
	{
	  case '1':
		flag=judgment_User();
		if(flag==1) InUserMenu();
		else if(flag==0)OutUserMenu();
		break;

	  case '2':
	  	Admin_Menu();
		break;

	  case '3':
		return;
	}
  }
}
