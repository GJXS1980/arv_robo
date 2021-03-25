#ifndef __ARV_USART_H_
#define __ARV_USART_H_

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

using namespace std;

class ARV_USART
{
    public:
            
            ARV_USART(char* port);  
            bool USART_Seting(int speed,int flow_ctrl,int databits,int stopbits,int parity);
            bool Data_Write(unsigned char *send_buf,int data_len);
            bool Data_Read(unsigned char *rcv_buf,int data_len);
            void USART_CLEAN(void);
            ~ARV_USART();
   private:	
	   int fd;		

};

#endif
