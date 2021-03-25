#include "sensor.h"

/**************************************
Function: 主函数，ROS初始化
***************************************/
int main(int argc, char** argv)
{
	ros::init(argc, argv, "STM32_CONTROL_NODE");
	ROS_INFO("STM32_CONTROL_NODE has turned on ");
	turn_on_robot Robot_Control; //实例化一个对象
	Robot_Control.Control();  //循环执行数据采集和发布topic等操作
	return 0;
} 

/**************************************
Function: 订阅回调函数Callback，根据订阅的指令向串口发控制协议开启和关闭某个传感器
***************************************/
void turn_on_robot::STM32OrderCallback(const std_msgs::Float32MultiArray::ConstPtr& msg)
{
	Send_Data.tx[0]= FRAME_HEADER;
	Send_Data.tx[7]= FRAME_TAIL;
	
	if(msg->data[0])
	{
		Send_Data.tx[1] = msg->data[1];
	}
	else 
	{
		Send_Data.tx[2] = msg->data[1];
	}
	Send_Data.tx[3] = EMPTY1;
	Send_Data.tx[4] = EMPTY1;
	Send_Data.tx[5] = EMPTY1;	
	Send_Data.tx[6] = Check_Sum(6,SEND_DATA_CHECK);//校验位检测;	
	
	Stm32_Serial->Data_Write(Send_Data.tx,sizeof (Send_Data.tx));//读串口数据
}

void turn_on_robot::SendDataCallback(const std_msgs::Float32MultiArray::ConstPtr& SET)
{
	Send_Data.tx[0]= FRAME_HEADER;
	Send_Data.tx[7]= FRAME_TAIL;
	Send_Data.tx[1] = EMPTY2;
	Send_Data.tx[2] = EMPTY2;
	
	Send_Data.tx[3] = SET->data[3];	
	Send_Data.tx[4] = SET->data[0];
	Send_Data.tx[5] = SET->data[1];
	Send_Data.tx[6] = Check_Sum(6,SEND_DATA_CHECK);//校验位检测;	
	Stm32_Serial->Data_Write(Send_Data.tx,sizeof (Send_Data.tx));//读串口数据
}


/**************************************
Function: 发布传感器相关信息
***************************************/
void turn_on_robot::Publish_SensorData()
{
    std_msgs::Int32 collision_msgs;	
    std_msgs::Float32MultiArray voltage_msgs;	//定义电源电压发布topic的数据类型std_msgs::Float32
    std_msgs::Float32MultiArray ultrasoni_msgs; 
    std_msgs::Float32MultiArray temperature_msgs; 
    std_msgs::Float32 mpu9250_msgs; 	    

   
    collision_msgs.data = Receive_Data.Collision_State ;  
    collision_publisher.publish(collision_msgs);

    voltage_msgs.data.push_back(Receive_Data.Power_voltage[0]);
    voltage_msgs.data.push_back(Receive_Data.Power_voltage[1]);
    voltage_publisher.publish(voltage_msgs);
   
    ultrasoni_msgs.data.push_back(Receive_Data.Ultrasonic_DATA[0]);
    ultrasoni_msgs.data.push_back(Receive_Data.Ultrasonic_DATA[1]);
    ultrasoni_msgs.data.push_back(Receive_Data.Ultrasonic_DATA[2]);
    ultrasonic_publisher.publish(ultrasoni_msgs);
    
    temperature_msgs.data.push_back(Receive_Data.Temperature_DATA[0]);
    temperature_msgs.data.push_back(Receive_Data.Temperature_DATA[1]);
    temperature_publisher.publish(temperature_msgs);

    //mpu9250_msgs.data.push_back(Receive_Data.mpu_data.roll);
    //mpu9250_msgs.data.push_back(Receive_Data.mpu_data.pitch);
    mpu9250_msgs.data=Receive_Data.mpu_data.yaw;
    mpu9250_publisher.publish(mpu9250_msgs);


}
/**************************************
Function: 串口通讯校验函数，数据包除最后一个字节，其他的全部数据按位异或的结果作为帧尾
***************************************/
unsigned char turn_on_robot::Check_Sum(unsigned char Count_Number,unsigned char mode)
{
	unsigned char check_sum=0,k;
	
	if(mode==0) //接收数据
	{
		for(k=0;k<Count_Number;k++)//Count_Number是接收数组位数减1
		{
			check_sum=check_sum^Receive_Data.rx[k];//按位异或
		}
	}
	
	if(mode==1) //发送数据
	{
		for(k=0;k<Count_Number;k++)//Count_Number是发送数组位数减1
		{
			check_sum=check_sum^Send_Data.tx[k];//按位异或
		}
	}
	return check_sum;//返回结果
}

