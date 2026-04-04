#include "Edger.hpp"

/**
* Detect edges with Sobel algo
* @param img image to detect edges on
* @return None
*/
int Edger::detect_edges_sobel(const cv::Mat &img) {
    if (img.empty()) {
        return -1;
    }

    // 2. Convert to grayscale
    cv::Mat gray;
    cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    // 3. Blur to reduce noise
    cv::Mat blurred;
    GaussianBlur(gray, blurred, cv::Size(3, 3), 0);

    // 4. Sobel X and Sobel Y (signed 16-bit)
    cv::Mat gradX, gradY;
    Sobel(blurred, gradX, CV_16S, 1, 0, 3);
    Sobel(blurred, gradY, CV_16S, 0, 1, 3);

    // 5. Convert to float for magnitude calculation
    cv::Mat gradXf, gradYf;
    gradX.convertTo(gradXf, CV_32F);
    gradY.convertTo(gradYf, CV_32F);

    // 6. Compute true gradient magnitude
    cv::Mat mag;
    magnitude(gradXf, gradYf, mag);

    // 7. Convert to 8-bit for display
    cv::Mat sobel;
    mag.convertTo(sobel, CV_8U);

    // 8. Show result
    imshow("Sobel Magnitude", sobel);
    cv::waitKey(0);
    return 0;
}

/**
 * Draw bounding box with label
 * @param frame current frame
 * @param bbox
 * @param ok is tracking ok
 */
void Edger::draw_bb(cv::Mat &frame, const cv::Rect &bbox, const bool ok) {
    if (ok) {
        // draw green box
        cv::rectangle(frame, bbox, cv::Scalar(0, 255, 0), 2);

        // draw "Tracking" above the box
        cv::putText(frame, "Tracking",
                    cv::Point(bbox.x, bbox.y - 10),
                    cv::FONT_HERSHEY_SIMPLEX, 0.7,
                    cv::Scalar(0, 255, 0), 2);
    } else {
        // draw "Lost" above the last known box
        cv::putText(frame, "Lost",
                    cv::Point(bbox.x, bbox.y - 10),
                    cv::FONT_HERSHEY_SIMPLEX, 0.7,
                    cv::Scalar(0, 0, 255), 2);
    }
}

/**
 * Track object with tracker to track object within video
 */
void Edger::track_object(cv::Mat &img) {
//    auto tracker = cv::TrackerCSRT::create();
//    auto bbox = cv::selectROI("", img);
//    tracker->init(img, bbox);
}
