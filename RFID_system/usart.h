#ifndef USART_H
#define USART_H
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <string.h>
#include <QObject>
#include <QThread>
#include <QCoreApplication>
#include <QtDebug>

#define   USB    "/dev/ttyUSB1"

//replace define
const int FALSE = -1;
const int TURE = 0;
using namespace std;

class USART :public QObject
{
    Q_OBJECT
public:
        int fd;

        USART(char* port);  //串口号

        int UART0_Set(int fd,int speed,int flow_ctrl,int databits,int stopbits,int parity);

        int UART0_Send(int fd,unsigned char *send_buf,int data_len);
        int UART0_Recv(int fd,unsigned char *rcv_buf,int data_len);

        float GET_TEMP(void);

        int temp_move(int size);

        int temp_distance(int mode);

        ~USART();
public slots:

//    void cardslots();
signals:


};


#endif // USART_H
