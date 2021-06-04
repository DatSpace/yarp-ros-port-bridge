#include <yarp/os/Bottle.h>
#include <yarp/os/Network.h>
#include <yarp/os/Port.h>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <algorithm>

std::vector<std::pair<std::string, yarp::os::Port*>> ports_list;

void wrapperCallback(const std_msgs::String::ConstPtr &msg)
{
    std::stringstream data_stream_(msg->data);
    std::string data_segment;
    std::vector<std::string> segment_list;
    
    while (std::getline(data_stream_, data_segment, ' '))
    {
        segment_list.push_back(data_segment);
    }

    if (segment_list.size() >= 2)
    {
        if (segment_list[0] == "connect")
        {
            std::string temp_server = segment_list[1];

            if (!yarp::os::Network::isConnected(temp_server + "_wrapper", temp_server))
            {
                std::cout << "Connecting to " << temp_server << std::endl;

                ports_list.push_back(std::pair<std::string, yarp::os::Port*> (temp_server, new yarp::os::Port));
                
                ports_list[ports_list.size()-1].second->open(temp_server + "_wrapper");
                ports_list[ports_list.size()-1].second->addOutput(temp_server);
            }
            else
            {
                std::cout << "Wrapper already connected to " << temp_server << "! Skiping,.." << std::endl;
                return;
            }
        }
        else if (segment_list[0] == "disconnect")
        {
            std::string temp_server = segment_list[1];

            if (yarp::os::Network::isConnected(temp_server + "_wrapper", temp_server))
            {
                std::cout << "Connecting to " << temp_server << std::endl;
                yarp::os::Network::disconnect(temp_server + "_wrapper", temp_server);
                int temp_pair_index = 0;
                for (int i = 0; i <= ports_list.size(); i++)
                {
                    if (ports_list[i].first == temp_server)
                    {
                        temp_pair_index = i;
                        delete ports_list[i].second;
                        break;
                    }
                }
                ports_list.erase(ports_list.begin()+temp_pair_index);
            }
            else
            {
                std::cout << "Wrapper not connected to " << temp_server << "! Skiping,.." << std::endl;
                return;
            }
        }
        else if (segment_list[0] == "write")
        {
            bool exists = false;
            yarp::os::Port *temp_port;
            std::string temp_server = segment_list[1];

            for (int i = 0; i < ports_list.size(); i++)
            {
                if (ports_list[i].first == temp_server)
                {
                    temp_port = ports_list[i].second;
                    exists = true;
                    break;
                }
            }

            if (!exists)
            {
                std::cout << "Port wrapper doesnt exist. Skipping..." << std::endl;
                return;
            }

            if (temp_port->getOutputCount() == 0)
            {
                std::cout << "Port exists but not connected to any other ports. Skipping..." << std::endl;
                return;
            }
            else
            {
                yarp::os::Bottle cmd;

                if (segment_list.size() < 3)
                {
                    std::cout << "Not enough paramaters received for writting. Skipping..." << std::endl;
                    return;
                }

                // for (int i = 2; i < segment_list.size(); i++)
                // {
                //     cmd.addString(segment_list[i]);
                // }
                cmd.addString(segment_list[2]);
                cmd.addString(segment_list[3]);
                cmd.addInt32(stoi(segment_list[4]));
                cmd.addFloat32(stof(segment_list[5]));

                std::cout << "Sending message: " << cmd.toString() << std::endl;
                temp_port->write(cmd);
            }
        }
        else if (segment_list[0] == "read")
        {
            std::cout << "Reading is not implemented yet..." << std::endl;
        }
        else
        {
            std::cout << "Not supported command/format..." << std::endl;
        }
    }
    else
    {
        std::cout << "Error: You need to give at least 1 parameter. Ex. \"connect /cer/head/rpc:i\"" << std::endl;
    }
}

int main(int argc, char *argv[])
{
    YARP_UNUSED(argc);
    YARP_UNUSED(argv);
    yarp::os::Network yarp;

    ros::init(argc, argv, "yarp_rpc_subscriber");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("yarp_rpc_publisher", 10, wrapperCallback);

    ros::spin();

    return 0;
}
