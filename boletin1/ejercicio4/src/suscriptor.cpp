#include <ros/ros.h>
#include <ejercicio4/datos.h>
#include <iostream>
using namespace std;
int valor = 0;

void callback(const ejercicio4::datos::ConstPtr& msg){
    if(valor==3){
        ROS_INFO("He recivido: NOmbre [%s] Convocatoria [%d] Nota [%f]", msg->nombre.c_str(), msg->convocatoria, msg->nota);
    }
    else {
        valor = valor + 1;
        ROS_INFO("Numero de iteraciones %d", valor);
    }
}

int main(int argc, char **argv){
    ros::init(argc, argv, "suscriptor_node");
    ros::NodelHandle nh;
    ros::Subscriber sub=nh.subscriber("calificacion",1000,callback);
    ros::spin();
    return 0;
}