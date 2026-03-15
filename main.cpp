#include <string>

#include <QFile>
#include <QMainWindow>
#include <QApplication>
#include <QPushButton>
#include <QFileDialog>
#include <QtUiTools/QUiLoader>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QWindow>
#include <QMessageBox>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/tracking.hpp>

#ifdef WIN32
constexpr auto path_to_img =  "";
#elifdef linux
constexpr auto path_to_img = "/home/kirill/Downloads/Edge-detector/edge_detector.ui";
#else
#error("No specified OS")
#endif

import Libio;

namespace Img_detect {

    struct Cv_entity {
        std::string file_name;
    };

    /**
     * Detect edges with Sobel algo
     * @param img image to detect edges on
     * @return
     */
    int detect_edges_sobel(const cv::Mat &img) {
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
    void draw_bb(cv::Mat &frame, const cv::Rect &bbox, const bool ok) {
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
    void track_object() {
//        auto tracker = cv::TrackerCSRT::create();
    }

    /**
     * Can be used as a coroutine. Start main cycle of the opencv.
     * @param file_name name of the file to analyze
     */
    void opencv_cycle(const std::string &file_name) {
        cv::Mat img;
        while (true) {
            img = cv::imread(file_name, cv::COLOR_BGR2GRAY);
        }
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QUiLoader loader;
    if constexpr (1) {
        auto widgets = loader.availableWidgets();
        for (auto elem: widgets) {
            libio::output::println(elem);
        }
    }
    QFile file(path_to_img); //absolute path to file with ui
    auto res = file.open(QFile::ReadOnly);
    if (not res) {
        QMessageBox(QMessageBox::Icon::Critical, "Error", "An error occurred during loading UI file").exec();
    }
    file.close();

    QWidget *main_window = dynamic_cast<QMainWindow *>(loader.load(&file));
    auto player = std::make_unique<QMediaPlayer>(); //video or other media player
    auto vid_wid = main_window->findChild<QVideoWidget *>("video_wid");
    auto open_vid = main_window->findChild<QPushButton *>("open_vid_btn");
    auto play_vid = main_window->findChild<QPushButton *>("play_vid_btn");
    auto detect_vid = main_window->findChild<QPushButton *>("detect_btn");
    auto track_vid = main_window->findChild<QPushButton *>("track_btn");
    auto stop_vid = main_window->findChild<QPushButton *>("stop_btn");
    auto settings_vid = main_window->findChild<QPushButton *>("settings_btn");

    QPushButton::connect(open_vid, &QPushButton::clicked, [&main_window, &player, &vid_wid] {
        QString filename = QFileDialog::getOpenFileName(main_window, "Choose File");
        if (filename.isEmpty()) {
            return; //it can be an exception
        }
        player->setSource(QUrl(filename));
        player->setVideoOutput(vid_wid);

        if (not player->hasVideo()) {
            QMessageBox(QMessageBox::Icon::Warning, "Error", "An error occurred during video insert").exec();
        }
    });

    QPushButton::connect(play_vid, &QPushButton::clicked, [&player, &vid_wid] {
        player->play();
        vid_wid->show();
        if (not player->isPlaying()) {
            QMessageBox(QMessageBox::Icon::Warning, "Error", "An error occurred during playing video").exec();
        }
    });

    QPushButton::connect(stop_vid, &QPushButton::clicked, [&player] {
        player->stop();
        if (player->mediaStatus() != QMediaPlayer::StalledMedia) {
            QMessageBox(QMessageBox::Icon::Warning, "Error", "Video is not stopped").exec();
        }
    });

    QPushButton::connect(detect_vid, &QPushButton::clicked, [&player] {
//            Img_detect::detect_edges_sobel();
    });

    QPushButton::connect(track_vid, &QPushButton::clicked, [&player] {
//
    });

    QPushButton::connect(settings_vid, &QPushButton::clicked, [] {
        auto settings_page = new QWindow();
        sleep(1000);
        delete settings_page;
    });

    if (main_window) {
        main_window->show();
    }

    return QApplication::exec();
}