#ifndef __DET_SEG_H__
#define __DET_SEG_H__
#include <opencv2/opencv.hpp>

#include "spdp/spdp.h"


const static int16_t MAX_IMAGE_WIDTH = 1920;
const static int16_t MAX_IMAGE_HEIGHT = 1080;

struct DetSegConfig {
    std::string sourcePath;
    std::string modelDir;
    uint16_t runFrameNum = 0;
    float scoreThresh = 0.5f;
};




class DetSeg {
public:
    DetSeg(DetSegConfig config);
    int run();

private:
    bool inited = false;
    bool videoSource;
    std::vector<cv::String> filenames;
    cv::VideoCapture cap;

    std::string resultPath;
    DetSegConfig cfg;
    SpdpConfig spdpConfig;
    cv::VideoWriter vw;
    double fps = 25.0;
    int imageWidth, imageHeight;

    int initSource();
    int initSequenceSource();
    int initVideoSource();
    cv::Mat readFrame(int frameIdx, std::string& filename);
};

#endif //__DET_SEG_H__