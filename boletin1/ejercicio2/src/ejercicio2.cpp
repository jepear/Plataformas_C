#include<ros/ros.h>
#include<std_msgs/Int32.h>

int main(int argc, char **argv){
    ros::init(argc,argv,"Ejercicio2_node");
    ros::NodeHandle nh;

    ros::Publisher pub=nh.advertise<std_msgs::Int32>("contador",10);
    ros::Rate loop_rate(2);
    std_msgs::Int32 msg;
    msg.data=0;

    while(ros::ok()){
        
        pub.publish(msg);
        msg.data++;
        loop_rate.sleep();
    }
    return 0;
}