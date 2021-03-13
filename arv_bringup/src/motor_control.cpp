#include "motor.h"
#define debug     0

/**************************************
Function: 主函数，ROS初始化，通过turn_on_motor类创建Robot_control对象并自动调用构造函数初始化
***************************************/
int main(int argc, char** argv)
{
	ros::init(argc, argv, "ARV_MOTOR_NODE");
	ROS_INFO("ARV_MOTOR node has turned on ");

	turn_on_motor Robot_Control; 
	Robot_Control.Signal_Handle();
	Robot_Control.motor_init();
	Robot_Control.Control();  //循环执行数据采集和发布topic等操作
	//signal(SIGINT, Robot_Control.Signal_Handle);
	return 0;
} 

/**************************************
Function: 捕捉信号函数，退出时，失能以及将速度清零
***************************************/
void* turn_on_motor::Signal_Handle()
{
	unsigned char speed_buf[12] = {0x01, 0x44, 0x23, 0x18, 0x33, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	unsigned char enable_buf[12] = {0x01, 0x44, 0x21, 0x00, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t crc_hl[2] = {0};

	//	速度清零
	CRC16CheckSum((unsigned char *)speed_buf, 10, crc_hl);//校验位计算
	speed_buf[10] = crc_hl[0];
	speed_buf[11] = crc_hl[1];
	MOTOR_Serial->Data_Write(speed_buf,sizeof(speed_buf));
	usleep(1000*10);
	MOTOR_Serial->USART_CLEAN();

	//	电机失能
	CRC16CheckSum((unsigned char *)enable_buf, 10, crc_hl);//校验位计算
	enable_buf[10] = crc_hl[0];
	enable_buf[11] = crc_hl[1];
	MOTOR_Serial->Data_Write(enable_buf,sizeof (enable_buf));
	usleep(1000*10);
	MOTOR_Serial->USART_CLEAN();

}
/**************************************
Function: 订阅回调函数Callback，根据订阅的指令向串口发控制协议开启和关闭某个传感器
***************************************/
void turn_on_motor::MOTOR_Enable_Callback(const std_msgs::Int32::ConstPtr &enable)
{
	unsigned char enable_buf[12]={0x01, 0x44, 0x21, 0x00, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t crc_hl[2] = {0};
	MOTOR_Serial->USART_CLEAN();
	switch(enable->data){
		case 0:	enable_buf[7] = 0x00; enable_buf[9] = 0x00; break;
		case 1:	enable_buf[7] = 0x01; enable_buf[9] = 0x00; break;
		case 2:	enable_buf[7] = 0x00; enable_buf[9] = 0x01; break;
		case 3:	enable_buf[7] = 0x01; enable_buf[9] = 0x01; break;
		default:	break;
	}
	
	CRC16CheckSum((unsigned char *)enable_buf, 10, crc_hl);//校验位计算
	enable_buf[10] = crc_hl[0];
	enable_buf[11] = crc_hl[1];
	//	printf("crc_hl[0] %02x crc_hl[1] %02x\n",crc_hl[0],crc_hl[1]);
	MOTOR_Serial->Data_Write(enable_buf,sizeof (enable_buf));
	usleep(1000*10);
	MOTOR_Serial->USART_CLEAN();
}

/**************************************
Function: 订阅速读设置回调函数，单位为M/S 最大速度为300转每秒，即2.6583 M/S
***************************************/
void turn_on_motor::SetSpeedCallback(const std_msgs::Float32MultiArray::ConstPtr &speed)
{
	unsigned char speed_buf[12] = {0x01, 0x44, 0x23, 0x18, 0x33, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	unsigned char crc_hl[2] = {0};	
	bool neg_flag[2];
	// float set_speed[2];	
	std_msgs::Float32MultiArray set_speed;
	set_speed.data = speed->data;

	//	速度限制
	if(set_speed.data[0] > 0.3){
		set_speed.data[0] = 0.3;
	}
	else if(set_speed.data[0] < -0.3){
		set_speed.data[0] = -0.3;
	}
	
	if(set_speed.data[1] > 0.3)
	{
		set_speed.data[1] = 0.3;
	}
	else if(set_speed.data[1] < -0.3)
	{
		set_speed.data[1] = -0.3;
	}
    // std::cout << "kinematics motor speed: " << set_speed << std::endl;

	//	速度变换（m/s --> r/min）	
	set_speed.data[0] = set_speed.data[0]*60/(pi*d);
	set_speed.data[1] = set_speed.data[1]*60/(pi*d);
	// set_speed.data[1]= set_speed.data[1]*60/(pi*d);

	//	判断速度的正负
	neg_flag[0] = set_speed.data[0]>0?true:false;
	neg_flag[1] = set_speed.data[1]>0?true:false;

	//	速度取绝对值
	set_speed.data[0] = fabs(set_speed.data[0]);
	set_speed.data[1] = fabs(set_speed.data[1]);

	//	速度四舍五入
	if(((int)(set_speed.data[0]*10)%10) >= 5){
		set_speed.data[0] = set_speed.data[0] + 1;
	}

	if(((int)(set_speed.data[1]*10)%10) >= 5){
		set_speed.data[1] = set_speed.data[1] + 1;
	}
	
	// 速度符号恢复
	if(!neg_flag[0]) set_speed.data[0] = -set_speed.data[0];
	if(!neg_flag[1]) set_speed.data[1] = -set_speed.data[1];

    // std::cout << "kinematics motor speed: " << set_speed << std::endl;

	MOTOR_Serial->USART_CLEAN();

	speed_buf[6] = ((int)set_speed.data[0]>>8)&0xff;
	speed_buf[7] = (int)set_speed.data[0]&0xff;
	// speed_buf[7]=(int)set_speed.data[0]&0xff;	
	speed_buf[8] = ((int)set_speed.data[1]>>8)&0xff;
	speed_buf[9] = (int)set_speed.data[1]&0xff;
	// speed_buf[9]=(int)set_speed.data[1]&0xff;	

	CRC16CheckSum((unsigned char *)speed_buf, 10, crc_hl);//校验位计算
	speed_buf[10] = crc_hl[0];
	speed_buf[11] = crc_hl[1];
	// speed_buf[11]=crc_hl[1];
	MOTOR_Serial->Data_Write(speed_buf,12);
	usleep(1000*10);
	MOTOR_Serial->USART_CLEAN();	
}


/**************************************
Function: 发布伺服电机错误码
***************************************/
void turn_on_motor::Publish_Motor_ERROR()
{
	std_msgs::Int32MultiArray ERROR; 	 
	unsigned char check_Data[12]={0};

	unsigned char driver_read_error_cmd[8] = {0x01, 0x43, 0x50, 0x12, 0x51, 0x12, 0x48, 0x9d}; 		//读取错误码
	memset(check_Data, 0, sizeof(check_Data));
	MOTOR_Serial->Data_Write(driver_read_error_cmd,12);
	usleep(1000*100);
	MOTOR_Serial->Data_Read(check_Data,sizeof(check_Data));

	ERROR.data.push_back(check_Data[7]);
	ERROR.data.push_back(check_Data[9]);
	ERROR_publisher.publish(ERROR);

}
/**************************************
Function: 串口通讯校验函数，数据包除最后一个字节，其他的全部数据按位异或的结果作为帧尾
***************************************/
unsigned char turn_on_motor::Check_Sum(uint8_t *rx,unsigned char Count_Number)
{
	unsigned char check_sum=0,k;
	for(k = 0; k < Count_Number;k++){
		check_sum = check_sum^rx[k];//按位异或
	}
	return check_sum;
}

void turn_on_motor::CountEncoder(int *NewEncoder,int *OldEncoder,int *turns)
{
	if((*NewEncoder<100) && (*OldEncoder>5500))  //0~5599  5600
	(*turns)++;
	if((*NewEncoder>5500) && (*OldEncoder<100))
	(*turns)--;
}

/**************************************
Function: 从串口读取数据获取私服电机的相关信息速度、编码器等信息
***************************************/
void turn_on_motor::Get_MOTOR_Data()
{
	static int NewEncoder_A = 0, OldEncoder_A = 0, NewEncoder_B = 0, OldEncoder_B = 0, Orin_Encoder_A = 0, Orin_Encoder_B = 0;
	static  bool start = true;
	unsigned char Receive_Data_Pr[12]={0};
	unsigned char crc_hl[2] = {0};
	unsigned char encoder_cmd[8] = {0x01,0x43,0x50,0x04,0x51,0x04,0x28,0x97};
	unsigned char speed_cmd[8] = {0x01,0x43,0x50,0x00,0x51,0x00,0x68,0x95};
	std_msgs::Int32MultiArray Encoder; 	
	std_msgs::Float32MultiArray Speed; 
	
	//１.读取两轴编码器  
	MOTOR_Serial->Data_Write(encoder_cmd,8);
	usleep(1000*10);
	MOTOR_Serial->Data_Read(Receive_Data_Pr,sizeof (Receive_Data_Pr));	//读串口数据
	CRC16CheckSum((unsigned char *)Receive_Data_Pr, 10, crc_hl);	//校验位计算
	if((Receive_Data_Pr[10] == crc_hl[0]) && (Receive_Data_Pr[11] == crc_hl[1])) //校验成功后赋值
	{
		#if debug
		printf("DATA1:\n");
		for(int i=0;i<12;i++)
		{
			printf("%02x ",Receive_Data_Pr[i]);
		}    
		printf("\n");
		#endif
		
		Receive_Data.Encoder_A = (Receive_Data_Pr[6] << 8|Receive_Data_Pr[7])&0xffff;
		Receive_Data.Encoder_B = (Receive_Data_Pr[8] << 8|Receive_Data_Pr[9])&0xffff;
		
		if(start){
			Orin_Encoder_A = Receive_Data.Encoder_A;
			Orin_Encoder_B = Receive_Data.Encoder_B;
			start = false;
		}
		
		OldEncoder_A = NewEncoder_A;
		OldEncoder_B = NewEncoder_B;
		
		NewEncoder_A = Receive_Data.Encoder_A;
		NewEncoder_B = Receive_Data.Encoder_B;
		
		CountEncoder(&NewEncoder_A, &OldEncoder_A, &MotorA_turns);
		CountEncoder(&NewEncoder_B, &OldEncoder_B, &MotorB_turns);
		
		Receive_Data.Encoder_A = 5599*MotorA_turns + Receive_Data.Encoder_A - Orin_Encoder_A;		//减掉初始位置
		Receive_Data.Encoder_B = 5599*MotorB_turns + Receive_Data.Encoder_B - Orin_Encoder_B;
		
		Encoder.data.push_back(Receive_Data.Encoder_A);
		Encoder.data.push_back(Receive_Data.Encoder_B);	
		Encoder_publisher.publish(Encoder);
		//printf("Receive_Data.Encoder_A %d\n",Receive_Data.Encoder_A);
		//printf("Receive_Data.Encoder_B %d\n",Receive_Data.Encoder_B);
   }
   
   memset(Receive_Data_Pr,0,sizeof(Receive_Data_Pr));
   usleep(1000*10);
   //2.读取两轴速度环   
   MOTOR_Serial->Data_Write(speed_cmd, sizeof(speed_cmd));  
   usleep(1000*10);
   MOTOR_Serial->Data_Read(Receive_Data_Pr, sizeof(Receive_Data_Pr));//读串口数据
   CRC16CheckSum((unsigned char *)Receive_Data_Pr, 10, crc_hl);//校验位计算   
   if((Receive_Data_Pr[10] == crc_hl[0]) && (Receive_Data_Pr[11] == crc_hl[1])) //校验成功后赋值
   {
	   #if debug
	   printf("DATA2:\n");  
	   for(int i=0;i<12;i++)
	   {
		   printf("%02x ",Receive_Data_Pr[i]);
		}    
		printf("\n");
		#endif
		
		Receive_Data.Speed_A  = Receive_Data_Pr[6] == 0xff? -(~(Receive_Data_Pr[7]-1)&0xff):Receive_Data_Pr[7];
		Receive_Data.Speed_B  = Receive_Data_Pr[8] == 0xff? -(~(Receive_Data_Pr[9]-1)&0xff):Receive_Data_Pr[9];
		//printf("Receive_Data.Speed_A %d\n",Receive_Data.Speed_A);
		//printf("Receive_Data.Speed_B %d\n",Receive_Data.Speed_B);
		//Speed.data.push_back(Receive_Data.Speed_A);
		//Speed.data.push_back(Receive_Data.Speed_B);
		Speed.data.push_back(Receive_Data.Speed_A*pi*d/60);
		Speed.data.push_back(Receive_Data.Speed_B*pi*d/60);
		Speed_publisher.publish(Speed);
   }

}
/**************************************
Function: 相关控制代码，代码循环执行
***************************************/
void turn_on_motor::Control()
{
	// ros::Rate loop_rate(20);
	while(ros::ok())
	{
		MOTOR_Serial->USART_CLEAN();
		Get_MOTOR_Data(); 		 		//读取私服电子的编码器和速度
		Publish_Motor_ERROR(); 			//发布
		// loop_rate.sleep();
		ros::spinOnce();				//循环等待回调函数	  
	}
	Signal_Handle();	// 程序退出时给电机速度清零				
}


/**************************************
Function: 电机初始化函数，默认启动上电
***************************************/
void turn_on_motor::motor_init(void)
{
	unsigned char enable_buf[12] = {0x01,0x44,0x21,0x00,0x31,0x00,0x00,0x01,0x00,0x01,0x75,0x34};
	unsigned char driver_clear_cmd[8] = {0x01,0x06,0x46,0x02,0x00,0x00,0x3d,0x42};		 		//清楚警报
 	unsigned char driver_reset_cmd[8] = {0x01,0x06,0x46,0x03,0x00,0x01,0xad,0x42}; 				//重启电机
 	unsigned char driver_read_error_cmd[8] = {0x01,0x43,0x50,0x12,0x51,0x12,0x48,0x9d}; 		//读取错误码
 	unsigned char driver_read_enable_cmd[8] = {0x01,0x43,0x21,0x00,0x31,0x00,0x5b,0xa9}; 		//读取使能状态
	unsigned char check_Data[12]={1};
	int t = 0;
	while (check_Data[7] || check_Data[9] )														//上电电机检验
	{
		memset(check_Data, 0, sizeof(check_Data));
		MOTOR_Serial->Data_Write(driver_read_error_cmd, 8);
		usleep(1000*100);
		MOTOR_Serial->Data_Read(check_Data, sizeof(check_Data));
		t++;
		if(t==5)
		{
			MOTOR_Serial->Data_Write(driver_reset_cmd, 8);			//重启设备
			usleep(1000*100);
			MOTOR_Serial->USART_CLEAN();	
		} else if(t>5)
		{
			printf("电机故障,故障码：Moto-A:%02X  Moto-B:%02X\n", check_Data[7], check_Data[9]);
			exit(0);
		}
	}
	
	MOTOR_Serial->Data_Write(enable_buf, 12);
	usleep(1000*100);
	MOTOR_Serial->USART_CLEAN();
	ROS_INFO_STREAM("ARV_MOTOR Init OK");	
}

/**************************************
Function: STM32与电机模块的连接，及ROS话题的发布与订阅
***************************************/
turn_on_motor::turn_on_motor():MotorA_turns(0), MotorB_turns(0)
{
	memset(&Receive_Data, 0, sizeof(Receive_Data)); 
	ros::NodeHandle private_nh("~");
	private_nh.param<std::string>("usart_port_name", usart_port_name, "/dev/ttyS0");	//固定串口
	private_nh.param<int>("serial_baud_rate", serial_baud_rate, 115200);	//和下位机底层波特率115200
	
	Speed_publisher = n.advertise<std_msgs::Float32MultiArray>("/Motor_Speed", 1000);	//	电机速度话题			
	Encoder_publisher = n.advertise<std_msgs::Int32MultiArray>("/Motor_Encoder", 1000);	//	电机编码器数值话题
	ERROR_publisher = n.advertise<std_msgs::Int32MultiArray>("/Motor_ERROR_CODE", 1000);	//	电机错误码话题
	
	MOTOR_ENALBE_Sub = n.subscribe("/Motor_SetEnable_TOPIC", 1000,&turn_on_motor::MOTOR_Enable_Callback,this);	//	电机使能话题
	MOTOR_SetSpeed_Sub  = n.subscribe("/Motor_SetSpeed_TOPIC", 1000,&turn_on_motor::SetSpeedCallback,this);	//	电机速度设置话题

	MOTOR_Serial = new ARV_USART((char*)usart_port_name.data());	//	连接端口
	MOTOR_Serial->USART_Seting(serial_baud_rate, 0, 8, 1, 'N');	//	设置波特率
	if(MOTOR_Serial->USART_Seting(serial_baud_rate, 0, 8, 1, 'N') != false)
	{
		ROS_INFO_STREAM("Data ready");
	} 
	else
	{
		exit(0);
	}
}

/**************************************
Function: 析构函数 
***************************************/
turn_on_motor::~turn_on_motor()
{
	ROS_INFO_STREAM("Shutting down");//close
}