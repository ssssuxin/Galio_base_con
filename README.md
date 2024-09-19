这是伽利略的底盘通信DEMO（cmd_vel直接控制移动）

环境依赖：  
首先要配好SDK 安装细节 参照飞书链接https://gvtdwawnc78.feishu.cn/wiki/LFPEwwseRi565EkhA9icZPRlnab

使用方式  
将代码克隆在GalileoSDK目录下（跟GalileoSDKTest一个目录）  

    catkin_make
    rosrun GalileoSDKTest subscribe_pub 
    rosrun GalileoSDKTest test1
    rosrun teleop_twist_keyboard teleop_twist_keyboard.py
