#include <yarp/os/Bottle.h>
#include <yarp/os/Network.h>
#include <yarp/os/RpcClient.h>
#include "ros/ros.h"
#include "std_msgs/String.h"


yarp::os::RpcClient port;
const std::string client_name = "/head_control";
std::string server_name = "/SIM_CER_ROBOT/head/rpc:i";
 
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
    if (msg->data.at(0) == '/'){
        yarp::os::Network::disconnect(client_name, server_name);
        server_name = msg->data;
        std::cout << "Server port was set to " << server_name << std::endl;
        yarp::os::Network::connect(client_name, server_name);
    }else{
        if (port.getOutputCount() == 0) {
            std::cout << "Connecting to " << server_name << std::endl;
            yarp::os::Network::connect(client_name, server_name);
        }else{
            yarp::os::Bottle cmd;
            std::stringstream test(msg->data);
            std::string segment;
            std::vector<std::string> seglist;

            while(std::getline(test, segment, ' '))
            {
                seglist.push_back(segment);
            }

            if (seglist.size() < 4){
                std::cout << "Skipping... Not enough paramaters received..." << std::endl;
                return;
            }

            cmd.addString(seglist[0]);
            cmd.addString(seglist[1]);
            cmd.addInt32(stoi(seglist[2]));
            cmd.addFloat32(stof(seglist[3]));

            std::cout << "Sending message... " << cmd.toString() << std::endl;
            yarp::os::Bottle response;
            port.write(cmd, response);
            std::cout << "Got response: " << response.toString() << std::endl;
        }
    }
}

int main(int argc, char* argv[])
{
    ros::init(argc, argv, "yarp_rpc_subscriber");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("yarp_rpc_publisher", 1000, chatterCallback);
 
    yarp::os::Network yarp;
    port.open(client_name);
 
    ros::spin();
    
    return 0;
}
