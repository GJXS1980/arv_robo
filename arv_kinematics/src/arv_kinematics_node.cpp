#include "arv_kinematics.h"
#include "ros/ros.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "arv_kinematics");
    HGarvKinematics arv;
    ros::spin();
    return 0;
}
