#ifndef EDGE_DETECTOR_EDGER_HPP
#define EDGE_DETECTOR_EDGER_HPP

#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/tracking.hpp>

import Libio;

class Edger {
public:
    static void track_object(cv::Mat& img);

    static void draw_bb(cv::Mat &frame, const cv::Rect &bbox, bool ok);

    static int detect_edges_sobel(const cv::Mat &img);
};


#endif //EDGE_DETECTOR_EDGER_HPP
