#include <QFile>
#include <QtUiTools/QUiLoader>


#ifdef DYNAMIC
#include <QMainWindow>
#include <QApplication>

#error("Need to change invocation")

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QUiLoader loader;
    QFile     file("edge_detector.ui");
    file.open(QFile::ReadOnly);
    QWidget *main_window = dynamic_cast<QMainWindow *>(loader.load(&file));
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


// #include "cmake-build-debug/_deps/opencv-src/"
// #include "cmake-build-debug/_deps/opencv-src/modules/core/include/opencv2/core/mat.hpp"
// #include "cmake-build-debug/_deps/opencv-src/modules/videoio/include/opencv2/videoio.hpp"
// #include "cmake-build-debug/_deps/opencv-src/modules/videoio/include/opencv2/videoio/legacy/constants_c.h"

import Libio;

QT_BEGIN_NAMESPACE

class Ui_MainWindow {
    protected:
        ~Ui_MainWindow();

        Ui_MainWindow();

    protected:
        QWidget *     centralwidget        = nullptr;
        QWidget *     verticalLayoutWidget = nullptr;
        QVBoxLayout * buttons              = nullptr;
        QPushButton * play_vid_btn         = nullptr;
        QPushButton * detect_btn           = nullptr;
        QPushButton * stop_btn             = nullptr;
        QPushButton * settings_btn         = nullptr;
        QFrame *      frame                = nullptr;
        QVideoWidget *video_wid            = nullptr; //add your video here
        QMenuBar *    menubar              = nullptr;
        QStatusBar *  statusbar            = nullptr;

    private:
        void clear_ui() const {
            delete buttons;
            delete play_vid_btn;
            delete detect_btn;
            delete stop_btn;
            delete settings_btn;
            delete video_wid;
            delete menubar;
            delete statusbar;
            delete verticalLayoutWidget;
            delete frame;
            delete centralwidget;
        }

        void setup_ui(QMainWindow *MainWindow) {
            if (MainWindow->objectName().isEmpty()) {
                MainWindow->setObjectName("MainWindow");
            }
            MainWindow->resize(960, 580);
            centralwidget = new QWidget(MainWindow);
            centralwidget->setObjectName("centralwidget");
            verticalLayoutWidget = new QWidget(centralwidget);
            verticalLayoutWidget->setObjectName("verticalLayoutWidget");
            verticalLayoutWidget->setGeometry(QRect(780, 19, 160, 227));
            buttons = new QVBoxLayout(verticalLayoutWidget);
            buttons->setSpacing(0);
            buttons->setObjectName("buttons");
            buttons->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
            buttons->setContentsMargins(0, 0, 0, 0);
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
            MainWindow->setCentralWidget(centralwidget);
            menubar = new QMenuBar(MainWindow);
            menubar->setObjectName("menubar");
            menubar->setGeometry(QRect(0, 0, 964, 22));
            MainWindow->setMenuBar(menubar);
            statusbar = new QStatusBar(MainWindow);
            statusbar->setObjectName("statusbar");
            MainWindow->setStatusBar(statusbar);

            retranslateUi(MainWindow);

            QMetaObject::connectSlotsByName(MainWindow);
        } // setup_ui

        void retranslateUi(QMainWindow *MainWindow) const {
            MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
            play_vid_btn->setText(QCoreApplication::translate("MainWindow", "Play video", nullptr));
            detect_btn->setText(QCoreApplication::translate("MainWindow", "Detect edges", nullptr));
            stop_btn->setText(QCoreApplication::translate("MainWindow", "Stop video", nullptr));
            settings_btn->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        } // retranslateUi
};

namespace Ui {
    class MainWindow : public Ui_MainWindow {
        MainWindow();

        static MainWindow *instance;

        public:
            ~MainWindow();

            static MainWindow *get_instance();
    };
} // namespace Ui

//Realization:
Ui_MainWindow::Ui_MainWindow() {
    setup_ui(new QMainWindow());
}

Ui_MainWindow::~Ui_MainWindow() {
    clear_ui();
}

Ui::MainWindow::MainWindow() : Ui_MainWindow() {
}

Ui::MainWindow::~MainWindow() {
    delete instance;
}

Ui::MainWindow *Ui::MainWindow::get_instance() {
    if (instance == nullptr) {
        instance = new Ui::MainWindow();
    }
    return instance;
}

QT_END_NAMESPACE

#endif // EDGE_DETECTORJHRQTD_H
#endif

int main() {
    auto main_window = Ui::MainWindow::get_instance();
    if constexpr (true) {
        //for test execution
        using namespace cv;
        libio::output::print("Enter video name to proceed: ");
        std::string  video_name = libio::input::user_input();
        VideoCapture cap(video_name);
        if (!cap.isOpened()) {
            libio::output::println("Cannot open the video file.");
            // throw; //it can be an error
            return -1;
        }
        const double fps = cap.get(CV_CAP_PROP_FPS);
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
}
