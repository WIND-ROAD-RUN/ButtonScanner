#include <string>
#include <iostream>
#include"ime_ModelEngine.h"

int main(int argc, char* argv[])
{
    std::string modelPath = R"(C:\Users\34615\Desktop\best.engine)";
    std::string name_file = R"(C:\Users\34615\Desktop\index.names)";

    rw::ime::ModelEngine modelEngine(modelPath, name_file);


    std::string imgpath = R"(C:\Users\34615\Desktop\1.png)";
    cv::Mat img = cv::imread(imgpath.c_str());
    if (img.empty()) {
        std::cerr << "Failed to load image: " << imgpath << std::endl;
        return -1;
    }

    std::vector<rw::ime::ProcessRectanglesResult> vecrecogresult;
    cv::Mat resultMat;
    cv::Mat maskmat;

    auto isProcess=modelEngine.ProcessMask(img, resultMat, maskmat, vecrecogresult);

    std::cout << isProcess;

    cv::imshow("Asd", resultMat);
    
    cv::waitKey();

    return 0;
}