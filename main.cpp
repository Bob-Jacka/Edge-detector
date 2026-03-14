#include <QFile>
#include <string>

#define DYNAMIC

#ifdef DYNAMIC

#include <QMainWindow>
#include <QApplication>
#include <QPushButton>
#include <QFileDialog>
#include <QtUiTools/QUiLoader>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QUiLoader loader;
    QFile file("/home/kirill/Downloads/Edge-detector/edge_detector.ui");
    auto res = file.open(QFile::ReadOnly);
    if (res) {
        //
    }

    QWidget *main_window = dynamic_cast<QMainWindow *>(loader.load(&file));
    auto open_vid = main_window->findChild<QPushButton *>();
    QPushButton::connect(open_vid, &QPushButton::clicked, [&main_window] {
        QString filename = QFileDialog::getExistingDirectory(main_window, "Choose File");
        if (filename.isEmpty()) {
            return;
        }
        QFile file(filename);
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            return;
        }
    });
    file.close();

    if (main_window) {
        main_window->show();
    }

    return QApplication::exec();
}

#elifndef DYNAMIC
#pragma message("Using static interface")
/********************************************************************************
** Form generated from reading UI file 'edge_detectorjhRqtD.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef EDGE_DETECTORJHRQTD_H
#define EDGE_DETECTORJHRQTD_H

#include <QtCore/QVariant>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QFileDialog>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include "main.moc"

import Libio;

QT_BEGIN_NAMESPACE

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

class Ui_MainWindow : QWidget {

Q_OBJECT

private:

    QMainWindow *main_window = nullptr;

    QWidget *centralwidget = nullptr;
    QWidget *verticalLayoutWidget = nullptr;

    QVBoxLayout *buttons = nullptr;
    QPushButton *open_vid = nullptr;
    QPushButton *play_vid_btn = nullptr;
    QPushButton *detect_btn = nullptr;
    QPushButton *stop_btn = nullptr;
    QPushButton *settings_btn = nullptr;

    QFrame *frame = nullptr;
    QVideoWidget *video_wid = nullptr; //add your video here
    QMenuBar *menubar = nullptr;
    QStatusBar *statusbar = nullptr;

private:

    void init_callbacks() {
        QObject::connect(open_vid, &QPushButton::clicked, [this] {
            QString dir = QFileDialog::getExistingDirectory(this, "Pick file", QDir::currentPath());
        });
    }

    void clear_ui() const {
        delete buttons;
        delete play_vid_btn;
        delete open_vid;
        delete detect_btn;
        delete stop_btn;
        delete settings_btn;
        delete video_wid;
        delete menubar;
        delete statusbar;
        delete verticalLayoutWidget;
        delete frame;
        delete centralwidget;
        delete main_window;
    }

    void setup_ui() {
        main_window = new QMainWindow();
        if (main_window->objectName().isEmpty()) {
            main_window->setObjectName("MainWindow");
        }
        main_window->resize(960, 580);
        centralwidget = new QWidget();
        centralwidget->setObjectName("centralwidget");
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(780, 19, 160, 227));
        buttons = new QVBoxLayout(verticalLayoutWidget);
        buttons->setSpacing(0);
        buttons->setObjectName("buttons");
        buttons->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        buttons->setContentsMargins(0, 0, 0, 0);

        open_vid = new QPushButton(verticalLayoutWidget);
        open_vid->setObjectName("open_vid");

        buttons->addWidget(open_vid);

        play_vid_btn = new QPushButton(verticalLayoutWidget);
        play_vid_btn->setObjectName("play_vid_btn");

        buttons->addWidget(play_vid_btn);

        detect_btn = new QPushButton(verticalLayoutWidget);
        detect_btn->setObjectName("detect_btn");

        buttons->addWidget(detect_btn);

        stop_btn = new QPushButton(verticalLayoutWidget);
        stop_btn->setObjectName("stop_btn");

        buttons->addWidget(stop_btn);

        settings_btn = new QPushButton(verticalLayoutWidget);
        settings_btn->setObjectName("settings_btn");

        buttons->addWidget(settings_btn);

        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(20, 20, 741, 471));
        frame->setFrameShape(QFrame::Shape::Box);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        frame->setLineWidth(5);
        frame->setMidLineWidth(0);
        video_wid = new QVideoWidget(frame);
        video_wid->setObjectName("widget");
        video_wid->setGeometry(QRect(10, 10, 721, 451));
        main_window->setCentralWidget(centralwidget);
        menubar = new QMenuBar(main_window);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 964, 22));
        main_window->setMenuBar(menubar);
        statusbar = new QStatusBar(main_window);
        statusbar->setObjectName("statusbar");
        main_window->setStatusBar(statusbar);

        retranslateUi(main_window);

        QMetaObject::connectSlotsByName(main_window);
        init_callbacks();
    } // setup_ui

    void retranslateUi(QMainWindow *MainWindow) const {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        play_vid_btn->setText(QCoreApplication::translate("MainWindow", "Play video", nullptr));
        detect_btn->setText(QCoreApplication::translate("MainWindow", "Detect edges", nullptr));
        stop_btn->setText(QCoreApplication::translate("MainWindow", "Stop video", nullptr));
        settings_btn->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
    } // retranslateUi

public:
    ~Ui_MainWindow() override {
        clear_ui();
    }

    Ui_MainWindow() {
        setup_ui();
    }
};

QT_END_NAMESPACE

#endif
#endif

#ifndef DYNAMIC
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto main_window = std::make_unique<Ui_MainWindow>();
    if constexpr (true) {
        //for test execution
        using namespace cv;
        libio::output::print("Enter video name to proceed: ");
        std::string video_name = libio::input::user_input();
        VideoCapture cap(video_name);
        if (!cap.isOpened()) {
            libio::output::println("Cannot open the video file.");
            // throw; //it can be an error
            return -1;
        }
        const double fps = cap.get(CAP_PROP_FPS);
        libio::output::println("Video frames per second: " + std::to_string(fps));
        while (true) {
            Mat frame;
            // Mat object is a basic image container. frame is an object of Mat.
            if (!cap.read(frame)) {
                libio::output::println("Cannot read the video file.");
                break;
            }
        }
    }
    return QApplication::exec();
}
#endif
