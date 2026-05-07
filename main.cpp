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
#include <QAudioOutput>
#include <QCheckBox>
#include <QWindow>
#include "Edger.hpp"

//#define DEBUG //uncomment or comment

#define GET_VID_POS ((static_cast<double>(media_player->position()))) ///Get video position

#define FORWARD_STEP (1000) ///How many milly to jump forward

#define BACKWARD_STEP (1000) ///How many milly to jump backward

QT_BEGIN_NAMESPACE

class Ui_MainWindow {
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *buttons;
    QPushButton *open_vid_btn;
    QPushButton *play_vid_btn;

    QPushButton *go_back_btn;
    QPushButton *go_forward_btn;

    QPushButton *detect_btn;
    QPushButton *track_btn;
    QPushButton *stop_btn;

    QCheckBox *is_need_audio;
    QFrame *frame;
    QVideoWidget *video_wid;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow) {
        if (MainWindow->objectName().isEmpty()) {
            MainWindow->setObjectName("MainWindow");
        }
        MainWindow->resize(970, 580);
        MainWindow->setFixedSize(970, 580); //do not resize window
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

        go_back_btn = new QPushButton(verticalLayoutWidget);
        go_back_btn->setObjectName("go_back_btn");
        go_back_btn->setStyleSheet("background-color: #ee82ee;"); //looks like pink
        buttons->addWidget(go_back_btn);

        go_forward_btn = new QPushButton(verticalLayoutWidget);
        go_forward_btn->setObjectName("go_forward_btn");
        go_forward_btn->setStyleSheet("background-color: #ee82ee;");
        buttons->addWidget(go_forward_btn);

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

        is_need_audio = new QCheckBox(verticalLayoutWidget);
        is_need_audio->setObjectName("is_need_audio");
        is_need_audio->setCheckState(Qt::CheckState::Checked);
        buttons->addWidget(is_need_audio);

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
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Edge detector", nullptr));
        open_vid_btn->setText(QCoreApplication::translate("MainWindow", "Open video", nullptr));
        play_vid_btn->setText(QCoreApplication::translate("MainWindow", "Play video", nullptr));
        go_back_btn->setText(QCoreApplication::translate("MainWindow", "Go back", nullptr));
        go_forward_btn->setText(QCoreApplication::translate("MainWindow", "Go forward", nullptr));
        detect_btn->setText(QCoreApplication::translate("MainWindow", "Detect edges", nullptr));
        track_btn->setText(QCoreApplication::translate("MainWindow", "Track object", nullptr));
        stop_btn->setText(QCoreApplication::translate("MainWindow", "Stop video", nullptr));
        is_need_audio->setText(QCoreApplication::translate("MainWindow", "Turn on/off audio?", nullptr));
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

    auto media_player = std::make_unique<QMediaPlayer>(); //video or dynamic media media_player
    auto audio_output = std::make_unique<QAudioOutput>();

    auto vid_wid = main_win->findChild<QVideoWidget *>("video_wid");
    auto open_vid = main_win->findChild<QPushButton *>("open_vid_btn");
    auto play_vid = main_win->findChild<QPushButton *>("play_vid_btn");

    auto go_back_vid = main_win->findChild<QPushButton *>("go_back_btn");
    auto go_forward_vid = main_win->findChild<QPushButton *>("go_forward_btn");

    auto detect_vid = main_win->findChild<QPushButton *>("detect_btn"); ///Detect edges in video
    auto track_vid = main_win->findChild<QPushButton *>("track_btn"); ///Track object in video
    auto stop_vid = main_win->findChild<QPushButton *>("stop_btn"); ///Stop video
    auto checkbox_aud = main_win->findChild<QCheckBox *>("is_need_audio"); ///Open setting window

    //Open video
    QPushButton::connect(open_vid, &QPushButton::clicked,
                         [&main_win, &media_player, &vid_wid, &video_capture, &audio_output] {

                             QString filename = QFileDialog::getOpenFileName(main_win.get(), "Choose File");

                             if (filename.endsWith("jpg") or filename.endsWith("png")) {
                                 QMessageBox(QMessageBox::Icon::Critical, "Error", "Photos are not supported").exec();
                                 return;
                             }
                             if (filename.isEmpty()) {
                                 QMessageBox(QMessageBox::Icon::Warning, "Warning", "Filename is empty").exec();
                                 return; //it can be an exception, but maybe memory leak
                             }
                             media_player->setSource(QUrl(filename));
                             video_capture = std::make_unique<cv::VideoCapture>(filename.toStdString());
                             if (media_player->source().isEmpty()) {
                                 QMessageBox(QMessageBox::Icon::Warning, "Warning",
                                             "An error occurred during video insert").exec();
                                 return;
                             }

                             media_player->setVideoOutput(vid_wid);
                             media_player->setAudioOutput(audio_output.get());
                             vid_wid->show();
                         });

    //Play video
    QPushButton::connect(play_vid, &QPushButton::clicked, [&media_player] {
        if (media_player->isPlaying()) {
            media_player->pause(); //unexpected feature
            return;
        }

        if (not media_player->hasVideo()) {
            QMessageBox(QMessageBox::Icon::Warning, "Warning", "Open video first").exec();
            return;
        }

        media_player->play();

        if (not media_player->isPlaying()) {
            QMessageBox(QMessageBox::Icon::Warning, "Warning", "An error occurred during playing video").exec();
            return;
        }
    });

    //Go back in video
    QPushButton::connect(go_back_vid, &QPushButton::clicked, [&media_player, &video_capture] {
        if (media_player->hasVideo()) {
            auto pos = GET_VID_POS;
            pos -= BACKWARD_STEP;

            media_player->setPosition(pos);
            video_capture->set(cv::CAP_PROP_POS_MSEC, pos);
            return;
        } else {
            QMessageBox(QMessageBox::Icon::Critical, "Error", "Video is not turned on").exec();
            return;
        }
    });

    //Go forward in video
    QPushButton::connect(go_forward_vid, &QPushButton::clicked, [&media_player, &video_capture] {
        if (media_player->hasVideo()) {
            auto pos = GET_VID_POS;
            pos += FORWARD_STEP;

            media_player->setPosition(pos);
            video_capture->set(cv::CAP_PROP_POS_MSEC, pos);
            return;
        } else {
            QMessageBox(QMessageBox::Icon::Critical, "Error", "Video is not turned on").exec();
            return;
        }
    });

    //Stop video
    QPushButton::connect(stop_vid, &QPushButton::clicked, [&media_player] {
        if (media_player->hasVideo()) {
            media_player->pause();
            if (media_player->isPlaying()) {
                QMessageBox(QMessageBox::Icon::Warning, "Warning", "Video is not stopped, error occurred").exec();
                return;
            }
        } else {
            QMessageBox(QMessageBox::Icon::Critical, "Error", "Video is not turned on").exec();
            return;
        }
    });

    //Detecting edges in video
    QPushButton::connect(detect_vid, &QPushButton::clicked, [&media_player, &video_capture] {
        if (not media_player->hasVideo()) {
            QMessageBox(QMessageBox::Icon::Critical, "Error", "Video is not turned on").exec();
            return;
        }

        media_player->pause(); //stop video when detect
        cv::Mat frame;
        video_capture->set(cv::CAP_PROP_POS_MSEC, GET_VID_POS);
        bool success = video_capture->read(frame);
        if (not success) {
            qDebug() << "Video has ended";
            return;
        }
        Edger::detect_edges(frame);
        return;
    });

    //Track video
    QPushButton::connect(track_vid, &QPushButton::clicked, [&media_player, &video_capture] {
        if (not media_player->hasVideo()) {
            QMessageBox(QMessageBox::Icon::Critical, "Error", "Video is not turned on").exec();
            return;
        }

        media_player->pause(); //stop main video when detect
        cv::Mat frame;
        video_capture->set(cv::CAP_PROP_POS_MSEC, GET_VID_POS);
        bool success = video_capture->read(frame);
        if (!success) {
            qDebug() << "Video has ended";
            return;
        }
        Edger::track_object<cv::TrackerCSRT>(video_capture.get(), frame);
        return;
    });

    //Audio settings
    QCheckBox::connect(checkbox_aud, &QCheckBox::clicked, [&checkbox_aud, &audio_output, &media_player] {
        if (media_player->hasVideo() or media_player->hasAudio()) {
            bool current_mute = checkbox_aud->isChecked();
            audio_output->setMuted(!current_mute);
            return;
        } else {
            QMessageBox(QMessageBox::Icon::Critical, "Error", "Video or audio is not turned on").exec();
            checkbox_aud->setChecked(false);
            return;
        }
    });

    if (main_win) {
        main_win->show();
    }

    return QApplication::exec();
}

#endif
