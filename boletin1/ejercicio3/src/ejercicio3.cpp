#include<ros/ros.h>
#include<std_msgs/Int32.h>
#include<iostream>
using namespace std;

void contadorCallBack (const std_msgs::Int32ConstPtr & msg){
    ROS_INFO("Elemento %i", msg->data);
    cout<<"Elemento: "<<msg->data<<endl;
}

int main (int argc, char ** argv){
    ros::init(argc,argv, "ejercicio3_node");
    ros::NodeHandle nh;
    
    ros::Subscriber sub=nh.subscribe("contador",10,contadorCallBack);

    ros::spin();

    return 0;
}
