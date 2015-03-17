
#ifndef MASKOR_GIGE_CAM_H
#define MASKOR_GIGE_CAM_H

#define _UNIX_
#define BUFFER_COUNT ( 16 )

#include <iostream>
#include <boost/thread.hpp>
#include <opencv2/opencv.hpp>
#include <list>

//For user input without pause
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>

//PLEORA SDK
#include <PvSystem.h>
#include <PvDevice.h>
#include <PvStream.h>
#include <PvResult.h>
#include <PvInterface.h>
#include <PvDeviceInfo.h>
#include <PvBuffer.h>
#include <PvImage.h>
#include <PvGenParameterArray.h>


namespace maskor
{

class GigeCam
{
public:
    GigeCam();
    ~GigeCam();

    void open();
    void close();
    void start();
    void stop();
    void autoFocus();
    void acquisitionStop();
    void acquisitionStart();

    //Sensor getter
    void getSensorInfo();
    int getFocusPosition();
    double getFocusDistance();


    //Sensor setter
    void setIRFormat(int i);
    void setSize(int w, int h);
    void setOffset(int x, int y);
    void setPixelFormat(int i);
    void setTestImage(int i);
    void setAcquisitionMode(int i);
    void setAcquisitionFrameCount(int i);
    void SensorSetDefaults();
    void SensorSetFactoryDefaults();
    void setFocusPosition(int i);
    void setFocusDistance(float i);
    void setFocusDirection(int i);
    void setAutoFocusMethod(int i);
    void setNUCMode(int i);
    void setNoiseReduction(int i);
    void setIRFrameRate(int i);
    void NUCAction();
    void setFocusStep(int i);
    void FocusDecrement();
    void FocusIncrement();

    //getter and setter
    boost::shared_ptr<cv::Mat> getImage();

private:
    //genicam / eBUS SDK
    PvSystem System_;
    PvPipeline* Pipeline_;
    PvDevice* Device_;
    PvDeviceInfo* DeviceInfo_;
    PvStream* Stream_;
    PvImage* PvImage_;
    PvGenParameterArray* DeviceParams_;
    PvGenParameterArray* StreamParams_;
    std::list<PvBuffer*> Bufferlist_;

    //an own thread for the capture process (boost shared_ptr will delete itself if not used anymore)
    boost::shared_ptr<boost::thread> ImageThread_;

    //openCV Images
    boost::shared_ptr<cv::Mat> ImagePtr;

    //internal testing/helping functions
    int _findDevices();
    void _freeStreamBuffers();
    void _imageThread();
    void _showImages();
    void _ImgtoBinary();
    void _changemode(int);
    int  _kbhit(void);

    bool showImage;

}; //end class GigeCam



} //end namespace

#endif //MASKOR_GIGE_CAM_H

