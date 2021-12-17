#include<ros/ros.h>
#include<geometry_msgs/Twist.h>
#include<nav_msgs/Odometry.h>
#include<ej5_examen/coordenada.h>
#include<string>
using namespace std;

class Robot{
    private:
    /*Fijajos que en este caso todos los elementos que necesitamos son atributos de la clase
    no tenemos los problemas de ámbito para acceder al publicador que tenemos en la versión
    estrucutrada*/
        ros::NodeHandle nh;//El NodeHandle es un atributo por lo que la creación del objeto tiene que ser después del ros::ini
        ros::Subscriber subOdom;
        ros::ServiceServer server;
        ros::Publisher pubMov;
        float xActual;
        float yActual;
        const static float VELOCIDAD=0.1;//Le estoy estableciendo un valor constante a nivel de clase en lugar de asignarlo
                                        // en el constructor, por eso es const y static
        const static float DISTANCIA=0.05;

        void callBackOdom(const nav_msgs::OdometryConstPtr & msg){

            xActual=msg->pose.pose.position.x+2;
            yActual=msg->pose.pose.position.y+2;
          



        }

        void moverRobot(geometry_msgs::Twist & msg_mov, int direccion, int pasos)
        {
                ros::Rate loop_rate(1);
                msg_mov.linear.x=VELOCIDAD*direccion;
                ROS_INFO("Moviendo el robot %i en la direccion: %s ", pasos, (direccion>0)?"Positiva":"Negativa");
                for(int i=0; i<pasos;i++){
                    pubMov.publish(msg_mov);
                    loop_rate.sleep();

                }
                msg_mov.linear.x=0;
        }

        void girarRobot(geometry_msgs::Twist & msg_mov, int direccion, int giros=2)
        {
            ros::Rate loop_rate(1);
            msg_mov.angular.z=1.6*direccion;
            ROS_INFO("GIrando el robot");
            for(int i=0; i<giros;i++)
            {
                pubMov.publish(msg_mov);
                loop_rate.sleep();
            }
            msg_mov.angular.z=0;


        }

        bool callBackCoordenadas(ej5_examen::coordenadaRequest & req, ej5_examen::coordenadaResponse & res){
            float x_nueva=req.x;
            float y_nueva=req.y;
            bool rdo=true;
            geometry_msgs::Twist msg_mov;


            if(0.5<= x_nueva && x_nueva<=3.0 && 0.5<=y_nueva && y_nueva<=5.0){
                ROS_INFO("Moviendo el robot a las coordenadas (%f,%f)",x_nueva, y_nueva);
                float x_diff=x_nueva-xActual;
                float y_diff=y_nueva-yActual;

                if(x_diff!=0){
                    ROS_INFO("Moviendo las X");
                    moverRobot(msg_mov,(x_diff>0)?1:-1, abs(int(x_diff/DISTANCIA)));

                }

                if(y_diff!=0){
                    ROS_INFO("Moviendo las Y");
                    girarRobot(msg_mov, 1);
                    moverRobot(msg_mov,(y_diff>0)?1:-1, abs(int(y_diff/DISTANCIA)));
                    girarRobot(msg_mov, -1);
                }
            }
            else{
                ROS_INFO("Coordenadas no validas");
                rdo=false;
            }

            res.status=rdo;

            return true;


        }


    public:
    Robot( string name_srv)
    {
        /*El constructor es el que asigna los valores a los atributos por lo que es donde tenemos que inicializar
        los publicadores, subscriptores y servicios. EL objeto  NodeHandle ya se crea solo con el constructor por defecto*/
        
            xActual=0.0;
            yActual=0.0;

            /*El método subscribe cambia respecto a la versión estructurada
            Tenemos que especificar la función que usaremos como callBack. Como la función es parte de una clase
            tenemos que especificar su "localización" (parecido al namespace) nombre_clase::nombre_funcion
            El uso del <<&>> es porque necesitamos obtener un puntero a esa función y al no ser una función estática
            es necesario ponerlo de forma expresa (en la versión estructurada no era necesario por que lo infería
            pero realmente lo podéis usar también). Finalmente necesita un puntero al propio objeto por eso ponemos
            el <<this>>
            La forma de instanciar la plantilla (especificar los tipos genéricos T y M ) también cambia un poco porque
             ahora tenemos un mensaje y una clase y es necesario especificar sus nombres PERO en realidad al usar los
             callBacks normalmente puede inferir los tipos que tiene que usar  y si no los ponéis no debería
             de daros problemas
             ej.  subOdom=nh.subscribe("odom", 10, &Robot::callBackOdom,this);
          
            */
            subOdom=nh.subscribe<nav_msgs::Odometry, Robot>("odom", 10, &Robot::callBackOdom,this);
            server=nh.advertiseService<Robot, ej5_examen::coordenadaRequest, ej5_examen::coordenadaResponse>(name_srv,&Robot::callBackCoordenadas, this);
            pubMov=nh.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity",10);


    }

};

int main (int argc , char ** argv)
{
    //inicializamos ROS como siempre
    ros::init(argc, argv, "servidor_clase");
    //ojo!! no creamos el NodeHandle, en este caso es un atributo del objeto el cual tenemos que crear después del init
    Robot robot("servidor_srv");

    ros::spin();
    return 0;

}
