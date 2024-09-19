#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h> // 引入Twist消息类型，用于cmd_vel

class RosPubSub
{
public:
    // 构造函数
    RosPubSub(ros::NodeHandle& nh);

    // 回调函数
    void messageCallback(const geometry_msgs::Twist::ConstPtr& msg);
    void Write_date();

private:
    ros::NodeHandle nh_;               // ROS节点句柄
    ros::Subscriber subscriber_;       // 订阅者
    ros::Publisher publisher_;         // 发布者
    double V_X_L,V_Z_A;
    int update;

};