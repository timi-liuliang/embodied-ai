#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    std::string videoPath = "path/to/video.mp4";
    std::string outputPath = "path/to/input/";

    cv::VideoCapture videoCapture(videoPath);

    if (!videoCapture.isOpened()) 
    {
        std::cerr << "Error opening video file!" << std::endl;
        return -1;
    }

    int frameCount = 0;
    cv::Mat frame;

    while (videoCapture.read(frame)) 
    {
        std::string outputFilename = outputPath + "frame_" + std::to_string(frameCount) + ".jpg";

        // Save the current frame as an image
        cv::imwrite(outputFilename, frame);

        frameCount++;
    }

    videoCapture.release();

    std::cout << "Frames extracted: " << frameCount << std::endl;

    return 0;
}