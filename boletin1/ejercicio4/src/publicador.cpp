#include <ros/ros.h>
#include <datos/datos1.h>
#include <iostream>
using namespace std;


int main(intargc,char **argv){
    int value;
    ros::init(argc,argv,"ejercicio4_node");
    ros::NodelHandle nh;

    ros::Publisher pub=nh.advertise<ejercicio4::datos>("calificacion",1);

    string nombre;
    int convocatoria;
    float nota;
    ejercio4::datos msg;

    cout<<"Escribe tu nombre completo: ";
    getline(cin,nombre);
    cout<<"Escribe el numero de convocatoria y la nota seprada por un espacio: ";
    scanf("%d%f",&convocatoria,&nota);

    msg.nombre = nombre;
    msg.convocatoria = convocatoria;
    msg.nota = nota;

    pub.publish(msg);

    while(ros::ok()){
        ROS__INFO("Introduce 1 si quieres enviar otro dato, = si quieres apagar el programa");
        cin>>value;
        if (value==1){
            cout<<"Introduce el nombre: ";
            cin>>nombre;    
            cout<<"Escribe el numero de convocatoria y la nota separado por un espacio: ";
            scanf("%d%f",&convocatoria,&nota);
            msg.nombre = nombre;
            msg.convocatoria = convocatoria;
            msg.nota=nota;
            pub.publish(msg);   
        }
        else{
            cout<<"Shutdown";
            ros::shutdown();
        }
    }
}
return 0;