#include <opencv2/opencv.hpp>
#include <iostream>

// 定义枚举类型，表示计算模式
enum class CropMode {
    Rectangle,       // 计算矩形区域的平均 RGB 值
    InscribedCircle  // 计算矩形内接圆的平均 RGB 值
};

cv::Vec3f calculateRegionRGB(const cv::Mat& image, const cv::Rect& rect, CropMode mode,
    std::vector<cv::Rect> excludeRegions = {}, CropMode excludeMode = CropMode::Rectangle) {
    // 检查图像是否为空
    if (image.empty()) {
        throw std::invalid_argument("Input image is empty.");
    }

    // 检查图像是否为彩色图像
    if (image.channels() != 3) {
        throw std::invalid_argument("Input image must be a 3-channel (RGB) image.");
    }

    // 检查矩形是否在图像范围内
    cv::Rect imageBounds(0, 0, image.cols, image.rows);
    cv::Rect validRect = rect & imageBounds; // 取交集，确保矩形在图像范围内

    if (validRect.width <= 0 || validRect.height <= 0) {
        throw std::invalid_argument("The rectangle is outside the image bounds.");
    }

    // 创建掩码
    cv::Mat mask = cv::Mat::zeros(image.size(), CV_8UC1);

    // 根据模式标记主区域
    if (mode == CropMode::Rectangle) {
        mask(validRect).setTo(255);
    }
    else if (mode == CropMode::InscribedCircle) {
        int radius = std::min(validRect.width, validRect.height) / 2;
        cv::Point center(validRect.x + validRect.width / 2, validRect.y + validRect.height / 2);
        cv::circle(mask, center, radius, cv::Scalar(255), -1);
    }
    else {
        throw std::invalid_argument("Invalid crop mode.");
    }

    // 处理需要排除的区域
    for (const auto& excludeRect : excludeRegions) {
        // 确保排除区域在主区域内，且不等于主区域
        if ((excludeRect & validRect) != excludeRect || excludeRect == validRect) {
            continue; // 跳过无效的排除区域
        }

        if (excludeMode == CropMode::Rectangle) {
            // 在掩码中去掉矩形区域
            mask(excludeRect).setTo(0);
        }
        else if (excludeMode == CropMode::InscribedCircle) {
            // 计算内接圆的半径和中心点
            int radius = std::min(excludeRect.width, excludeRect.height) / 2;
            cv::Point center(excludeRect.x + excludeRect.width / 2, excludeRect.y + excludeRect.height / 2);
            cv::circle(mask, center, radius, cv::Scalar(0), -1);
        }
    }

    // 使用掩码计算平均 RGB 值
    cv::Scalar meanRGB = cv::mean(image, mask);

    // 返回平均 RGB 值
    return cv::Vec3f(meanRGB[2], meanRGB[1], meanRGB[0]); // 注意：OpenCV 的通道顺序是 BGR
}

int main() {
    // 读取图像
    cv::Mat image = cv::imread(R"(C:\Users\rw\Desktop\1.png)");

    if (image.empty()) {
        std::cerr << "Error: Could not load image." << std::endl;
        return -1;
    }

    // 定义主矩形区域
    cv::Rect rect(50, 50, 200, 200);

    // 定义需要排除的子区域
    std::vector<cv::Rect> excludeRegions = {
        cv::Rect(70, 70, 50, 50), // 子矩形 1
        cv::Rect(150, 150, 30, 30) // 子矩形 2
    };

    try {
        // 创建掩码
        cv::Mat mask = cv::Mat::zeros(image.size(), CV_8UC1);

        // 标记主区域
        mask(rect).setTo(255);

        // 排除子区域
        for (const auto& excludeRect : excludeRegions) {
            mask(excludeRect).setTo(0);
        }

        // 使用掩码抠出主区域
        cv::Mat croppedRegion;
        image.copyTo(croppedRegion, mask);

        // 提取主区域的边界矩形
        cv::Rect boundingRect = rect;

        // 显示抠出的主区域
        cv::imshow("Cropped Region", croppedRegion(boundingRect));

        // 计算矩形区域的平均 RGB 值，排除子矩形区域
        cv::Vec3f avgRGBRect = calculateRegionRGB(image, rect, CropMode::Rectangle, excludeRegions, CropMode::Rectangle);
        std::cout << "Rectangle (Excluding Sub-Regions) - Average R: " << avgRGBRect[0]
            << ", G: " << avgRGBRect[1]
            << ", B: " << avgRGBRect[2] << std::endl;

        // 等待用户按键退出
        cv::waitKey(0);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}