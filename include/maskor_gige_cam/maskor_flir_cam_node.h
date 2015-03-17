#ifndef MASKOR_FLIR_CAM_NODE_H
#define MASKOR_FLIR_CAM_NODE_H

//GIGE CAM
#include <maskor_gige_cam/maskor_gige_cam.h>

//ROS
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <dynamic_reconfigure/server.h>
#include <maskor_gige_cam/FlirConfig.h>
#include <driver_base/SensorLevels.h>
#include <std_msgs/Float32MultiArray.h>

class FlirNode
{
public:
    FlirNode();
    ~FlirNode();

    //mainloop
    void receiveAndPublish();

private:
    // ROS
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Publisher RawImagePub_;
    image_transport::Publisher ThermalImagePub_;
    image_transport::Publisher TemperatureImagePub_;
    ros::Publisher TemperatureImagePub2_;
    sensor_msgs::ImagePtr ImagePtr_;

    // FLIR Camera
    boost::scoped_ptr <maskor::GigeCam> cam_;

    //OpenCV Images
    boost::shared_ptr<cv::Mat> RawImagePtr_;
    boost::shared_ptr<cv::Mat> ThermalImagePtr_;
    boost::shared_ptr<cv::Mat> TemperatureImagePtr_;

    //dynamic reconfigure
    dynamic_reconfigure::Server<maskor_gige_camera::FlirConfig> ReconfigSvr_;

    //internal helper functions
    double _pixel2temp(unsigned short pixelValue);
    void _thermalImageProc(cv::Mat &in, cv::Mat &out);
    void _temperatureImageProc(cv::Mat &in, cv::Mat &out);
    void _temperatureImageProc(cv::Mat &in, std_msgs::Float32MultiArray &array);
    void _showImages();
    void _configCb(maskor_gige_camera::FlirConfig &config, uint32_t level);

    //show images in separate openCV windows?
    bool showImages;

    std_msgs::Float32MultiArray temperatures;
};

#endif //MASKOR_FLIR_CAM_NODE_H
