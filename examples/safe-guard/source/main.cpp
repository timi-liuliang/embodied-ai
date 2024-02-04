#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <chrono>

bool detectHuman(cv::Mat& frame)
{
    cv::Mat gray, bg, diff, thresh;

    bool motionDetected = false;
    cv::Ptr<cv::BackgroundSubtractor> bgSubtractor = cv::createBackgroundSubtractorMOG2();

    // TODO: ������ʵ���˵Ķ�̬���
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    bgSubtractor->apply(gray, bg);

    cv::absdiff(bg, gray, diff);
    cv::threshold(diff, thresh, 30, 255, cv::THRESH_BINARY);

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(thresh, thresh, cv::MORPH_CLOSE, kernel);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(thresh, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    motionDetected = false;
    for (const auto& contour : contours) {
        double area = cv::contourArea(contour);
        if (area > 1000) { // ������С�����ֵ��ȷ����⵽�Ķ����㹻��
            motionDetected = true;
            break;
        }
    }

    return motionDetected;
}

int main(int argc, char** argv)
{
    // Set current path
    std::filesystem::path executablePath = std::filesystem::path(argv[0]);
    std::filesystem::path currentPath = executablePath.parent_path();
    std::filesystem::current_path(currentPath);

    cv::VideoCapture cap(0); // ������ͷ��0����Ĭ�ϵ�����ͷ�豸

    if (!cap.isOpened()) {
        std::cerr << "Error: Failed to open camera." << std::endl;
        return -1;
    }

    cv::Mat frame;

    std::chrono::steady_clock::time_point startTime, endTime;
    int videoDuration = 300; // 5 minutes in seconds
    cv::VideoWriter videoWriter;

    while (true) {
        cap >> frame;

        if (frame.empty()) {
            std::cerr << "Error: Failed to capture frame." << std::endl;
            break;
        }

        bool motionDetected = detectHuman(frame);
        if (motionDetected) 
        {
            if (!videoWriter.isOpened()) 
            {
                startTime = std::chrono::steady_clock::now();
                std::string filename = currentPath.string() + ("/video_" + std::to_string(startTime.time_since_epoch().count()) + ".avi");
                videoWriter.open(filename, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 24, cv::Size(frame.cols, frame.rows));
            }
            videoWriter.write(frame);
        }

        if (videoWriter.isOpened())
        {
            endTime = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsedSec = endTime - startTime;
            if (elapsedSec.count() >= videoDuration)
            {
                videoWriter.release();
                std::cout << "Video saved: " << std::endl;
            }
        }

        // ��⵽����ESC���˳�ѭ��
        if (cv::waitKey(1) == 27) {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}