void turn_on_robot::CountTurns(float *newdata, float *olddata)
{
	if((*newdata < -170.0f)&&( *olddata > 170.0f))
		turns++;		
	
	if((*newdata > 170.0f)&&( *olddata < -170.0f))
		turns--;
}


void turn_on_robot::CalYaw(float *yaw)
{
  static int semple = 30;
  static float ori_mpu_data = 0; 
  
 // printf("data:%f\n",ori_mpu_data);
  if(semple)
   {
	semple--;
	ori_mpu_data += 360.0*(turns)+(*yaw);
   }
   else 
   {
	*yaw = 360.0*(turns)+(*yaw) - ori_mpu_data/30.0f;
   }

}

void turn_on_robot::mpu_trans(uint8_t *rx,int len)
{
	static float  newdata =0.0f,olddata = 0.0f;
	 
	//Receive_Data.mpu_data.roll =  rx[1]<<8|rx[2];			//int 
	//Receive_Data.mpu_data.roll += (float)(rx[3]<<8|rx[4])/1000;
	//Receive_Data.mpu_data.roll = rx[0]>0? Receive_Data.mpu_data.roll:-Receive_Data.mpu_data.roll;

	//Receive_Data.mpu_data.pitch =  rx[6]<<8|rx[7];	;
	//Receive_Data.mpu_data.pitch += (float)(rx[8]<<8|rx[9])/1000;
	//Receive_Data.mpu_data.pitch = rx[5]>0? Receive_Data.mpu_data.pitch:-Receive_Data.mpu_data.pitch;
	
	Receive_Data.mpu_data.yaw =  rx[1]<<8|rx[2];	;
	Receive_Data.mpu_data.yaw += (float)(rx[3]<<8|rx[4])/1000;
	Receive_Data.mpu_data.yaw = rx[0]>0? Receive_Data.mpu_data.yaw:-Receive_Data.mpu_data.yaw;

	olddata = newdata;
	newdata = Receive_Data.mpu_data.yaw; 
	
	CountTurns(&newdata,&olddata);
	CalYaw(&Receive_Data.mpu_data.yaw);
}


