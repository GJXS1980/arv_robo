#include "ARV_USART.h"

ARV_USART::ARV_USART(char* port)
{
    fd = open( port, O_RDWR|O_NOCTTY|O_NDELAY);
    if(fd == -1)
    {
        cout<<"Not find Serial Port!"<<endl;
    }
}

bool ARV_USART::USART_Seting(int speed,int flow_ctrl,int databits,int stopbits,int parity)
{
    unsigned int  i;
    int speed_arr[] = { B115200, B19200, B9600, B4800, B2400, B1200, B300};	
    int name_arr[] = {115200, 19200, 9600, 4800, 2400, 1200, 300};
    struct termios options;

    if(tcgetattr(fd, &options) != 0)
    {
        cout<<".>>"<<endl;
        usleep(1000*400);
        cout<<"...>>"<<endl;
        usleep(1000*400);
        cout<<".....>>"<<endl;
        usleep(1000*400);
        cout<<"........>>"<<endl;
        cout<<"#######Open Serial Failure,NOT Find Serial Port Or NOT Permission#######"<<endl;
        return false;
    }
    //设置串口输入波特率和输出波特率
    for ( i= 0; i < sizeof(speed_arr) / sizeof(int);  i++)
    {
        if  (speed == name_arr[i])
        {
            cfsetispeed(&options, speed_arr[i]);
            cfsetospeed(&options, speed_arr[i]);
        }
    }

    //修改控制模式，保证程序不会占用串口
    options.c_cflag |= CLOCAL;
    //修改控制模式，使得能够从串口中读取输入数据
    options.c_cflag |= CREAD;
    //设置数据流控制
    switch(flow_ctrl)
    {
        case 0://不使用流控制
                options.c_cflag &= ~CRTSCTS;
                break;
        case 1://使用硬件流控制
                options.c_cflag |= CRTSCTS;
                break;
        case 2://使用软件流控制
                options.c_cflag |= IXON | IXOFF | IXANY;
                break;
    }
    //设置数据位 屏蔽其他标志位
    options.c_cflag &= ~CSIZE;
    switch (databits)
    {
        case 5:
                options.c_cflag |= CS5;
                break;
        case 6:
                options.c_cflag |= CS6;
                break;
        case 7:
                options.c_cflag |= CS7;
                break;
        case 8:
                options.c_cflag |= CS8;
                break;
        default:
                cout<<"Unsupported data size"<<endl;
                return false;
    }
    //设置校验位
    switch (parity)
    {
        case 'n':
        case 'N': //无奇偶校验位。
                options.c_cflag &= ~PARENB;
                options.c_iflag &= ~INPCK;
                break;
        case 'o':
        case 'O'://设置为奇校验
                options.c_cflag |= (PARODD | PARENB);
                options.c_iflag |= INPCK;
                break;
        case 'e':
        case 'E'://设置为偶校验
                options.c_cflag |= PARENB;
                options.c_cflag &= ~PARODD;
                options.c_iflag |= INPCK;
                break;
        case 's':
        case 'S': //设置为空格
                options.c_cflag &= ~PARENB;
                options.c_cflag &= ~CSTOPB;
                break;
        default:
                cout<<"Unsupported parity"<<endl;;
                return false;
    }
    
    // 设置停止位
    switch (stopbits)
    {
        case 1:
                options.c_cflag &= ~CSTOPB; break;
        case 2:
                options.c_cflag |= CSTOPB; break;
        default:
                cout<<"Unsupported stop bits"<<endl;
                return false;
    }

 	/*******修改输出模式，原始数据输出(重点问题) **********/ 
    options.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);  
    options.c_oflag &= ~OPOST;  
    options.c_cflag |= CLOCAL | CREAD;  
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);  
    //设置等待时间和最小接收字符
    options.c_cc[VTIME] = 1; // 读取一个字符等待1*(1/10)s 
    options.c_cc[VMIN] = 1; //读取字符的最少个数为1 

    //如果发生数据溢出，接收数据，但是不再读取 刷新收到的数据但是不读
    tcflush(fd,TCIFLUSH);
    
    //激活配置 
    if (tcsetattr(fd,TCSANOW,&options) != 0)
    {
        cout<<"ARV_USART Seting Error!"<<endl;
        return false;
    }
    return true;
}

bool ARV_USART::Data_Write(unsigned char *send_buf,int data_len)
{
    int len = 0;
    len = write(fd,send_buf,data_len);
	
    if (len == data_len )
    {
        return len;
    }
    else
    {
        tcflush(fd,TCOFLUSH);
        return false;
    }

}

bool ARV_USART::Data_Read(unsigned char *rcv_buf,int data_len)
{
    int len,fs_sel;
    fd_set fs_read;
    struct timeval time;
    FD_ZERO(&fs_read);
    FD_SET(fd,&fs_read);
    time.tv_sec = 0;
    time.tv_usec = 1000*100;

    //使用select实现串口的多路通信
    fs_sel = select(fd+1,&fs_read,NULL,NULL,&time);
    if(fs_sel)
    {
        len = read(fd,rcv_buf,data_len);
        return len;
    }
    else
    {
        return false;
    }
    return true;
}

void ARV_USART::USART_CLEAN(void)
{

   tcflush(fd,TCIOFLUSH);

}


ARV_USART::~ARV_USART()
{
    close(fd);
}




