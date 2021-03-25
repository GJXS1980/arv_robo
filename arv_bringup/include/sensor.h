
#ifndef __ARV_ROBOT_H_
#define __ARV_ROBOT_H_
// 头文件
#include "ros/ros.h"
#include <iostream>
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
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/Float32MultiArray.h"
#include <thread>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include "ARV_USART.h"


using namespace std;
#define SEND_DATA_CHECK   1     	//标志位，发送端做校验位
#define READ_DATA_CHECK   0     	//标志位，接收端做校验位
#define FRAME_HEADER      0X7B  	//帧头，和下位机一致
#define FRAME_TAIL  	  0X7D 		//帧尾
#define RECEIVE_DATA_SIZE		22//下位机发过来的数据的长度
#define SEND_DATA_SIZE			8//ROS发给下位机的数据的长度
#define PI 				3.1415926f//圆周率
#define EMPTY1 			0X00
#define EMPTY2 			0X0A

typedef struct __MPU9250_DATA_
{
	float roll;
	float pitch;
	float yaw;
}MPU9250_DATA;



typedef struct _SEND_DATA_  
{
	uint8_t tx[SEND_DATA_SIZE];
	uint8_t get_error;	       
	short Send_HZ;           
	uint8_t Once_Data;         
	unsigned char Frame_Tail;    //1个字节  帧尾 校验位 

}SEND_DATA;

typedef struct _RECEIVE_DATA_     
{
    uint8_t rx[RECEIVE_DATA_SIZE];
	unsigned char Frame_Header; 	//1个字节 帧头
	MPU9250_DATA mpu_data;
	float Power_voltage[2];		//电源电压
	float Ultrasonic_DATA[3];		
	float Temperature_DATA[2];
	short Collision_State;
	unsigned char Frame_Tail;	//1个字节  帧尾 校验位

	// int Speed_A;
	// int Speed_B;
	// int Encoder_A;
	// int Encoder_B;

}RECEIVE_DATA;


class turn_on_robot
{
	public:
		turn_on_robot(); //构造函数
		~turn_on_robot(); //析构函数
		void Control(); //循环控制代码
		//serial::Serial Stm32_Serial; //声明串口对象 
		ARV_USART *Stm32_Serial;
		void CalYaw(float *yaw);
		void CountTurns(float *newdata,float *olddata);
		void MPU_RESET(void);
	
	private:
		void STM32OrderCallback(const std_msgs::Float32MultiArray::ConstPtr& msg);	
		void SendDataCallback(const std_msgs::Float32MultiArray::ConstPtr& SET);	
		/* Read/Write data from ttyUSB 串口和控制函数声明 */
		bool Get_Sensor_Data();
		void mpu_trans(uint8_t *rx,int len);
		void thr_fun1(void);
		void Publish_SensorData();//发布
		unsigned char Check_Sum(unsigned char Count_Number,unsigned char mode);//校验函数
		int serial_baud_rate;//波特率
		string usart_port_name;
		ros::NodeHandle n;//创建句柄
		ros::Time _Now, _Last_Time;//时间相关
		float Sampling_Time; //采样时间
		boost::mutex mMutex;
		short turns;
	
		ros::Subscriber Cmd_Sensor_Sub,Enable_Sensor_Sub;//初始化2个订阅者
		ros::Publisher voltage_publisher, collision_publisher, ultrasonic_publisher,temperature_publisher,mpu9250_publisher,error_publisher;//初始化6个发布者
		RECEIVE_DATA Receive_Data;  //接收结构体   Receive_Data    
        SEND_DATA Send_Data;  //发送结构体  Send_Data
        MPU9250_DATA Mpu9250_Data;
};
#endif
