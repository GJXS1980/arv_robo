#include "process.h"
#include "mainwindow.h"
#include "card.h"
#include "usart.h"

Process::Process(QObject *parent) :  QThread(parent)
{
        IC = new Card(input_eventx);
        memset(ID,0,sizeof(ID));
}

void Process::run()
{
     while(1)
     {
         if(IC->GET_ID(ID))
         {
                send_rifdID(ID);
                qDebug()<<"send:"<<ID;

         }
         msleep(1);
      }

}

Process2::Process2(QObject *parent) :  QThread(parent)
{
        mlx90614 = new USART(USB);

        mlx90614->UART0_Set(mlx90614->fd,9600,0,8,1,'N');

        mlx90614->temp_distance(1);         // 1 额头 0 手心
        mlx90614->temp_move(0x75);         // 默认偏移 7

}

void Process2::run()
{
    int len;
    int t = 0;

    unsigned char rcv_buf[8] = {0};
    unsigned char send_buf[5]={0x40,0x01,0x01,0x40,0x0D};
    static int runs = 0 ;

     while(1)
      {

         runs++;
         if(runs %150 == 0)
         {
             len = mlx90614->UART0_Send(mlx90614->fd,send_buf,5);
             if(len > 0)                                        //发送成功
             {
                 len = 0;
                 len = mlx90614->UART0_Recv(mlx90614->fd,rcv_buf,8);

//                 for(int i=0; i<8; i++)
//                 {
//                   printf("%x ",rcv_buf[i]);
//                 }
//                 printf("\n");

                 if(len>0)
                 {
                      if(rcv_buf[3] == 0)                          //传感器读取成功
                     {
                            t = (rcv_buf[5]<<8) + rcv_buf[4];
                            Temp = t/100;                           //整数部分
                            t =  t % 100;                            //小数部分
                            Temp += (float) t /100 ;
                            send_Temperature(Temp);
                     }
                 }
             }

        }
        msleep(1);
      }
}
