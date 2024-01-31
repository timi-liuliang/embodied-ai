#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) 
{
    // ��ȡ����ͼ��
    cv::Mat image1 = cv::imread("path_to_image1.jpg", cv::IMREAD_GRAYSCALE);
    cv::Mat image2 = cv::imread("path_to_image2.jpg", cv::IMREAD_GRAYSCALE);

    // ��ʼ������������
    cv::Ptr<cv::FeatureDetector> detector = cv::ORB::create();

    // ���������
    std::vector<cv::KeyPoint> keypoints1, keypoints2;
    detector->detect(image1, keypoints1);
    detector->detect(image2, keypoints2);

    // ��ȡ����������
    cv::Ptr<cv::DescriptorExtractor> extractor = cv::ORB::create();
    cv::Mat descriptors1, descriptors2;
    extractor->compute(image1, keypoints1, descriptors1);
    extractor->compute(image2, keypoints2, descriptors2);

    // ��ʼ������ƥ����
    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("BruteForce");

    // ������ƥ��
    std::vector<cv::DMatch> matches;
    matcher->match(descriptors1, descriptors2, matches);

    // ����ƥ����
    cv::Mat matchImage;
    cv::drawMatches(image1, keypoints1, image2, keypoints2, matches, matchImage);

    // ��ʾƥ����
    cv::imshow("Matches", matchImage);
    cv::waitKey(0);

    return 0;
}