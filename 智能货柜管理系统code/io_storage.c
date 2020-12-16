#include"io_storage.h"
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
int nFd = 0;
struct termios stNew;
struct termios stOld;
int SerialInit()
{
    nFd = open(DEVICE, O_RDWR|O_NOCTTY|O_NDELAY);
    if(-1 == nFd)
    {
        perror("Open Serial Port Error!\n");
        return -1;
    }

    if( (fcntl(nFd, F_SETFL, 0)) < 0 )
    {
        perror("Fcntl F_SETFL Error!\n");
        return -1;
    }

    if(tcgetattr(nFd, &stOld) != 0)
    {
        perror("tcgetattr error!\n");
        return -1;
    }

    stNew = stOld;
    cfmakeraw(&stNew);//将终端设置为原始模式，该模式下全部的输入数据以字节为单位被处理
    //set speed
    cfsetispeed(&stNew, BAUDRATE);//115200
    cfsetospeed(&stNew, BAUDRATE);

    //set databits
    stNew.c_cflag |= (CLOCAL|CREAD);
    stNew.c_cflag &= ~CSIZE;
    stNew.c_cflag |= CS8;
    //set parity

	stNew.c_cflag &= ~PARENB;
	stNew.c_iflag &= ~INPCK;
    //set stopbits

	stNew.c_cflag &= ~CSTOPB;
    stNew.c_cc[VTIME]=0;    //指定所要读取字符的最小数量
    stNew.c_cc[VMIN]=1; //指定读取第一个字符的等待时间，时间的单位为n*100ms
                //假设设置VTIME=0，则无字符输入时read（）操作无限期的堵塞
    tcflush(nFd,TCIFLUSH);  //清空终端未完毕的输入/输出请求及数据。
	if( tcsetattr(nFd,TCSANOW,&stNew) != 0 )
    {
        perror("tcsetattr Error!\n");
        return -1;
    }
    return nFd;
}


//串口发送入柜命令
//m  代表入库物料信息的结构体    no_num  代表柜号
//return   0代表入柜失败    1代表入柜成功
int in_Storage( inData m,int no_num)
{
  
  Tail t;
  t.tail1=0xAA;
  t.tail2=0x55;
  //inData m={2,"12580",10,3};
  inData *mdata=(inData*)malloc(sizeof(inData)+sizeof(Tail));
  *mdata=m;
  memcpy(mdata->data,&t,sizeof(Tail));
  Head *head=(Head*)malloc(sizeof(Head)+sizeof(inData)+sizeof(Tail));
  head->head1=0x5A;
  head->head2=0xA5;
  head->len=sizeof(Head)+sizeof(inData)+sizeof(Tail);
  head->cmd=0xC0+no_num;
  memcpy(head->data,mdata,sizeof(inData)+sizeof(Tail));

  int nRet = 0;
  int SIZE=255;//sizeof(Head1)+sizeof(Mycmd)+sizeof(Tail);
  char buf[SIZE];
  if( SerialInit() == -1 )
  {
	perror("SerialInit Error!\n");
	return 0;
  }
  bzero(buf, SIZE);

  printf("正在向串口发送数据，请稍等。。。。\n");

  sleep(1);
  //write(nFd,sendmsg,strlen(sendmsg));//向串口发送数据
  int ret=write(nFd,head,sizeof(Head)+sizeof(inData)+sizeof(Tail));//向串口发送数据
  printf("ret:%d\n",ret);

  printf("数据处理中请稍等。。。。\n");
  //串口接收部分
  nRet = read(nFd, buf, SIZE);
  if(-1 == nRet)
  {
	perror("Read Data Error!\n");
	//        break;
  }
  if(buf[2] <= nRet)
  {
	//buf[nRet] = 0;
	Mycmd cmd;
	memcpy(&cmd,&buf[3],sizeof(Mycmd));
	//printf("cmd:%x\ncmddata:%d\n",cmd.cmd,cmd.cmddata);
	printf("返回数据接收成功!!!\n");
	if(cmd.cmddata==0){
	  printf("存储成功！！！\n"); close(nFd); return 1;
	}
	else if(cmd.cmddata==1){
	  printf("该货柜已经被占用！！！\n");
	  close(nFd); return 0; 
	}
	else if(cmd.cmddata==2){
	  printf("超重！！！\n");
	  close(nFd); return 0; 
	}
	
  }
  close(nFd);
  return 0;
}








