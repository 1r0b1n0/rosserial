#include <ros/ros.h>
#include <ros/master.h>
#include <rosserial_msgs/RequestTopicsList.h>

bool service_handler(rosserial_msgs::RequestTopicsList::Request  &req,
         rosserial_msgs::RequestTopicsList::Response &res)
{
    (void)req;

    ros::master::V_TopicInfo topic_infos;
    ros::master::getTopics(topic_infos);
    for (ros::master::TopicInfo topic_info: topic_infos)
    {
        rosserial_msgs::RosTopicAndType topicAndType;
        topicAndType.topic = topic_info.name;
        topicAndType.type = topic_info.datatype;
        res.topics.push_back(topicAndType);
    }
    return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "topics_service_server");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("/get_topics_list", service_handler);
  ros::spin();

  return 0;
}
