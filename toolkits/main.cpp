#include <iostream>
#include <fstream>
#include <sstream>
#include <getopt.h>
#include <filesystem>

#include "det_seg.h"

using namespace std;





int main(int argc, char* argv[])
{
    std::string sourcePath;
    std::string modelDir;
    uint16_t runFrameNum = 0;
    float scoreThresh = 0.5f;

    struct option longopts[] = {
        { "source",      required_argument,  NULL,  's'},
        { "model",       required_argument,  NULL,  'm'},
        { "num",         required_argument,  NULL,  'n'},
        { "score",       required_argument,  NULL,  't'},
        { 0,                  0,                  0,       0},
    };

    int ch;
    while ((ch = getopt_long(argc, argv, "s:m:n:t:", longopts, NULL)) != -1) {
        switch (ch) {
            case 's':
                sourcePath = optarg;
                break;
            case 'm':
                modelDir = optarg;
                break;
            case 'n':
                runFrameNum = atoi(optarg);
                break;
            case 't':
                scoreThresh = atof(optarg);
                break;
            }
    }

    // 初始化
    DetSegConfig cfg;
    cfg.sourcePath = sourcePath;
    cfg.modelDir = modelDir;
    cfg.runFrameNum = runFrameNum;
    cfg.scoreThresh = scoreThresh;

    DetSeg detSeg = DetSeg(cfg);
    detSeg.run();
}






