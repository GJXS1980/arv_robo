#include "arv_kinematics.h"

#define KINEMATICS_DEBUG false
#define INVERS_KINEMATICS_DEBUG false
#include "cmath"

template<typename T>
std::ostream& operator<< (std::ostream& os, std::vector<T> vec)
{
    os << '[';
    for(int i=0; i<vec.size(); i++) 
    {
        os << vec[i] <<" ";
    }
    return os << ']';
}

std::vector<float> HGarvKinematics::inverse_kinematics(float vx, float vy, float vth)
{
    std::vector<float> motor_speed(m_kinematics_mode, 0);
    switch(m_kinematics_mode) {
    case 2:
            //  两轮底盘运动学求解，前进方向为X正方向，左边为Y正方向，逆时针转动为正方向
            motor_speed[0] = (vx - vth*m_wheel_separation/2);
            motor_speed[1] = -(vx + vth*m_wheel_separation/2);
            break;
    case 3:
            //ROS_INFO("do nothing on kinematics_mode=3, waiting ro update");
            motor_speed[0] = (vx*sin(PI/3) + vy*cos(PI/3) + m_wheel_separation*vth)/m_wheel_radius*30/PI;
            motor_speed[1] = -(vx*sin(PI/3) - vy*cos(PI/3) - m_wheel_separation*vth)/m_wheel_radius*30/PI;
            motor_speed[2] = (-vy + m_wheel_separation*vth)/m_wheel_radius*30/PI;
            break;
    default:
            ROS_INFO("cannot support the kinematics");
    }
    
    #if INVERS_KINEMATICS_DEBUG
        std::cout << "kinematics motor speed: " << motor_speed << std::endl;
    #endif
    //std::cout << "kinematics motor speed: " << motor_speed << std::endl;
    return motor_speed;
}

//  两轮底盘正运动学求解
std::vector<float> HGarvKinematics::kinematics(std::vector<float> motorspeed)
{
    std::vector<float> velocity(3, 0);	// vx, vy, vth
    switch(m_kinematics_mode) {
    case 2:
        // velocity[0] = (-motorspeed[0] + motorspeed[1])*PI*m_wheel_radius/60.0; //m/s motorspeed (r/min)
        // velocity[1] = 0;
        // velocity[2] = (motorspeed[0] + motorspeed[1])*2*PI*m_wheel_radius/m_wheel_separation/60.0;
        velocity[0] = (-motorspeed[0] + motorspeed[1]); //m/s
        velocity[1] = (motorspeed[0] + motorspeed[1]);
        break;
    case 3:
        velocity[0] = (motorspeed[0] - motorspeed[1])*PI/30.f*m_wheel_radius/sqrt(3);
        velocity[1] = (motorspeed[0] + motorspeed[1] - 2*motorspeed[2])*PI*m_wheel_radius/30.f/3.f;
        velocity[2] = (motorspeed[0] + motorspeed[1] + motorspeed[2])*PI*m_wheel_radius/30.f/3.f/m_wheel_separation;
        break;
    }
    
    #if KINEMATICS_DEBUG
        std::cout << "kinematics: "<< velocity << std::endl;
    #endif

    return  velocity;
}

//  速度控制指令的获取及逆运动学求解
void HGarvKinematics::vel_callback(const geometry_msgs::Twist::ConstPtr& vel)
{
    float vx = 0, vy = 0, vth = 0;
    if (fabs(vel->linear.x) > m_max_vx) {
        vx = fabs(vel->linear.x)/vel->linear.x*m_max_vx;
    } 
    else {
        vx = vel->linear.x;
    }

    if (fabs(vel->angular.z) > m_max_vth) {
        vth = fabs(vel->angular.z)/vel->angular.z*m_max_vth;
    } 
    else {
        vth = vel->angular.z;
    }
    
    #if INVERS_KINEMATICS_DEBUG
        std::cout <<"received velocity [vx vy vth] "
                << '[' << vx << " " << vy <<" " << vth << ']'
                << std::endl;
    #endif
    m_motor_speed = inverse_kinematics(vx, 0, vth);
    //std::cout << "kinematics: "<< m_motor_speed << std::endl;
}

