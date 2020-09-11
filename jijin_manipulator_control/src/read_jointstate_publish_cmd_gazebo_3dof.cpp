#include <ros/ros.h>
#include <stdio.h>
#include <iostream>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float64.h>

bool is_jointState = false;
sensor_msgs::JointState jointState_in;
void chatter_jointStatesMsg_Callback(const sensor_msgs::JointState::ConstPtr& jointStateMsg)
{
	//save the msg
	jointState_in.header 	= jointStateMsg->header;
	jointState_in.name 	= jointStateMsg->name;
	jointState_in.position 	= jointStateMsg->position;
	jointState_in.velocity 	= jointStateMsg->velocity;
	jointState_in.effort 	= jointStateMsg->effort;

	//set flag
	is_jointState = true;
}


int main(int argc, char** argv)
{
	ros::init(argc, argv, "athena_laser_merge_node");

	ros::NodeHandle nh_;
	ros::NodeHandle private_nh_;

  	//a Subscriber
	ros::Subscriber chatter_laserScanMsg_1_sub = nh_.subscribe("joint_states_in", 1, chatter_jointStatesMsg_Callback);

	// a Publisher
	ros::Publisher joint_1_pub = nh_.advertise<std_msgs::Float64>("joint_1_angle_out", 1);
	ros::Publisher joint_2_pub = nh_.advertise<std_msgs::Float64>("joint_2_angle_out", 1);
	ros::Publisher joint_3_pub = nh_.advertise<std_msgs::Float64>("joint_3_angle_out", 1);

	ros::Rate loop_rate(100);
	while(nh_.ok())
	{
		if(is_jointState)
		{
			//reset flag
			is_jointState = false;
			
			std_msgs::Float64 command_1;
			command_1.data = jointState_in.position[0];
			std_msgs::Float64 command_2;
			command_2.data = jointState_in.position[1];
			std_msgs::Float64 command_3;
			command_3.data = jointState_in.position[2];

			joint_1_pub.publish(command_1);
			joint_2_pub.publish(command_2);
			joint_3_pub.publish(command_3);
		}
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}
