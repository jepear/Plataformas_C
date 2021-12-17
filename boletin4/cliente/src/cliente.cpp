#include<ros/ros.h>
#include<actionlib/server/simple_action_server.h>
#include<mensaje/simpleactionmsgAction.h>
#include<iostream>
using namespace std;

void doneCallBack(const actionlib::SimpleClientGoalState &state, const mensaje::simpleactionmsgResutlConstPtr &result){
    ROS_INFO("Done CallBack");
    ROS_INFO("Estado: %s",state.toString().c_str());
    ROS_INFO("Resultado: %i",result->total);
    ROS_INFO("Estado: %s",result->msg.c_str());
}


void activeCallBack(){
    ROS_INFO("Empezando a trabajar.");
}


void feedbackCallBack(const mensaje::simpleactionmsgFeedbackCostPtr &feedback){
    ROS_INFO("Feedback callback");
    ROS_INFO("Feedback: %i", feedback->parcial);
}

int main(int argc, char **argv){
    ros::init(argc,argv,"servidor_accion");
    actionlib::SimpleActionClient< mensaje::simpleactionmsgAction>cliente("servido_simple_acciones",true);
    ros::Rate loop_rate(1);
    ROS_INFO("Esperando por el servidor de acciones.");
    cliente.waitForSrver();
    mensaje::simpleactionmsgGoal goal_msg;
    cout<<"Dame un numero de segundos"<<endl;
    cin>>goal_smg.numero;

    cliente.sendGoal(goal_msg,doneCallBack,activeCallback,feedbackCallBack);

    actionlib::SimpleClientGoalState statu=cliente.getState();
    int cont = 0;
    
    while (status == actionlib::SimpleClientGoalState::PENDING || status == actionlib::SimpleClientGoalState:.ACTIVE){
        ROS_INFO("haciendo cosas:%i",cont);
        loop_rate.sleep();
	cont++;
	status=cliente.getSate();
    }
    return 0;
}
