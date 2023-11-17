# 接入joystick手柄

1. 安装`ros-noetic-joy`功能包

   ```
    sudo apt-get install ros-noetic-joy
   ```

2. 检查系统是否检测到合适硬件

   ```
    ls /dev/input/
   ```

   `js0`是我们的手柄

3. 测试手柄是否可以正常操作

   ```
    sudo jstest /dev/input/js0
   ```

   有类似输出如下：

   ```
   Axes: 0: 0 1: 0 2: 0 
   Buttons: 0:off 1:off 2:off 3:off 4:off 5:off 6:off 7:off 8:off 9:off 10:off
   ```

4. 利用joy_node发出手柄的运动topic

   ```
   rosrun joy joy_node _dev:=/dev/input/js0
   rostopic echo /joy
   ```

   至此，手柄信号已传入`ros`相应`topic`中





# 接入摄像机

1. 安装`ros-noetic-usb-cam`功能包

   ```
   sudo apt-get install ros-noetic-usb-cam
   ```

   `ros-noetic-usb-cam`是ROS中用于支持`USB`摄像头的软件包。在ROS中，`USB`摄像头通常被用于机器人视觉系统、自主导航和环境感知等方面。该软件包提供了与`USB`摄像头通信和数据传输所需的节点和工具。

2. 查看相机类型

   ```
   v4l2-ctl -d 0 --all
   ```

   查看相机提供的像素格式

3. 参数设置

   ```
   rosparam set usb_cam/pixel_format ***
   ```

   `***`表示查到的像素格式，比如`mjpeg`

4. 启动功能包

   ```
   rosrun usb_cam usb_cam_node _video_device:=/dev/video0 
   ```

   `_video_device:=/dev/video0`表示调用设备

   `video0`一般默认为计算机自带的摄像头

5. 可视化图像

   ```
   rosrun image_view image_view image:=/usb_cam/image_raw
   ```

   `image:=/usb_cam/image_raw`表示可视化信息来源

   或者通过`rviz`来显示图像



# 接入astra_camera(RGBD相机)

1. install dependencies

   ```
   # Assuming you have sourced the ros environment, same below
   sudo apt install libgflags-dev  ros-$ROS_DISTRO-image-geometry ros-$ROS_DISTRO-camera-info-manager\
   ros-$ROS_DISTRO-image-transport ros-$ROS_DISTRO-image-publisher libgoogle-glog-dev libusb-1.0-0-dev libeigen3-dev
   ```

2. install libuvc

   ```
   sudo apt-get install ros-noetic-libuvc-*
   ```

3. 下载pkg文件

   * ```
      cd ~/ros_ws/src
      git clone https://github.com/orbbec/ros_astra_camera.git
     ```

   * download zip

4. 编译pkg

   ```
   cd ~/ros_ws
   catkin_make
   ```

5. 运行

   ```
   roslaunch astra_camera astra.launch
   ```





# 接入slamtec_robot底盘

1. install serial pkg

   ```
   sudo apt-get install ros-noetic-serial
   ```

2. pkg文件teacher提供了，获取方式不详

3. 查看dev

   ```
   ls /dev
   ```

   一般为ttyUSB0

4. 修改base_serial.launch文件中参数

   ```
   <param name="usart_port_name"    type="string" value="/dev/ttyUSB0"/>
   ```

5. 编译pkg

   ```
   cd ~/ros_ws
   catkin_make
   ```

6. 运行

   ```
   roslaunch turn_on_slamtec_robot base_serial.launch
   ```

   此时可以查看topic，查看底盘受哪些topic控制

   事实上，控制该底盘的topic和`turtlesim`一致，均为`/cmd_vel`