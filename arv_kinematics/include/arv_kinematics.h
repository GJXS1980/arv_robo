#ifndef _BOBAC_KINEMATICS_H
#define _BOBAC_KINEMATICS_H

#include "string"
#include "vector"

#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "geometry_msgs/Twist.h"
#include "boost/bind.hpp"
#include "boost/thread/thread.hpp"
#include "std_msgs/Float32MultiArray.h"

const float PI = std::acos(-1);

#define default_namespace ("/arv_kinematics/")
#define default_kinematics_mode (2)

#define default_wheel_radius (0.0845)    // 轮子的半径
#define default_wheel_separation (0.446)  // 两个轮子间距
#define default_vx (2.5)    // 速度最大
#define default_vy (2.5)    // 速度最大
#define default_vth (2.5)   // 速度最大


class BobacKinematics
{
public:
    BobacKinematics();
    ros::NodeHandle m_h;
    ros::NodeHandle m_ph;//private NodeHandle, for parameter set
    ros::Subscriber m_vel_sub; //subscribe topic = "cmd_vel"
    ros::Subscriber m_status_sub; //
    ros::Publisher m_motor_speed_pub, m_vel_pub;
    std::vector<float> m_motor_speed;	//inverse_kinematics
    std::vector<float> m_real_vel;	//kinematics

    int m_kinematics_mode;
    float m_wheel_separation;
    float m_wheel_radius;
    float m_max_vx;
    float m_max_vy;
    float m_max_vth;

    std::vector<float> kinematics(std::vector<float> motorspeed);
    std::vector<float> inverse_kinematics(float vx, float vy, float vth);

    void vel_callback(const geometry_msgs::Twist::ConstPtr& vel);
    void status_callback(const std_msgs::Float32MultiArray::ConstPtr& status);
    void motor_speed_pub();
    void status_pub();

    boost::thread m_ikthread;
    boost::thread m_kthread;
};

#endif
