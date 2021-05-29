#include <yarp/os/Bottle.h>
#include <yarp/os/Network.h>
#include <yarp/os/RpcClient.h>
#include "ros/ros.h"
#include "std_msgs/String.h"
 
using yarp::os::Bottle;
using yarp::os::Network;
using yarp::os::RpcClient;

RpcClient port;
 
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
    Bottle cmd;
    cmd.addString("set");
    cmd.addString("pos");

    std::stringstream test(msg->data);
    std::string segment;
    std::vector<std::string> seglist;

    while(std::getline(test, segment, '_'))
    {
        seglist.push_back(segment);
    }

    cmd.addInt32(stoi(seglist[0]));
    cmd.addFloat32(stof(seglist[1]));

    printf("Sending message... %s\n", cmd.toString().c_str());
    Bottle response;
    port.write(cmd, response);
    printf("Got response: %s\n", response.toString().c_str());
}

int main(int argc, char* argv[])
{

    ros::init(argc, argv, "yarp_rpc_subscriber");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("yarp_rpc_publisher", 1000, chatterCallback);

    if (argc < 3) {
        fprintf(stderr, "Please supply (1) a port name for the client\n");
        fprintf(stderr, "              (2) a port name for the server\n");
        return 1;
    }
 
    Network yarp;
    const char* client_name = "/head_control";
    const char* server_name = "/SIM_CER_ROBOT/head/rpc:i";
 
    port.open(client_name);

    if (port.getOutputCount() == 0) {
        printf("Can't connect to %s\n Will retry...", server_name);
        yarp::os::Network::connect(client_name, server_name);
    }
 
    ros::spin();
    
    return 0;
}
