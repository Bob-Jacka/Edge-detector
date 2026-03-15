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

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#ifdef WIN32
constexpr auto path_to_img =  "";
#elifdef linux
constexpr auto path_to_img = "/home/kirill/Downloads/Edge-detector/edge_detector.ui";
#else
#error("No specified OS")
#endif

namespace {
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
     * Can be used as a coroutine. Start main cycle of the opencv.
     * @param file_name name of the file to analyze
     */
    void opencv_cycle(const std::string &file_name) {
        cv::Mat img;
        while (true) {
            img = cv::imread(file_name, cv::COLOR_BGR2GRAY);
        }
    }

    extern "C" {
    int main(int argc, char *argv[]) {
        QApplication a(argc, argv);

        QUiLoader loader;
        QFile file(path_to_img); //absolute path to file with ui
        auto res = file.open(QFile::ReadOnly);
        if (res) {
            //
        }
        file.close();

        QWidget *main_window = dynamic_cast<QMainWindow *>(loader.load(&file));
        auto player = std::make_unique<QMediaPlayer>(); //video or other media player
        auto vid_wid = main_window->findChild<QVideoWidget *>();
        auto open_vid = main_window->findChild<QPushButton *>();
        auto play_vid = main_window->findChild<QPushButton *>("Play video");
        auto detect_vid = main_window->findChild<QPushButton *>("Detect edges");
        auto stop_vid = main_window->findChild<QPushButton *>("Stop video");
        auto settings_vid = main_window->findChild<QPushButton *>("Settings");

        QPushButton::connect(open_vid, &QPushButton::clicked, [&main_window, &player, &vid_wid] {
            QString filename = QFileDialog::getExistingDirectory(main_window, "Choose File");
            if (filename.isEmpty()) {
                return; //it can be an exception
            }
            player->setSource(QUrl(filename));
            player->setVideoOutput(vid_wid);
        });

        QPushButton::connect(play_vid, &QPushButton::clicked, [&player] {
            player->play();
        });

        QPushButton::connect(stop_vid, &QPushButton::clicked, [&player] {
            player->stop();
        });

        QPushButton::connect(detect_vid, &QPushButton::clicked, [&player] {
//            detect_edges_sobel();
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
    }
}