//  两轮底盘正运动学求解
void HGarvKinematics::status_callback(const std_msgs::Float32MultiArray::ConstPtr& status)
{
    std::vector<float> motorspeed = status->data;
    m_real_vel = kinematics(motorspeed);
}

void HGarvKinematics::motor_speed_pub()
{
    std_msgs::Float32MultiArray msg;
    ros::Rate loop(10);

    m_vel_sub = m_h.subscribe<geometry_msgs::Twist>("cmd_vel", 100, &HGarvKinematics::vel_callback, this);
    m_motor_speed_pub = m_h.advertise<std_msgs::Float32MultiArray>("/Motor_SetSpeed_TOPIC", 10);

    m_motor_speed = std::vector<float>(m_kinematics_mode, 0);

    while(ros::ok()) {
        loop.sleep();
        msg.data = m_motor_speed;
        m_motor_speed_pub.publish(msg);

        //  电机速度重置
        m_motor_speed[0] = 0;
        m_motor_speed[1] = 0;
        ros::spinOnce();
    }
}

//get bobac sensor information and kinematics
void HGarvKinematics::status_pub()
{
    m_status_sub = m_h.subscribe<std_msgs::Float32MultiArray>("arv_sensor", 10, &HGarvKinematics::status_callback, this);
    m_vel_pub = m_h.advertise<geometry_msgs::Twist>("real_vel", 10);
    m_real_vel = std::vector<float>(3, 0);

    ros::Rate loop(10);
    while(ros::ok()) {

        #if KINEMATICS_DEBUG
            std::cout << "kinematics vel: " << m_real_vel << std::endl;
        #endif

        geometry_msgs::Twist msg;
        msg.linear.x = m_real_vel[0];
        msg.linear.y = m_real_vel[1];
        msg.angular.z = m_real_vel[2];
        m_vel_pub.publish(msg);
        loop.sleep();
        ros::spinOnce();
    }
}


HGarvKinematics::HGarvKinematics()
{
    m_ph = ros::NodeHandle("~");
    //get kinematics_mode
    if(!m_ph.getParam("kinematics_mode", m_kinematics_mode)) {
        m_kinematics_mode = default_kinematics_mode;
        ROS_INFO("use default param \"kinematics_mode = %d\"",m_kinematics_mode);
    } else {
        ROS_INFO("kinematics_mode = %d", m_kinematics_mode);
    }

    //get wheel_diameter and wheel_separation
    if(!m_ph.getParam("wheel_radius", m_wheel_radius)) {
        m_wheel_radius = default_wheel_radius;
        ROS_INFO("use default param \"wheel_radius = %g\"",default_wheel_radius);
    } else {
        ROS_INFO("wheel_radius = %g", m_wheel_radius);
    }

    if(!m_ph.getParam("wheel_separation", m_wheel_separation)) {
        m_wheel_separation = default_wheel_separation;
        ROS_INFO("use default param \"wheel_separation = %g\"",default_wheel_separation);
    } else {
        ROS_INFO("wheel_separation = %g", m_wheel_separation);
    }

    //get max velocity
    if(!m_ph.getParam("max_vx", m_max_vx)) {
        m_max_vx = default_vx;
        ROS_INFO("use default param \"max_vx = %g\"",m_max_vx);
    } else {
        ROS_INFO("max_vx = %g", m_max_vx);
    }

    if(!m_ph.getParam("max_vy", m_max_vy)) {
        m_max_vy = default_vy;
        ROS_INFO("use default param \"max_vy = %g\"",m_max_vy);
    } else {
        ROS_INFO("max_vy = %g", m_max_vy);
    }

    if(!m_ph.getParam("max_vth", m_max_vth)) {
        m_max_vth = default_vth;
        ROS_INFO("use default param \"max_vth = %g\"",m_max_vth);
    } else {
        ROS_INFO("max_vth = %g", m_max_vth);
    }
    m_ikthread = boost::thread(boost::bind(&HGarvKinematics::motor_speed_pub, this));
    m_kthread = boost::thread(boost::bind(&HGarvKinematics::status_pub, this));
}

