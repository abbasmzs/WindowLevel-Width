#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Read 16-bit image
    cv::Mat img = cv::imread("D:/A.mazrouei/Data/RawData_1.tiff", cv::IMREAD_ANYDEPTH);
    if (img.empty()) {
        std::cerr << "Error: could not read image" << std::endl;
        return -1;
    }
    cv::bitwise_not(img,img);

    // Find maximum value
    double minValFi, maxValFi;
    cv::minMaxLoc(img, &minValFi, &maxValFi);
    std::cout << "Maximum value of image: " << maxValFi << std::endl;


    // Calculate histogram
    int histSize = 65535;
    float range[] = { 7000, 65535 };
    const float* histRange = { range };
    cv::Mat hist;
    cv::calcHist(&img, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange);

    // Find maximum value and its location in histogram
    double maxVal;
    cv::Point maxLoc;
    cv::minMaxLoc(hist, nullptr, &maxVal, nullptr, &maxLoc);
    std::cout << "Maximum value of histogram: " << maxVal << std::endl;
    std::cout << "Location of maximum value in histo: " << maxLoc.y << std::endl;


    // Plot histogram
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);
    cv::Mat histImage(hist_h, hist_w, CV_16UC1, cv::Scalar(0));
    cv::normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX);
    for (int i = 7000; i < histSize; i++) {
        cv::line(histImage,
            cv::Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
            cv::Point(bin_w * i, hist_h - cvRound(hist.at<float>(i))),
            cv::Scalar(65535), 2);
    }
    cv::imshow("Histogram", histImage);
    cv::waitKey(0);


    return 0;
}