#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) 
{
    // Set current path
    std::filesystem::path executablePath = std::filesystem::path(argv[0]);
    std::filesystem::path currentPath = executablePath.parent_path();
    std::filesystem::current_path(currentPath);

    // Config two image path
    std::filesystem::path image1Path = std::filesystem::current_path() / "data/IMG_0400.jpg";
    std::filesystem::path image2Path = std::filesystem::current_path() / "data/IMG_0401.jpg";

    // Read two images
    cv::Mat image1 = cv::imread( image1Path.string(), cv::IMREAD_GRAYSCALE);
    cv::Mat image2 = cv::imread( image2Path.string(), cv::IMREAD_GRAYSCALE);

    double imageWidth = image1.cols;
    double imageHeight = image1.rows;

    // Initialize feature point detector
    cv::Ptr<cv::ORB> detector = cv::ORB::create();
    detector->setMaxFeatures(1024);

    // Detect feature points
    std::vector<cv::KeyPoint> keypoints1, keypoints2;
    detector->detect(image1, keypoints1);
    detector->detect(image2, keypoints2);

    // Extract feature descriptors
    cv::Ptr<cv::ORB> extractor = cv::ORB::create();
    cv::Mat descriptors1, descriptors2;
    extractor->compute(image1, keypoints1, descriptors1);
    extractor->compute(image2, keypoints2, descriptors2);

    // Initialize feature matcher
    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("BruteForce");

    // Match feature points
    std::vector<cv::DMatch> matches;
    matcher->match(descriptors1, descriptors2, matches);

    // Draw matching results
    cv::Mat matchImage;
    cv::drawMatches(image1, keypoints1, image2, keypoints2, matches, matchImage);

    // Display matching results
    cv::Size displaySize(imageWidth * 2.0 / 6.0, imageHeight * 2.0 / 12.0);
    cv::Mat resizedImage;
    cv::resize(matchImage, resizedImage, displaySize);
    cv::imshow("Matches", resizedImage);

    // Adjust window position
    int screenWidth = 1920;
    int screenHeight = 1080;
    int windowWidth = displaySize.width;
    int windowHeight = displaySize.height;

    int windowLeft = (screenWidth - windowWidth) / 2;
    int windowTop = (screenHeight - windowHeight) / 2;
    cv::moveWindow("Matches", windowLeft, windowTop);
    cv::waitKey(0);

    return 0;
}