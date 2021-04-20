#include "card.h"

Card::Card(string eventx)
{
        int           i;
        char          buf[256] = { 0 };
        unsigned char mask[EV_MAX/8 + 1];
        int           version;

        if ((fd = open(eventx.c_str(), O_RDONLY, 0)) >= 0)
        {
                   //输入输出控制设置
                   ioctl(fd, EVIOCGVERSION, &version);
                   ioctl(fd, EVIOCGNAME(sizeof(buf)), buf);
                   ioctl(fd, EVIOCGBIT(0, sizeof(mask)), mask);

                   //读取设备信息
                   cout<<"\t\t\t<*****设备信息*****>"<<endl;
                   cout<<"\t\t\t"<<input_eventx<<endl;
                   cout<<"\t\t\tevdev version:" <<(version >> 16)<<((version>>8)&0xff)<<(version & 0xff)<<endl;
                   cout<<"\t\tname:"<<buf<<endl;

                   //初始化结构体
                   for (i = 0; i < LED_MAX; i++)
                   {
                       i_event.time.tv_sec  = time(0);
                       i_event.time.tv_usec = 0;
                       i_event.type         = EV_LED;
                       i_event.code         = i;
                       i_event.value        = 0;
                       write(fd, &i_event, sizeof(i_event));
                   }
                   cout<<"\t\t\t\t请刷卡..."<<endl;
        }
        else
        {
            cout<<"\t\tOPEN RFID FAILED!!!"<<endl<<"Please check the port number and permissions"<<endl;

        }

}

Card::~Card()
{
    close(fd);
}


int Card::GET_ID(char* ID)
{
    static int  i = 0;
    static int ENTER = 1;      //数据重复处理

    int  rc;
    int  KEY;

    rc = read(fd, &i_event, sizeof(i_event));

    if(rc > 0)
    {
        if (i_event.type == EV_KEY && i_event.code <= BTN_MISC)
        {
            if(ENTER)
            {

                ENTER = 0;
                KEY = (i_event.code & 0xff)- 0x1;
                if(KEY == 27)
                {
                    ID[i] = '\0';
                    i = 0;
                    return 1;					//接受完毕
                }
                else sprintf(&ID[i++],"%d",KEY);

            }else ENTER = 1;

        }

    }

    return 0;
}



