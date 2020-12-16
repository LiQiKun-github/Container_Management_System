#ifndef _MENU_H_
#define _MENU_H_

#define MAINMENU    "\t\t*****************************************************\n"\
					"\t\t*****************************************************\n"\
					"\t\t***             1 操作人员登录                    ***\n"\
					"\t\t***             2 管理员登录                      ***\n"\
					"\t\t***             3 退出系统                        ***\n"\
					"\t\t*****************************************************\n"\
					"\t\t*****************************************************\n"\
					"\t\t\t\t请输入选项："


#define ADMINMENU  	"\t\t\t\t欢迎管理员登陆\n"\
 					"\t\t\t\t1 管理用户信息\n"\
					"\t\t\t\t2 管理物料信息\n"\
					"\t\t\t\t3 返回上一层\n"\
					"\t\t\t\t请输入选项："


#define ADMINUSERMENU	"\t\t\t\t1 单个出入库用户查询\n"\
						"\t\t\t\t2 全用户信息列表显示\n"\
						"\t\t\t\t3 用户增加\n"\
						"\t\t\t\t4 用户删除\n"\
						"\t\t\t\t5 用户修改\n"\
						"\t\t\t\t6 返回上一层\n"\
						"\t\t\t\t请输入选项："


#define ADMINMATERIALMENU	"\t\t\t\t1 物料查询\n"\
							"\t\t\t\t2 物料列表信息显示\n"\
							"\t\t\t\t3 物料增加\n"\
							"\t\t\t\t4 物料删除\n"\
							"\t\t\t\t5 物料修改\n"\
							"\t\t\t\t6 物料入库\n"\
							"\t\t\t\t7 物料出库\n"\
							"\t\t\t\t8 返回上一层\n"\
							"\t\t\t\t请输入选项："

#define USERMENU    "\t\t\t\t1 入库用户登录\n"\
					"\t\t\t\t2 出库用户登录\n"\
					"\t\t\t\t3 返回上一层\n"\
					"\t\t\t\t请输入选项："

#define INUSERMENU  "\t\t\t\t1 用户基本信息维护\n"\
					"\t\t\t\t2 查询操作\n"\
					"\t\t\t\t3 物品入柜操作\n"\
					"\t\t\t\t4 返回上一层\n"\
					"\t\t\t\t请输入选项："


#define OUTUSERMENU "\t\t\t\t1 用户基本信息维护\n"\
					"\t\t\t\t2 查询操作\n"\
					"\t\t\t\t3 物品出柜操作\n"\
					"\t\t\t\t4 返回上一层\n"\
					"\t\t\t\t请输入选项："

#define USERINFORMATIONMENU     "\t\t\t\t1 按用户编号查找\n"\
                                "\t\t\t\t2 按用户名查找\n"\
                                "\t\t\t\t3 查找所有入库用户\n"\
                                "\t\t\t\t4 查找所有出库用户\n"\
                                "\t\t\t\t5 返回上一层\n"\
                                "\t\t\t\t请输入选项："

void MainMenu();


void clear_flush();//清除缓存区



#endif

