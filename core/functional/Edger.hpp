#ifndef EDGE_DETECTOR_EDGER_HPP
#define EDGE_DETECTOR_EDGER_HPP

#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/tracking.hpp>

class Edger {
private:
    static void draw_bb(cv::Mat &frame, const cv::Rect &bbox, bool ok);

public:
    Edger() = default;

    ~Edger() = default;

    template<typename T>
    static void track_object(cv::VideoCapture *video_cap, cv::Mat &init_frame);

    static int detect_edges(const cv::Mat &img);
};

/**
* Track object with tracker to track object within video
* @tparam T - tracker object
*/
template<typename T = cv::TrackerCSRT>
void Edger::track_object(cv::VideoCapture *video_cap, cv::Mat &init_frame) {
    cv::Ptr<T> tracker = T::create();
    auto bbox = cv::selectROI("Select frame to detect", init_frame);
    tracker->init(init_frame, bbox);
    cv::Mat tmp_frame;
    bool read_res;
    while ((read_res = video_cap->read(tmp_frame))) {

        //Start timer
        auto timer = (double) cv::getTickCount();

        //Update the tracking result
        bool ok = tracker->update(tmp_frame, bbox);

        //Calculate Frames per second (FPS)
        double fps = cv::getTickFrequency() / ((double) cv::getTickCount() - timer);

        if (!tmp_frame.empty()) {
            if (ok) {
                Edger::draw_bb(tmp_frame, bbox, true);
            } else {
                Edger::draw_bb(tmp_frame, bbox, false);
                break; //exit tracking if lost object
            }

            if (!read_res) {
                break;
            }
        } else {
            break;
        }
        cv::putText(tmp_frame, "FPS : " + std::to_string(fps), cv::Point(100, 50), cv::FONT_HERSHEY_SIMPLEX, 0.75,
                    cv::Scalar(50, 170, 50), 2);

        imshow("Current tracking frame", tmp_frame);
        int k = cv::waitKey(1);
        if (k == 27) {
            break;
        }
    }
}

#endif
