#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    std::string videoPath = "D:/test/video.mp4";
    std::string outputPath = "D:/test/input/";

    cv::VideoCapture videoCapture(videoPath);

    if (!videoCapture.isOpened()) 
    {
        std::cerr << "Error opening video file!" << std::endl;
        return -1;
    }

    int framesCapturePerSecond = 1;
    double fps = videoCapture.get(cv::CAP_PROP_FPS);
    int interval = cvRound(fps / framesCapturePerSecond);

    int frameCount = 0;
    cv::Mat frame;

    while (videoCapture.read(frame)) 
    {
        if (frameCount % interval == 0)
        {
            std::string outputFilename = outputPath + "frame_" + std::to_string(frameCount) + ".jpg";
            cv::imwrite(outputFilename, frame);
        }

        frameCount++;
    }

    videoCapture.release();

    std::cout << "Frames extracted: " << frameCount << std::endl;

    return 0;
}