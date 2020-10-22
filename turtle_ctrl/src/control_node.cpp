#include "ros/ros.h"


#include <stdlib.h>
#include <ros/service.h>

#include "geometry_msgs/Twist.h"
#include <turtlesim/Spawn.h>
#include <turtlesim/Kill.h>

# define PI           3.14159265358979323846 
int main(int argc, char **argv)
{
  // ROS node setup
  using namespace ros;
  
  std::string turtle_name = "Zukhurova";
  init(argc, argv, "Zukhurova_turtle_ctrl");
  NodeHandle n;

  //Create service client turtle1
  ServiceClient service = n.serviceClient<turtlesim::Spawn>("spawn");
  turtlesim::Spawn::Request rqt;
  turtlesim::Spawn::Response resp;
  rqt.x = 0;
  rqt.y = 5;
  rqt.name = turtle_name;
  ros::service::waitForService("spawn", ros::Duration(5));
  service.call(rqt,resp);

  //Go to loop for controlling turtle
  Publisher pub = n.advertise<geometry_msgs::Twist>(turtle_name + "/cmd_vel", 1000);
  Rate loop_rate(2);
  geometry_msgs::Twist twist;
  twist.angular.z = PI / 1.2;
  while (true)
  {
    
      twist.linear.x = 5.0;
      twist.linear.y = 0.0;
      twist.angular.z = -1;
      pub.publish(twist);
      spinOnce();
      loop_rate.sleep();
      if (!n.ok())
         return 0;
    }
  return 0;
}
