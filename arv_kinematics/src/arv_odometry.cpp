#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Int32MultiArray.h>

const float PI = std::acos(-1);

double x = 0.0;
double y = 0.0;
double th = 0.0;

double vx = 0.0;
double vy = 0.0;
double vth = 0.0;

double r = 0.0845;  //  轮子半径
double d = 0.223;   //  轮子到底盘中心距离
double sum_encoder = 5599.0;    //  轮子转动一圈的脉冲数

double encoder_now_l = 0.0;
double encoder_now_r = 0.0;
double encoder_last_r = 0.0;
double encoder_last_l = 0.0;

double inc_encoder_l = 0.0;
double inc_encoder_r = 0.0;

// double count_l = 0;  //  左轮子转动圈数
// double count_r = 0;  //  右轮子半径


ros::Time current_time, last_time;

void vel_callback(const geometry_msgs::Twist::ConstPtr& vel)
{
    //get current velocity
    vx = vel->linear.x;
    vy = vel->linear.y;
    vth = vel->angular.z;
}

void encoder_callback(const std_msgs::Int32MultiArray::ConstPtr& enc)
{
    //get current velocity
    encoder_now_l = enc->data[0];   //  获取左轮编码值（累加之后））
    encoder_now_r = enc->data[1];    //  获取右轮编码值（累加之后））


    // if (encoder_now_l < 599 && encoder_last_l > 5000){
    //     count_l += 1;
    // }
    // else if (encoder_now_l > 5000 && encoder_last_l < 599)
    // {
    //     count_l -= 1;
    // }
    // else {
    //     count_l += 0;
    // }

    // if (encoder_now_r < 59 && encoder_last_r > 5540){
    //     count_r += 1;
    // }
    // else if (encoder_now_r > 5540 && encoder_last_r < 59)
    // {
    //     count_r -= 1;
    // }
    // else {
    //     count_r += 0;
    // }

    inc_encoder_l = encoder_now_l - encoder_last_l; //  左轮编码器变换量
    inc_encoder_r = encoder_now_r - encoder_last_r; //  右轮编码器变换量

    // std::cout << "motor encoder: " << encoder_now_r << std::endl <<  "motor encoder sum: "  << inc_encoder_r << std::endl;

    //  求解里程计数据
    th += PI * r * (inc_encoder_r - inc_encoder_l)/(d * sum_encoder);   //  航向角度
    x += (2 * PI * r * cos(th)) * inc_encoder_r / sum_encoder;   //  x方向位移
    y += (2 * PI * r * sin(th)) * inc_encoder_r / sum_encoder;   //  y方向位移

    encoder_last_l = encoder_now_l;
    encoder_last_r = encoder_now_r;

}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "odometry_publisher");
    ros::NodeHandle n;
    ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50);
    ros::Subscriber cmd_sub = n.subscribe<geometry_msgs::Twist>("cmd_vel",10, vel_callback);
    ros::Subscriber encoder_sub = n.subscribe<std_msgs::Int32MultiArray>("/Motor_Encoder",10, encoder_callback);

    tf::TransformBroadcaster odom_broadcaster;

    current_time = ros::Time::now();
    last_time = ros::Time::now();
    ros::Rate r(10.0);
    while(ros::ok()) {
        ros::spinOnce(); // check for incoming messages
        //since all odometry is 6DOF we'll need a quaternion created from yaw
        geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);

        //first, we'll publish the transform over tf
        geometry_msgs::TransformStamped odom_trans;
        odom_trans.header.stamp = current_time;
        odom_trans.header.frame_id = "odom";
        odom_trans.child_frame_id = "base_footprint";

        odom_trans.transform.translation.x = x;
        odom_trans.transform.translation.y = y;
        odom_trans.transform.translation.z = 0.0;
        odom_trans.transform.rotation = odom_quat;

        //send the transform
        odom_broadcaster.sendTransform(odom_trans);

        //next, we'll publish the odometry message over ROS
        nav_msgs::Odometry odom;
        odom.header.stamp = current_time;
        odom.header.frame_id = "odom";

        //set the position
        odom.pose.pose.position.x = x;
        odom.pose.pose.position.y = y;
        odom.pose.pose.position.z = 0.0;
        odom.pose.pose.orientation = odom_quat;

        //set the velocity
        odom.child_frame_id = "base_footprint";
        odom.twist.twist.linear.x = vx;
        odom.twist.twist.linear.y = vy;
        odom.twist.twist.angular.z = vth;
        //publish the message
        odom_pub.publish(odom);
        r.sleep();
    }
}
