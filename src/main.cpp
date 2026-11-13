
#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    std::cout << "================================\n";
    std::cout << " FPGA Gesture Recognition\n";
    std::cout << "================================\n";

    std::cout << "OpenCV version: "
              << CV_VERSION << std::endl;

    // Initialize camera
    std::cout << "[INFO] Initializing camera..." << std::endl;

    cv::VideoCapture camera(0, cv::CAP_DSHOW);

    if (!camera.isOpened())
    {
        std::cerr << "[ERROR] Cannot open camera!" << std::endl;
        return 1;
    }

    std::cout << "[INFO] Camera successfully opened!" << std::endl;

    // Capture frames
    cv::Mat frame;

    std::cout << "[INFO] Starting video stream..." << std::endl;

    while (true)
    {
        if (!camera.read(frame))
        {
            std::cerr << "[ERROR] Cannot read frame!" << std::endl;
            break;
        }

        if (frame.empty())
        {
            std::cerr << "[WARNING] Empty frame!" << std::endl;
            continue;
        }

        // Display frame
        cv::imshow("FPGA Gesture Recognition", frame);

        // Exit when ESC is pressed
        if (cv::waitKey(1) == 27)
        {
            std::cout << "[INFO] ESC pressed. Exiting..." << std::endl;
            break;
        }
    }

    camera.release();
    cv::destroyAllWindows();

    std::cout << "[INFO] Application finished." << std::endl;

    return 0;
}
