#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include <iostream>
#include <wiringPi.h>
#include "libSonar.h"

using namespace std;

double Recup_Hauteur(){
  int trigger, echo;
  // Changer les PIN en fonction des branchements sur la raspberry pi.
  trigger = 22;
  echo = 23;

  if (wiringPiSetup() == -1)
          return -1;

      Sonar sonar;
      sonar.init(trigger, echo);

      hauteur = sonar.distance(5000); // 5000 is a timeout in microseconds // Distane en cm

  return hauteur
  }


// =============== MAIN ================
int main(int argc, char **argv)
{
  ros::init(argc, argv, "hauteur");
  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<std_msgs::Float64>("hauteur", 1000);
  ros::Rate loop_rate(10);


  double hauteur = 0;
  while (ros::ok())
  {
    std_msgs::Float64 msg;
    hauteur = Recup_Hauteur();
    msg.data = hauteur;

    pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();

  }
  return 0;
}
