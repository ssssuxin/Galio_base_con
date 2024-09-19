#include "subscribe_pub.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>

static const char jsonfile[] = "new.dat";  // 改为二进制文件
// 构造函数
RosPubSub::RosPubSub(ros::NodeHandle& nh) : nh_(nh)
{
    V_X_L = 0;
    V_Z_A = 0;
    update = false;
    // 初始化订阅者，订阅 "/input_topic"
    subscriber_ = nh_.subscribe("/cmd_vel", 10, &RosPubSub::messageCallback, this);

    // 初始化发布者，发布到 "/output_topic"
    publisher_ = nh_.advertise<std_msgs::String>("/output_topic", 10);
}

// 回调函数，当接收到消息时调用
void RosPubSub::messageCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
    std::cout << "Received cmd_vel message:" << std::endl;
    std::cout << "Linear: [" 
              << msg->linear.x << ", " 
              << msg->linear.y << ", " 
              << msg->linear.z << "]" << std::endl;
    std::cout << "Angular: [" 
              << msg->angular.x << ", " 
              << msg->angular.y << ", " 
              << msg->angular.z << "]" << std::endl;
    V_X_L = msg->linear.x;
    V_Z_A = msg->angular.z;
    update = true;
    Write_date();

}

void RosPubSub::Write_date()
{
    FILE *fp;
    // 使用 "wb+" 模式打开文件以写入二进制数据
    if ((fp = fopen(jsonfile, "wb+")) == NULL)
    {
        printf("Failed to open file.\n");
        return;
    }

    // 加锁
    if (0 == flock(fileno(fp), LOCK_EX))
    {
        printf("lock...\n");

        // 写入两个 double 变量和一个 bool 变量到文件
        fwrite(&V_X_L, sizeof(double), 1, fp);
        fwrite(&V_Z_A, sizeof(double), 1, fp);
        fwrite(&update, sizeof(int), 1, fp);  // 使用 int 类型写入 bool

        // 解锁并关闭文件
        fclose(fp);
        flock(fileno(fp), LOCK_UN);
    }
    else
    {
        printf("lock failed\n");
    }
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "galileo_st");
    ros::NodeHandle nh;
    RosPubSub ros_interface(nh);
    ros::spin();
    ros::shutdown();
    return 0;
}
