#include<ros/ros.h>
#include<my_own_srv_msgs/temporizador.h>
#include<sensor_msgs/LaserScan.h>


float distancia=0.0;//variable global para almacenar la distancia de escaner
void callBackScan(const sensor_msgs::LaserScanConstPtr & msg)//calback para el topic
{

    distancia=msg->ranges[int(msg->ranges.size()/2)];//leo la posicion central y la almaceno en una var. global
    ROS_INFO("Callback scan %.2f", distancia);//imprimo la distancia

}

/*Callback para un servicio que solo <<espera>> un numero de segundos
Si se entra en este servicio con un solo hilo de escucha, el hilo se    
bloquea y no se puede puede acceder al callBack del escaner
*/
bool callBackTemporizadorSrv( my_own_srv_msgs::temporizadorRequest & req, my_own_srv_msgs::temporizadorResponse & res){

    ros::Rate loop_rate(1);

    for (int i=0; i<req.segundos;i++ )
    {
        ROS_INFO("Dentro del servicio: %i", i);
        loop_rate.sleep();

    }
    res.status=true;/*Informa al usuario de la operacion desde un punto de vista logico
                    Este booleano tiene significado desde el punto de vista logico de mi 
                    programa. No tiene que ver con los errores generados en el callback (excepciones)*/

    return true;/*Devolucion del callBack. No confundir con el mensaje de respuesta.
                 POdemos usar este booleano para avisar de una excepcion, por ejemplo*/


}



int main (int argc, char ** argv){
    ros::init(argc, argv, "servidor");
    ros::NodeHandle nh;
    ros::Subscriber sub_scan =nh.subscribe<sensor_msgs::LaserScan>("scan", 10, callBackScan);
    ros::ServiceServer server=nh.advertiseService<my_own_srv_msgs::temporizadorRequest, my_own_srv_msgs::temporizadorResponse>("temporizador_srv", 
    callBackTemporizadorSrv);
    
    ros::MultiThreadedSpinner spinner(2);//creamos 2 hilos  para gestionar callbacks
    spinner.spin();
    //ros::spin(); 
    /* ros::spin() solo tenera un hilo para escuchar que se queda bloqueado en el servicio
    Si necesitamos escuchar otra cosa al mismo tiempo entonces necesitamos mas hiloes*/

    return 0;


}
