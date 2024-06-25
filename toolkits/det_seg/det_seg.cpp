#include <iostream>
#include <filesystem>
#include <fstream>
#include <sys/stat.h>

#include "det_seg.h"



DetSeg::DetSeg(DetSegConfig config)
{
    cfg = config;
    int ret = initSource();

    if (ret == 0) {
        inited = true;
        std::string configPath = cfg.modelDir + "/config.json";
        std::string modelPath = cfg.modelDir + "/model.rknn";
        spdpConfig = SpdpReadConfig(configPath);

        // 初始化
        SpdpInit(spdpConfig, modelPath);
        SpdpSetScoreThresh(cfg.scoreThresh);
        if (videoSource) {
            resultPath = cfg.sourcePath + "-det.mp4";
            vw.open(resultPath, cv::CAP_FFMPEG, cv::VideoWriter::fourcc('a', 'v', 'c', '1'),
                    fps, cv::Size(imageWidth, imageHeight), true);
        } else {
            resultPath = cfg.sourcePath + "-det/";
            if (std::filesystem::exists(resultPath)) {
                std::string rmCmd = std::string("rm -r ") + resultPath;
                system(rmCmd.c_str());
            }
            mkdir(resultPath.c_str(), 0777);
        }
    }
}


int DetSeg::run()
{
    if (!inited) return -1;
    std::string filename;
    float forwardTime, postTime;
    float sumPreTime = 0.f;
    float sumForwardTime = 0.f;
    float sumPostTime = 0.f;

    cv::Mat oriImage, resImage;
    int frameIdx = 0;
    int frameCount = 0;

    while (frameIdx < cfg.runFrameNum) {
        oriImage = readFrame(frameIdx, filename);

        std::vector<Instance> instances = SpdpRun(oriImage, nullptr, &forwardTime, &postTime);
        frameCount += 1;
        sumForwardTime += forwardTime;
        sumPostTime += postTime;
        resImage = SpdpPlotInstance(oriImage, instances, spdpConfig.classNames);
        if (videoSource) {
            vw.write(resImage);
            printf("frame: %d, target nums: %d\n", frameIdx, (int)instances.size());
        } else {
            cv::imwrite(resultPath + filename, resImage);
            printf("frame: %s, target nums: %d\n", filename.c_str(), (int)instances.size());
        }
        frameIdx += 1;
    }

    printf("forward time: %.2fms, post time: %.2fms\n",
            sumForwardTime / cfg.runFrameNum,
            sumPostTime / cfg.runFrameNum);
    if (videoSource) {
        cap.release();
        vw.release();
    }
    // 释放
    SpdpRelease();
    return 0;
}




int DetSeg::initSource()
{
    int ret = 0;
    if (std::filesystem::is_directory(cfg.sourcePath)) {
        ret = initSequenceSource();
    } else {
        ret = initVideoSource();
    }
    if (ret) return ret;

    return ret;
}


int DetSeg::initSequenceSource()
{
    cv::glob(cfg.sourcePath, filenames);
    if (filenames.empty()) {
        return -1;
    }

    int runFrameNum = (int)filenames.size();
    if (cfg.runFrameNum == 0) {
        cfg.runFrameNum = runFrameNum;
    } else {
        cfg.runFrameNum= std::min((int)cfg.runFrameNum, runFrameNum);
    }
    videoSource = false;
    std::string filename;
    return 0;
}


int DetSeg::initVideoSource()
{
    cap.open(cfg.sourcePath);
    if (!cap.isOpened()) {
        printf("open '%s' failed!", cfg.sourcePath.c_str());
        return -1;
    }
    int runFrameNum = (int)cap.get(cv::CAP_PROP_FRAME_COUNT);
    fps = (double)cap.get(cv::CAP_PROP_FPS);
    if (cfg.runFrameNum == 0) {
        cfg.runFrameNum = runFrameNum;;
    } else {
        cfg.runFrameNum= std::min((int)cfg.runFrameNum, runFrameNum);
    }
    videoSource = true;
    imageWidth = (int)cap.get(cv::CAP_PROP_FRAME_WIDTH);
    imageHeight = (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    return 0;
}

cv::Mat DetSeg::readFrame(int frame_idx, std::string& filename)
{
    cv::Mat image;
    char imagename[100];
    if (videoSource) {
        cap >> image;
        filename = std::to_string(frame_idx);
    } else {
        std::string filepath = filenames[frame_idx];
        image = cv::imread(filepath);
        sprintf(imagename, "%s", filepath.c_str());
        filename = std::string(basename(imagename));
        imageWidth = image.cols;
        imageHeight = image.rows;
    }
    return image;
}

