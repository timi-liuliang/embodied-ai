#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    // Read chessboard image
    cv::Mat image = cv::imread("chessboard.png", cv::IMREAD_GRAYSCALE);

    // Set chessboard dimensions
    cv::Size boardSize(6, 9);

    // Save detected chessboard corner points
    std::vector<std::vector<cv::Point2f>> imagePoints;

    // Detect chessboard corners
    bool patternFound = cv::findChessboardCorners(image, boardSize, imagePoints[0]);

    // If chessboard corners are detected successfully
    if (patternFound) {
        // Refine corner positions with subpixel accuracy
        cv::cornerSubPix(image, imagePoints[0], cv::Size(11, 11), cv::Size(-1, -1),
            cv::TermCriteria(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, 30, 0.1));

        // Set world coordinates for calibration board
        std::vector<cv::Point3f> objectPoints;
        for (int i = 0; i < boardSize.height; i++) {
            for (int j = 0; j < boardSize.width; j++) {
                objectPoints.push_back(cv::Point3f(j, i, 0));
            }
        }

        // Get camera intrinsic parameters and distortion coefficients
        cv::Mat cameraMatrix, distCoeffs;
        std::vector<cv::Mat> rvecs, tvecs;

        cv::calibrateCamera(std::vector<std::vector<cv::Point3f>>(1, objectPoints), imagePoints,
            image.size(), cameraMatrix, distCoeffs, rvecs, tvecs);

        // Save the results to a text file
        cv::FileStorage fs("calibration_results.txt", cv::FileStorage::WRITE);
        fs << "Camera_Matrix" << cameraMatrix;
        fs << "Distortion_Coefficients" << distCoeffs;
        fs.release();

        std::cout << "Camera calibration completed, and the results are saved in calibration_results.txt file." << std::endl;
    }
    else {
        std::cout << "Unable to detect chessboard corners." << std::endl;
    }

    return 0;
}