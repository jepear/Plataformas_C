#include<ros/ros.h>

int main (int argc, char **argv){
    ros::init(argc,argv,"ejercicio1_node");
    ros::NodeHandle nh; 
    ros::Rate loop_rate(2);
    while(ros::ok()) { 
        ROS_INFO("Hola Mundo");
        loop_rate.sleep();
    }
    return 0;

}