/**************************************
Function: 从串口读取数据 
***************************************/
bool turn_on_robot::Get_Sensor_Data()
{ 
	short Header_Pos=0,Tail_Pos=21;  						
	uint8_t Receive_Data_Pr[RECEIVE_DATA_SIZE]={0};	
	Stm32_Serial->Data_Read(Receive_Data_Pr,sizeof (Receive_Data_Pr));//读串口数据
   
    if((Receive_Data_Pr[Header_Pos]==FRAME_HEADER)&&(Receive_Data_Pr[Tail_Pos]==FRAME_TAIL))  
    {  
      	memcpy(Receive_Data.rx, Receive_Data_Pr, sizeof(Receive_Data_Pr));
//	ROS_INFO("------------------------------------------------------------");
//	ROS_INFO("%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x",
//	Receive_Data.rx[0],Receive_Data.rx[1],Receive_Data.rx[2],Receive_Data.rx[3],Receive_Data.rx[4],Receive_Data.rx[5],Receive_Data.rx[6],Receive_Data.rx[7],
//	Receive_Data.rx[8],Receive_Data.rx[9],Receive_Data.rx[10],Receive_Data.rx[11],Receive_Data.rx[12],Receive_Data.rx[13],Receive_Data.rx[14],Receive_Data.rx[15],
//	Receive_Data.rx[16],Receive_Data.rx[17],Receive_Data.rx[18],Receive_Data.rx[19],Receive_Data.rx[20],Receive_Data.rx[21],Receive_Data.rx[22],Receive_Data.rx[23],
//	Receive_Data.rx[24],Receive_Data.rx[25],Receive_Data.rx[26],Receive_Data.rx[27],Receive_Data.rx[28],Receive_Data.rx[29],Receive_Data.rx[30]);
//	ROS_INFO("------------------------------------------------------------");
    }
    else 
   {
     	//ROS_INFO("eorro----");
	//Stm32_Serial.SetlnBufferCount(0);
     	return false;
   } 	
   
   //printf("vbat:%02x \n",Receive_Data.rx[18]);
   Receive_Data.Frame_Header= Receive_Data.rx[0]; //数据的第一位是帧头（固定值）
   Receive_Data.Frame_Tail= Receive_Data.rx[21];  //数据的最后一位是帧尾（数据校验位）
   
   if (Receive_Data.Frame_Header == FRAME_HEADER )//判断帧头
   {
	   if (Receive_Data.Frame_Tail == FRAME_TAIL) //判断帧尾
	   { 
		   if (Receive_Data.rx[20] == Check_Sum(20,READ_DATA_CHECK))//校验位检测
		   { 
			   mpu_trans(&Receive_Data.rx[1],4);
			   Receive_Data.Ultrasonic_DATA[0]=Receive_Data.rx[6]<<8|Receive_Data.rx[7];
			   Receive_Data.Ultrasonic_DATA[1]=Receive_Data.rx[8]<<8|Receive_Data.rx[9];
			   Receive_Data.Ultrasonic_DATA[2]=Receive_Data.rx[10]<<8|Receive_Data.rx[11];
			   Receive_Data.Ultrasonic_DATA[2]+=(float)Receive_Data.rx[12]/100;
			   Receive_Data.Temperature_DATA[0]= Receive_Data.rx[13];
			   Receive_Data.Temperature_DATA[0]+=(float)Receive_Data.rx[14]/100;
			   Receive_Data.Temperature_DATA[1]= Receive_Data.rx[15];
			   Receive_Data.Temperature_DATA[1]+=(float)Receive_Data.rx[16]/100;		
			   Receive_Data.Power_voltage[0] = Receive_Data.rx[17];//充电状态
			   Receive_Data.Power_voltage[1] = Receive_Data.rx[18];//获取电池电压
			   Receive_Data.Collision_State = Receive_Data.rx[19];
			   return true;
			}
		}
	} 
	return false;
}
/**************************************
Function: 这是相关控制代码，代码循环执行
***************************************/

void turn_on_robot::MPU_RESET(void)
{
	uint8_t cmd[]={0x7B,0x06,0x00,0x00,0x00,0x00,0x7D,0x7D};
	Stm32_Serial->Data_Write(cmd,sizeof(cmd));
}

void turn_on_robot::Control()
{
	_Last_Time = ros::Time::now();
	std::thread t1(&turn_on_robot::thr_fun1,this);
	ros::Rate loop_rate(100);	
	//MPU_RESET();
	//sleep(2);
	while(ros::ok())
	{
		_Now = ros::Time::now();
		Sampling_Time = (_Now - _Last_Time).toSec();	
		if (true == Get_Sensor_Data())  //从串口读取下位机法过来的全部数据
		{
			Publish_SensorData(); //发布
		}
		usleep(10);	
		_Last_Time = _Now;//记录时间
		loop_rate.sleep();
		ros::spinOnce();//循环等待回调函数
    }
}

