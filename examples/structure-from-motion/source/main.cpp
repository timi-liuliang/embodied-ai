#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) 
{
    if (argc > 1)
    {
        std::filesystem::path videoPath = argv[1];
        if(videoPath.is_relative())
            videoPath = std::filesystem::current_path() / videoPath;

        std::filesystem::path outputPath = videoPath.parent_path() / "frames/";
        if(!std::filesystem::exists(outputPath))
            std::filesystem::create_directories(outputPath);

        cv::VideoCapture videoCapture(videoPath.string());

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
                std::filesystem::path outputFilename = outputPath / ("frame_" + std::to_string(frameCount) + ".jpg");
                cv::imwrite(outputFilename.string(), frame);
            }

            frameCount++;
        }

        videoCapture.release();

        std::cout << "Frames extracted: " << frameCount << std::endl;

    }

    return 0;
}