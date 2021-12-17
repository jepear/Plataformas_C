#include<ros/ros.h>
#include<bol3_ej1/timer.h>
#include<iostream>

using namespace std;


bool fibonacciCallBack(bol3_ej1::timerRequest &request, bol3_ej1::timerResponse &response){

    ros::Rate loop_rate(2);

    double anterior = 1.0;
    double siguiente = 0.0;
    stringstream ss; //buffer

    for(int i=0;i<=request.request;i++){

        ss<<siguiente<<","; //agregamos los elementos al buffer
        anterior+=siguiente;
        siguiente=anterior-siguiente;
        

        loop_rate.sleep();
    }


    response.response=ss.str(); //convertimos el buffer a cadena

    return true; //siempre true, es para saber si se ejecuta con exito
}

int main(int argc, char ** argv){
    ros::init(argc,argv,"nodo_ejer2");
    ros::NodeHandle nh;

    ros::ServiceServer server=nh.advertiseService<bol3_ej1::timerRequest,bol3_ej1::timerResponse>("mi_servicio",fibonacciCallBack);
    ROS_INFO("Servicio creado");

    ros::spin();

    return 0;
}

