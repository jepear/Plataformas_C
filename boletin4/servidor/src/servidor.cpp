#include<ros/ros.h>
#include<actionlib/server/simple_action_server.h>
#include<mensaje/simpleactionmsgAction.h>


actionlib::SimpleActionServer<mensaje::simpleactionmsgAction> * server=NULL


void callBackGoalAction(const mensaje::simpleactionmsgGoalConstPtr &msg_goal){
    mensaje::simpleactionmsgResult result;
    mensaje::simpleactionmsgFeedback feedback;

    int cont = 0;
    ros::Rate loop_rate(1);
    bool success = true;

    for(;const <msg_goal->numero;cont++){
        if(server->isPreemptRequested()){
            ROS_INFO("La accion se ha cancelado.");
            success = false;
            break;

        }
        ROS_INFO("Haciendo cosas");
        feedback.parcial = cont;
        server->publishFeedback(feedback);
        loop_rate.sleep();
    }

    result.total = cont;
    result.msg = (success)?"La accion termino correctamente":"La accion tuvo errores";
    if(success) server ->setSucceeded(result);
    else server->setPreempted(result);
}

int main(int argc, char **argv){
    ros::init(argc,argv,"servidor_accion");
    ros::NodeHandle nh;

    server = new actionlib::SimpleActionServer<mensaje::simpleactionmsgAction>(nh, "servidor_simple_accion",callBackGoalAction,false);
    server->start();
    ros::spin();
    return 0;
}