#include "ros/ros.h"
#include "std_msgs/String.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <geometry_msgs/Twist.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include "boost/thread/mutex.hpp"
#include "boost/thread/thread.hpp"
#include <sstream>
#include <typeinfo>
#include <sys/types.h>
#include <signal.h>
#include <cctype>
#include <unistd.h>
#define PORT 4455



int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;

  ros::Publisher vel_pub_ = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

  // Variables and structures
  int server_fd, client_fd;
  struct sockaddr_in server_addr, client_addr;
  socklen_t addr_size;
  char buffer[1024];

  // Server socket
  server_fd = socket(AF_INET, SOCK_STREAM, 0);

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr("192.168.0.145"); // "192.168.35.80"

  bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  listen(server_fd, 5);
  printf("[LISTENING] Port Number: %d\n", PORT);
  
  client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_size);
  printf("[CONNECTED] New Connection\n");


  ros::Rate loop_rate(10);
  double linear_ = 0, angular_ = 0, l_scale_ = 0.3, a_scale_ = 0.5;

  while (ros::ok())
  {
 
    
        memset(buffer, '\0', sizeof(buffer));
        recv(client_fd, buffer, 1024, 0);
        send(client_fd, buffer, strlen(buffer), 0);

        std_msgs::String msg;
        std::stringstream ss;

        std::string str(buffer);
        ss << str;
        msg.data = ss.str();

        ROS_INFO("%s",msg.data.c_str());
              
        
        std_msgs::String msg2;
        std::stringstream ss2;
        ss2 << "0";
        msg2.data = ss2.str();

      
        geometry_msgs::Twist vel;

        if (std::stoi(msg.data) != std::stoi(msg2.data)){
            linear_ = 0.0;
            angular_ = 1.5;
	    kill(636,9); // pid

            vel.angular.z = a_scale_*angular_;
            vel.linear.x = l_scale_*linear_;
            vel_pub_.publish(vel);
            sleep(30); // according to the situation

            close(client_fd);
            close(server_fd);

            linear_=1.0;
            angular_ = 0.0;
            vel.angular.z = a_scale_*angular_;
            vel.linear.x = l_scale_*linear_;
            vel_pub_.publish(vel);
            sleep(2); // according to the situation

            linear_=0.0;
            angular_ = 0.0;
            vel.angular.z = a_scale_*angular_;
            vel.linear.x = l_scale_*linear_;
            vel_pub_.publish(vel);
            sleep(4); // according to the situation


            return 0;   
        }

        else{
            ros::spinOnce();
            loop_rate.sleep();
        }    
 }
 
}
