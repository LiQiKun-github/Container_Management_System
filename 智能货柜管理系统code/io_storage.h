#ifndef _IO_STORAGE_
#define _IO_STORAGE_

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#define BAUDRATE B115200 ///Baud rate : 115200

#define DEVICE "/dev/ttyS1"//设置你的端口号                                                          
//int nFd;

struct termios stNew;
struct termios stOld;
*/
typedef struct Head
{
  char head1;
  char head2;
  char len;
  char cmd;
  char data[0];
}Head;

typedef struct Head1
{
  char head1;
  char head2;
  char len;
  char data[0];
}Head1;

typedef struct Mycmd
{
  char cmd;
  int cmddata;
  char data[0];
}Mycmd;

typedef struct inData
{
  int id;//操作柜子编号
  char name[16];//操作物品编号
  int num;//存入物品数量
  int widget;//物品单个质量
  char data[0];
}inData;

typedef struct outData
{
  int id;//操作柜子编号
  char name[16];//操作物品编号
  int num;//存入物品数量
  int widget;//物品单个质量
  char data[0];
}outData;

typedef struct Tail
{
  char tail1;
  char tail2;
}Tail;


typedef struct Testn
{
  int data0;
  char data[0];
}Testn;

int SerialInit();
int in_Storage(inData m,int no_num);//入柜
int out_Storage(outData m,int no_num);//出柜
void show_One_Cabinet(Testn Mtdata,int id);//查询货柜物料数量




#endif