/**************************************
Function: 开启线程定时读取错误码 自检
***************************************/
void turn_on_robot::thr_fun1(void)
{
	uint8_t check = 0;
    uint8_t i;
 	std_msgs::Float32MultiArray error_msgs; 
	uint8_t error_buff[6]={0};	  
	while(1)
	{
		mMutex.lock();
		Send_Data.tx[0]= FRAME_HEADER;
		Send_Data.tx[7]= FRAME_TAIL;
		Send_Data.tx[1] = EMPTY2;
		Send_Data.tx[2] = EMPTY2;
	
		Send_Data.tx[3] = EMPTY1;	
		Send_Data.tx[4] = EMPTY1;
		Send_Data.tx[5] = 0x01;
		Send_Data.tx[6] = Check_Sum(6,SEND_DATA_CHECK);//校验位检测;	     
		Stm32_Serial->Data_Write(Send_Data.tx,8);//写串口数据		
		memset(error_buff,0,6);
	  	//usleep(1000);
		Stm32_Serial->Data_Read(error_buff,6);//读串口数据;
		//for(int i=0;i<6;i++)
		//printf("%02x ",error_buff[i]);				

		//printf("\n");
		if ((error_buff[0] == FRAME_HEADER)&&(error_buff[5]== FRAME_TAIL))//判断帧头 帧尾
  		{
			error_msgs.data.clear();			
			for(i=0;i<4;i++)
			{
				check = check^error_buff[i];
			}
			
			if (error_buff[4]==check) //CRC 
			{
				error_msgs.data.push_back(error_buff[1]);
				error_msgs.data.push_back(error_buff[2]);
				error_msgs.data.push_back(error_buff[3]);
				error_publisher.publish(error_msgs);
			}	
		}
		mMutex.unlock();
		sleep(2);
 	}

}

/**************************************
Function: 构造函数
***************************************/
turn_on_robot::turn_on_robot():Sampling_Time(0),turns(0)
{
	memset(&Receive_Data, 0, sizeof(Receive_Data)); 
	memset(&Send_Data, 0, sizeof(Send_Data));
	memset(&Mpu9250_Data, 0, sizeof(Mpu9250_Data));
	ros::NodeHandle private_nh("~");
	
	private_nh.param<std::string>("usart_port_name", usart_port_name, "/dev/ttyUSB0"); //固定串口
	private_nh.param<int>("serial_baud_rate", serial_baud_rate, 115200); //和下位机底层波特率115200 
	voltage_publisher 	= n.advertise<std_msgs::Float32MultiArray>("/Power_Msg", 100);	//电池电压数据发布
	collision_publisher 	= n.advertise<std_msgs::Int32>("Collision_State", 100);			
	ultrasonic_publisher 	= n.advertise<std_msgs::Float32MultiArray>("/Ultrasonic_DATA", 100);
	temperature_publisher = n.advertise<std_msgs::Float32MultiArray>("/Temperature_DATA", 100);
	mpu9250_publisher  	= n.advertise<std_msgs::Float32>("/MPU_DATA", 1000);
	error_publisher	= n.advertise<std_msgs::Float32MultiArray>("/STM32_ERROR_CODE", 100);
	Enable_Sensor_Sub = n.subscribe("/STM32_ENBLAE_Topic", 10, &turn_on_robot::STM32OrderCallback,this);	
	Cmd_Sensor_Sub = n.subscribe("/STM32_CMD_Topic", 10, &turn_on_robot::SendDataCallback,this);	
	
	Stm32_Serial = new ARV_USART((char*)usart_port_name.data());
	if(Stm32_Serial->USART_Seting(serial_baud_rate, 0, 8, 1, 'N')==false) exit(0);
	
	ROS_INFO_STREAM("STM32 Data ready");
}

/**************************************
Function: 析构函数
***************************************/
turn_on_robot::~turn_on_robot()
{
	//Stm32_Serial.close();//关闭串口
	ROS_INFO_STREAM("Shutting down");
}



