#ifndef __ARV_MOTOR_H_
#define __ARV_MOTOR_H_
// 头文件
#include "ros/ros.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string> 
#include <iostream>
#include <math.h>
#include <stdlib.h>    
#include <unistd.h>      
#include <sys/types.h>
#include <sys/stat.h>
#include <serial/serial.h>
#include <fcntl.h>          
#include <stdbool.h>
#include <tf/transform_broadcaster.h>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Int32MultiArray.h"
#include "crc16.h"
#include "ARV_USART.h"
#include <signal.h>
#include <math.h>


#define 	RECEIVE_DATA_SIZE		12
#define		SEND_DATA_SIZE			12
#define 	pi						3.14159
#define     d						0.169		//轮子直径


using namespace std;

extern  void CRC16CheckSum(uint8_t *pDataIn, int len, uint8_t *sum);
extern  void CRC16CheckSum(uint8_t *pDataIn, int len, uint16_t *sum);
  
typedef struct _RECEIVE_DATA_     
{
		int Speed_A;
		int Speed_B;
		int Encoder_A;
		int Encoder_B;
		
}RECEIVE_DATA;


class turn_on_motor
{
	public:
		turn_on_motor(); //构造函数
		~turn_on_motor(); //析构函数
		void Control();//循环控制代码
	        void motor_init(void);
		//serial::Serial MOTOR_Serial; //声明串口对象 
		ARV_USART *MOTOR_Serial;
		void CountEncoder(int *NewEncoder,int *OldEncoder,int *turns);
		int MotorA_turns;
		int MotorB_turns;
		void* Signal_Handle();


	private:
		void SetSpeedCallback(const std_msgs::Float32MultiArray::ConstPtr &speed);
		void MOTOR_Enable_Callback(const std_msgs::Int32::ConstPtr &enable);
		void Get_MOTOR_Data();
		

		
		void Publish_Motor_ERROR();//发布错误码
		unsigned char Check_Sum(uint8_t *rx,unsigned char Count_Number);//校验函数
		int serial_baud_rate;//波特率
		string usart_port_name;
		ros::NodeHandle n;//创建句柄
		ros::Subscriber MOTOR_ENALBE_Sub,MOTOR_SetSpeed_Sub;	//初始化2个订阅者
		ros::Publisher Speed_publisher, Encoder_publisher,ERROR_publisher;	//初始化2个发布者
		RECEIVE_DATA Receive_Data;  				//接收结构体   Receive_Data    
};
#endif
