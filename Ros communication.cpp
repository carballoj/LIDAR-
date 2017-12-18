#include <Wire.h>
#include <Arduino.h>
#include <MeMegaPi.h>
#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>
#include <Wire.h>
#include <LIDARLite.h>

LIDARLite myLidarLite;

//ROS node handle
ros::NodeHandle  nh;

// ROS Serial Range message definition
sensor_msgs::Range range_msg;

// definition of the ROS publisher for the range data
ros::Publisher pub_range( "range_data", &range_msg);
unsigned long range_timer;

// Frame ID used in the ROS topics
char frameid[] = "/laser_lite_v3";

void setup()
{
  Serial.begin(115200);
  
  myLidarLite.begin(0, true);
  myLidarLite.configure(0); // Change this number to try out alternate configurations
  
  /* ROS related */
  nh.initNode();
  nh.advertise(pub_range);
  range_msg.radiation_type = sensor_msgs::Range::INFRARED;
  range_msg.header.frame_id =  frameid;
  range_msg.field_of_view = 0.001;
  range_msg.min_range = 0.01;
  range_msg.max_range = 40.0;
  
}

void loop()
{
  // read and convert measurements to meters to comply with ROS
  range_msg.range = myLidarLite.distance()/100.0;
  range_msg.header.stamp = nh.now();
  pub_range.publish(&range_msg);
  range_timer =  millis();
  nh.spinOnce();  
}
