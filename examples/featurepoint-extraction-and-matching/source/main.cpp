#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) 
{
    // 读取两张图像
    cv::Mat image1 = cv::imread("path_to_image1.jpg", cv::IMREAD_GRAYSCALE);
    cv::Mat image2 = cv::imread("path_to_image2.jpg", cv::IMREAD_GRAYSCALE);

    // 初始化特征点检测器
    cv::Ptr<cv::FeatureDetector> detector = cv::ORB::create();

    // 检测特征点
    std::vector<cv::KeyPoint> keypoints1, keypoints2;
    detector->detect(image1, keypoints1);
    detector->detect(image2, keypoints2);

    // 提取特征描述子
    cv::Ptr<cv::DescriptorExtractor> extractor = cv::ORB::create();
    cv::Mat descriptors1, descriptors2;
    extractor->compute(image1, keypoints1, descriptors1);
    extractor->compute(image2, keypoints2, descriptors2);

    // 初始化特征匹配器
    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("BruteForce");

    // 特征点匹配
    std::vector<cv::DMatch> matches;
    matcher->match(descriptors1, descriptors2, matches);

    // 绘制匹配结果
    cv::Mat matchImage;
    cv::drawMatches(image1, keypoints1, image2, keypoints2, matches, matchImage);

    // 显示匹配结果
    cv::imshow("Matches", matchImage);
    cv::waitKey(0);

    return 0;
}