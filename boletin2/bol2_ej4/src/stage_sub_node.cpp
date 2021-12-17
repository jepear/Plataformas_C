#include <ros/ros.h>
//#include <nav_msgs/Odometry.h> Codigo del ejercicio 1
#include<sensor_msgs/LaserScan.h>
#include<geometry_msgs/Twist.h>
#include <algorithm>
#include <vector>
#include<iostream>
/*void callback(const nav_msgs::Odometry::ConstPtr& msg){    //Callback del ej1
    ROS_INFO("Header : Seq %d \nTime %S:\n FrameID: %s",msg->header.seq,msg->header.stamp,msg->header.frame_id.c_str());
    ROS_INFO("Position X%3.2f Y%f Z%f",msg->pose.pose.position.x,msg->pose.pose.position.y,msg->pose.pose.position.z);
    ROS_INFO("Orentacion X%f  Y%f Z%f",msg->pose.pose.orientation.x,msg->pose.pose.orientation.y,msg->pose.pose.orientation.z);
    //ROS_INFO("Me cago %s Id %d",msg->child_frame_id.c_str(),msg->header.seq); 
}*/

ros::Publisher pub;

void callback2(const sensor_msgs::LaserScan::ConstPtr& msg){    //Callback del ej1
    geometry_msgs::Twist data;
    int size = msg->ranges.size();
    int minIndex = 0;
    int maxIndex = 540; //0 to 540 for left side minimum distance
    int closestIndex = -1;
    double minVal = 999; //values are between 0.2 and 30 meters for my scanner

    for (int i = minIndex; i < maxIndex; i++)
    {
        if ((msg->ranges[i] <= minVal) && (msg->ranges[i] >= msg->range_min) && (msg->ranges[i] <= msg->range_max))
        {
            minVal = msg->ranges[i];
            closestIndex = i;
        }}

    //float a[]={1,2,3,4,4};
    //std::vector<int>::iterator result=a.begin();
    ROS_INFO_STREAM("Min ---" << msg->ranges[closestIndex]);

    if(msg->ranges[closestIndex]>1){
        int valor;
        std::cout<<"Introduce un valor:";
        std::cin>>valor;
        ros::Rate loop_rate(1);

        if(valor==6){
            ROS_INFO("Hacia delante");
            data.linear.x=0;
            data.linear.y=1;
            data.linear.z=0;

            data.angular.x=0;
            data.angular.y=0;
            data.angular.z=0;
            pub.publish(data);
        }else if(valor==4){
            ROS_INFO("Hacia atras");
            data.linear.y=-1;
            pub.publish(data);
        }else if(valor==2){ //Giro derecha
            data.angular.z=-1.6;
            for (int i =0;i<2; i++){
                pub.publish(data);
                loop_rate.sleep();
            }
        }else if(valor==8){ //Giro izquierda
            data.angular.z=1.6;
            for (int i =0;i<2; i++){
                pub.publish(data);
                loop_rate.sleep();
            }
        }else{
            ROS_INFO("Dame un valor adecuado");
        }
    }else{
        ROS_INFO("Tienes un objeto a menos de 1 metro. Gira el dispositivo");
        int valor;
        std::cout<<"Introduce un valor:";
        std::cin>>valor;
        ros::Rate loop_rate(1);
        if(valor==4){
            ROS_INFO("Hacia atras");
            data.linear.y=-1;
            pub.publish(data);
        }else if(valor==2){ //Giro derecha
            data.angular.z=-1.6;
            for (int i =0;i<2; i++){
                pub.publish(data);
                loop_rate.sleep();
            }
        }else if(valor==8){ //Giro izquierda
            data.angular.z=1.6;
            for (int i =0;i<2; i++){
                pub.publish(data);
                loop_rate.sleep();
            }
        }else{
            ROS_INFO("Dame un valor adecuado");
        }
    }
}

int main(int argc, char ** argv){
    ros::init(argc, argv, "stage_sub_nodo");
    ros::NodeHandle nh;
    //ros::Subscriber sub=nh.subscribe("odom",1000,callback); Ej1 Suscriptor
    ros::Subscriber sub=nh.subscribe("scan",1000,callback2);
    pub=nh.advertise<geometry_msgs::Twist>("mobile_base/commands/velocity",5);

    ros::spin();
    return 0;
}