//串口执行出柜命令
//m  代表出库物料信息的结构体    no_num  代表柜号
//return  0代表入库操作不成功  1代表入库操作成功
int out_Storage( outData m,int no_num)
{
  
  Tail t;
  t.tail1=0xAA;
  t.tail2=0x55;
  //outData m={2,"12580",10};
  outData *mdata=(outData*)malloc(sizeof(outData)+sizeof(Tail));
  *mdata=m;
  memcpy(mdata->data,&t,sizeof(Tail));
  Head *head=(Head*)malloc(sizeof(Head)+sizeof(outData)+sizeof(Tail));
  head->head1=0x5A;
  head->head2=0xA5;
  head->len=sizeof(Head)+sizeof(outData)+sizeof(Tail);
  //head->cmd=0xC0+no_num;
  head->cmd=0xD0+no_num;
  memcpy(head->data,mdata,sizeof(outData)+sizeof(Tail));
  int nRet = 0;
  int SIZE=255;//sizeof(Head1)+sizeof(Mycmd)+sizeof(Tail);
  char buf[SIZE];
  if( SerialInit() == -1 )
  {
	perror("SerialInit Error!\n");
	return 0;
  }
  bzero(buf, SIZE);

  printf("正在向串口发送数据，请稍等。。。。\n");

  sleep(1);
  //write(nFd,sendmsg,strlen(sendmsg));//向串口发送数据
  int ret=write(nFd,head,sizeof(Head)+sizeof(outData)+sizeof(Tail));//向串口发送数据
  printf("ret:%d\n",ret);

  printf("数据处理中请稍等。。。。\n");
  //串口接收部分
  nRet = read(nFd, buf, SIZE);
  if(-1 == nRet)
  {
	perror("Read Data Error!\n");
	//        break;
  }
  if(buf[2] <= nRet)
  {
	//buf[nRet] = 0;
	Mycmd cmd;
	memcpy(&cmd,&buf[3],sizeof(Mycmd));
	//printf("cmd:%x\ncmddata:%d\n",cmd.cmd,cmd.cmddata);
	printf("返回数据接收成功!!!\n");
	if(cmd.cmddata==0){
	  printf("\n\t\t\t\t取出成功！！！\n"); close(nFd); return 1;
	}
	else if(cmd.cmddata==1){
	  printf("\n\t\t\t\t物品不符！！！\n");close(nFd); return 0; 
	}
	else if(cmd.cmddata==2){
	  printf("\n\t\t\t\t物品数量不足！！！\n");close(nFd); return 0;
	}
	else if(cmd.cmddata==3){
	  printf("\n\t\t\t\t该货柜为空！！！\n");close(nFd); return 0;
	}
	
  }
  close(nFd);
  return 0;
}



//通过串口命令返回货柜物料数量
//Mydata 发送数据的结构体     id  货柜号
void show_One_Cabinet(Testn Mydata,int id)
{
  	Tail t;
	t.tail1=0xAA;
	t.tail2=0x55;
	//Testn Mydata;
	//Mydata.data0=10;
	memcpy(Mydata.data,&t,sizeof(Tail));
	Head *head=(Head*)malloc(sizeof(Head)+sizeof(Testn)+sizeof(Tail));
	head->head1=0x5A;
	head->head2=0xA5;
	head->len=sizeof(Head)+sizeof(Testn)+sizeof(Tail);
	head->cmd=0xB0+id;
	memcpy(head->data,&Mydata,sizeof(Testn)+sizeof(Tail));
    int nRet = 0;
    int SIZE=255;//sizeof(Head1)+sizeof(Mycmd)+sizeof(Tail);
    char buf[SIZE];
    if( SerialInit() == -1 )
    {
        perror("SerialInit Error!\n");
        return ;
    }
    bzero(buf, SIZE);
		sleep(1);
        //write(nFd,sendmsg,strlen(sendmsg));//向串口发送数据
        int ret=write(nFd,head,sizeof(Head)+sizeof(Testn)+sizeof(Tail));//向串口发送数据
        printf("ret:%d\n",ret);

        //串口接收部分
        nRet = read(nFd, buf, SIZE);
        if(-1 == nRet)
        {
            perror("Read Data Error!\n");
    //        break;
        }
        if(buf[2] <= nRet)
        {
            //buf[nRet] = 0;
            printf("get over\n");
			Mycmd cmd;
			memcpy(&cmd,&buf[3],sizeof(Mycmd));
			printf("cmd:%x,cmddata:%d\n",cmd.cmd,cmd.cmddata);
        }

    close(nFd);
    return ;
}
















