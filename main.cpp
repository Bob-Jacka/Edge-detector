/********************************************************************************
** Form generated from reading UI file 'edge_detectorgxFEOb.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef EDGE_DETECTORGXFEOB_H
#define EDGE_DETECTORGXFEOB_H

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
#include <QMediaPlayer>
#include <QMessageBox>
#include <QWindow>
#include "Edger.hpp"

QT_BEGIN_NAMESPACE

class Ui_MainWindow {
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *buttons;
    QPushButton *open_vid_btn;
    QPushButton *play_vid_btn;
    QPushButton *detect_btn;
    QPushButton *track_btn;
    QPushButton *stop_btn;
    QPushButton *settings_btn;
    QFrame *frame;
    QVideoWidget *video_wid;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow) {
        if (MainWindow->objectName().isEmpty()) {
            MainWindow->setObjectName("MainWindow");
        }
        MainWindow->resize(964, 578);
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

        open_vid_btn = new QPushButton(verticalLayoutWidget);
        open_vid_btn->setObjectName("open_vid_btn");
        buttons->addWidget(open_vid_btn);

        play_vid_btn = new QPushButton(verticalLayoutWidget);
        play_vid_btn->setObjectName("play_vid_btn");
        play_vid_btn->setStyleSheet("background-color: #bab86c;"); //looks like green
        buttons->addWidget(play_vid_btn);

        stop_btn = new QPushButton(verticalLayoutWidget);
        stop_btn->setObjectName("stop_btn");
        stop_btn->setStyleSheet("background-color: #c6a664;"); //looks like red
        buttons->addWidget(stop_btn);

        detect_btn = new QPushButton(verticalLayoutWidget);
        detect_btn->setObjectName("detect_btn");
        buttons->addWidget(detect_btn);

        track_btn = new QPushButton(verticalLayoutWidget);
        track_btn->setObjectName("track_btn");
        buttons->addWidget(track_btn);

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
        video_wid->setObjectName("video_wid");
        video_wid->setGeometry(QRect(10, 10, 721, 451));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 964, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow) const {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        open_vid_btn->setText(QCoreApplication::translate("MainWindow", "Open video", nullptr));
        play_vid_btn->setText(QCoreApplication::translate("MainWindow", "Play video", nullptr));
        detect_btn->setText(QCoreApplication::translate("MainWindow", "Detect edges", nullptr));
        track_btn->setText(QCoreApplication::translate("MainWindow", "Track object", nullptr));
        stop_btn->setText(QCoreApplication::translate("MainWindow", "Stop video", nullptr));
        settings_btn->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow : public Ui_MainWindow {
    };
} // namespace Ui

QT_END_NAMESPACE

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto window = std::make_unique<Ui::MainWindow>();
    auto main_win = std::make_unique<QMainWindow>();
    std::unique_ptr<cv::VideoCapture> video_capture;

    window->setupUi(main_win.get());

    auto player = std::make_unique<QMediaPlayer>(); //video or dynamic media player
    auto vid_wid = main_win->findChild<QVideoWidget *>("video_wid");
    auto open_vid = main_win->findChild<QPushButton *>("open_vid_btn");
    auto play_vid = main_win->findChild<QPushButton *>("play_vid_btn");
    auto detect_vid = main_win->findChild<QPushButton *>("detect_btn");
    auto track_vid = main_win->findChild<QPushButton *>("track_btn");
    auto stop_vid = main_win->findChild<QPushButton *>("stop_btn");
    auto settings_vid = main_win->findChild<QPushButton *>("settings_btn");

    QPushButton::connect(open_vid, &QPushButton::clicked, [&main_win, &player, &vid_wid, &video_capture] {
        QString filename = QFileDialog::getOpenFileName(main_win.get(), "Choose File");
        if (filename.isEmpty()) {
            return; //it can be an exception, but maybe memory leak
        }
        player->setSource(QUrl(filename));
        video_capture = std::make_unique<cv::VideoCapture>(filename.toStdString());
        if (player->source().isEmpty()) {
            QMessageBox(QMessageBox::Icon::Warning, "Error", "An error occurred during video insert").exec();
        }
        player->setVideoOutput(vid_wid);
    });

    QPushButton::connect(play_vid, &QPushButton::clicked, [&player, &vid_wid] {
        player->play();
        vid_wid->show();

        if (not player->hasVideo()) {
            QMessageBox(QMessageBox::Icon::Warning, "Warning", "Open video first").exec();
        }

        if (not player->isPlaying()) {
            QMessageBox(QMessageBox::Icon::Warning, "Warning", "An error occurred during playing video").exec();
        }
    });

    QPushButton::connect(stop_vid, &QPushButton::clicked, [&player] {
        player->stop();
        if (player->mediaStatus() != QMediaPlayer::StalledMedia) {
            QMessageBox(QMessageBox::Icon::Warning, "Error", "Video is not stopped").exec();
        }
    });

    QPushButton::connect(detect_vid, &QPushButton::clicked, [&video_capture] {
        cv::Mat frame;
        bool success = video_capture->read(frame);
        if (!success) {
            libio::output::println("Video has ended");
        }
        Edger::detect_edges_sobel(frame);
    });

    QPushButton::connect(track_vid, &QPushButton::clicked, [&video_capture] {
        cv::Mat frame;
        bool success = video_capture->read(frame);
        if (!success) {
            libio::output::println("Video has ended");
        }
        Edger::track_object(frame);
    });

    QPushButton::connect(settings_vid, &QPushButton::clicked, [] {
        auto settings_page = new QWindow();
        sleep(1000);
        delete settings_page;
    });

    if (main_win) {
        main_win->show();
    }

    return QApplication::exec();
}

#endif
