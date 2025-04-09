#include "stdafx.h"

#include"rqw_CameraObjectThread.hpp"
#include"rqw_CameraObject.hpp"
#include"hoec_CameraException.hpp"

#include "ButtonScanner.h"
#include"DlgProductSet.h"
#include"DlgProduceLineSet.h"
#include"GlobalStruct.h"
#include"NumKeyBord.h"

#include<qdebug>
#include<QtConcurrent>
#include <future>
#include<QDir>
#include<QFileInfo>

void ButtonScanner::updateExposureTimeTrigger()
{
    // 获取窗口的当前宽度和高度
    auto windowWidth = ui->gBoix_ImageDisplay->width();
    auto windowHeight = ui->gBoix_ImageDisplay->height();

    // 计算目标区域的宽度和高度
    int targetWidth = static_cast<int>(windowWidth * exposureTimeTriggerWidthRatio);
    int targetHeight = static_cast<int>(windowHeight * exposureTimeTriggerRatio);

    // 计算目标区域的左上角位置，使其居中
    int targetX = (windowWidth - targetWidth) / 2;
    int targetY = (windowHeight - targetHeight) / 2;

    // 更新 targetArea
    exposureTimeTriggerArea = QRect(targetX, targetY, targetWidth, targetHeight);

}

void ButtonScanner::onExposureTimeTriggerAreaClicked()
{
    auto isRuning = ui->rbtn_removeFunc->isChecked();
    if (!isRuning) {
        dlgExposureTimeSet->SetCamera(); // 设置相机为实时采集
        dlgExposureTimeSet->exec(); // 显示对话框
        dlgExposureTimeSet->ResetCamera(); // 重置相机为硬件触发
    }
}

void ButtonScanner::mousePressEvent(QMouseEvent* event)
{
    updateExposureTimeTrigger();
    auto point = event->pos();
    // 检查鼠标点击是否在 targetArea 内
    if (exposureTimeTriggerArea.contains(event->pos())) {
        onExposureTimeTriggerAreaClicked(); // 调用目标函数
    }

    QMainWindow::mousePressEvent(event);
}

void ButtonScanner::resizeEvent(QResizeEvent* event)
{
    // 当窗口大小发生变化时，更新 targetArea
    updateExposureTimeTrigger();
    QMainWindow::resizeEvent(event);
}

ButtonScanner::ButtonScanner(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ButtonScannerClass())
{
    ui->setupUi(this);
    mark_Thread = true;
    read_config();

    build_ui();
    build_connect();

    build_motion();

    build_camera();

    build_imageProcessorModule();

    //监视相机运动控制卡线程
    build_monitoringThread();

    build_ioThread();

    start_monitor();

    build_locationThread();
}

ButtonScanner::~ButtonScanner()
{
    mark_Thread = false;
    delete ui;
    auto& globalStruct = GlobalStruct::getInstance();
    globalStruct.destroyCamera();
    globalStruct.destroyImageProcessingModule();
    globalStruct.saveConfig();
}

void ButtonScanner::set_radioButton()
{
    ui->rbtn_debug->setAutoExclusive(false);
    ui->rbtn_defect->setAutoExclusive(false);
    ui->rbtn_downLight->setAutoExclusive(false);
    ui->rbtn_ForAndAgainst->setAutoExclusive(false);
    ui->rbtn_removeFunc->setAutoExclusive(false);
    ui->rbtn_sideLight->setAutoExclusive(false);
    ui->rbtn_takePicture->setAutoExclusive(false);
    ui->rbtn_upLight->setAutoExclusive(false);

    ui->rbtn_removeFunc->setAttribute(Qt::WA_TransparentForMouseEvents, true); // 禁止鼠标事件
    ui->rbtn_removeFunc->setFocusPolicy(Qt::NoFocus); // 禁止键盘焦点
}

void ButtonScanner::build_ui()
{
    //Set RadioButton ,make sure these can be checked at the same time
    set_radioButton();
    build_mainWindowData();
    build_dlgProduceLineSet();
    build_dlgProductSet();
    build_dlgExposureTimeSet();
}

void ButtonScanner::build_mainWindowData()
{
    auto& globalStruct = GlobalStruct::getInstance();
    auto& mainWindowConfig = globalStruct.mainWindowConfig;
    ui->label_produceTotalValue->setText(QString::number(mainWindowConfig.totalProduction));
    ui->label_wasteProductsValue->setText(QString::number(mainWindowConfig.totalWaste));
    ui->label_productionYieldValue->setText(QString::number(mainWindowConfig.passRate) + QString(" %"));
    ui->rbtn_debug->setChecked(mainWindowConfig.isDebugMode);
    ui->rbtn_takePicture->setChecked(mainWindowConfig.isTakePictures);
    ui->rbtn_removeFunc->setChecked(mainWindowConfig.isEliminating);
    ui->label_removeRate->setText(QString::number(mainWindowConfig.scrappingRate) + QString(" /min"));
    ui->rbtn_upLight->setChecked(mainWindowConfig.upLight);
    ui->rbtn_downLight->setChecked(mainWindowConfig.downLight);
    ui->rbtn_sideLight->setChecked(mainWindowConfig.sideLight);
    ui->rbtn_defect->setChecked(mainWindowConfig.isDefect);
    ui->rbtn_ForAndAgainst->setChecked(mainWindowConfig.isPositive);
}

void ButtonScanner::build_dlgProduceLineSet()
{
    this->dlgProduceLineSet = new DlgProduceLineSet(this);
}

void ButtonScanner::build_dlgProductSet()
{
    this->dlgProductSet = new DlgProductSet(this);
}

void ButtonScanner::build_dlgExposureTimeSet()
{
    this->dlgExposureTimeSet = new DlgExposureTimeSet(this);
    //设置对话框的初始位置
    int x = this->x() + (this->width() - dlgExposureTimeSet->width()) / 2;
    int y = this->y() + (this->height() - dlgExposureTimeSet->height()) / 2;
    dlgExposureTimeSet->move(x, y);
}

void ButtonScanner::build_connect()
{
    QObject::connect(ui->pbtn_exit, &QPushButton::clicked, 
        this, &ButtonScanner::pbtn_exit_clicked);

    QObject::connect(ui->pbtn_set, &QPushButton::clicked, 
        this, &ButtonScanner::pbtn_set_clicked);

    QObject::connect(ui->pbtn_newProduction, &QPushButton::clicked,
        this, &ButtonScanner::pbtn_newProduction_clicked);

    QObject::connect(ui->pbtn_lightValue, &QPushButton::clicked, 
        this, &ButtonScanner::pbtn_lightValue_clicked);

    QObject::connect(ui->pbtn_score,&QPushButton::clicked,
        this,&ButtonScanner::pbtn_score_clicked);

    QObject::connect(ui->rbtn_debug, &QPushButton::clicked, 
        this, &ButtonScanner::rbtn_debug_ckecked);

    QObject::connect(ui->rbtn_takePicture, &QPushButton::clicked, 
        this, &ButtonScanner::rbtn_takePicture_ckecked);

    QObject::connect(ui->rbtn_removeFunc, &QPushButton::clicked,
        this, &ButtonScanner::rbtn_removeFunc_ckecked);

    QObject::connect(ui->rbtn_upLight, &QPushButton::clicked, 
        this, &ButtonScanner::rbtn_upLight_ckecked);

    QObject::connect(ui->rbtn_sideLight, &QPushButton::clicked,
        this, &ButtonScanner::rbtn_sideLight_ckecked);

    QObject::connect(ui->rbtn_downLight, &QPushButton::clicked, 
        this, &ButtonScanner::rbtn_downLight_ckecked);

    QObject::connect(ui->rbtn_defect, &QPushButton::clicked, 
        this, &ButtonScanner::rbtn_defect_ckecked);

    QObject::connect(ui->rbtn_ForAndAgainst, &QPushButton::clicked, 
        this, &ButtonScanner::rbtn_ForAndAgainst_ckecked);
}

void ButtonScanner::read_config()
{
    auto& globalStruct = GlobalStruct::getInstance();
    globalStruct.buildConfigManager(rw::oso::StorageType::Xml);

    read_config_mainWindowConfig();
    read_config_productSetConfig();
    read_config_produceLineConfig();
    read_config_exposureTimeSetConfig();
}

void ButtonScanner::read_config_mainWindowConfig()
{
    auto& globalStruct = GlobalStruct::getInstance();

    QString mainWindowFilePath = R"(config/mainWindowConfig.xml)";
    QDir dir;
    QString mainWindowFilePathFull = dir.absoluteFilePath(mainWindowFilePath);
    QFileInfo mainWindowFile(mainWindowFilePathFull);

    globalStruct.mainWindowFilePath = mainWindowFilePathFull;

    if (!mainWindowFile.exists()) {
        QDir configDir = QFileInfo(mainWindowFilePathFull).absoluteDir();
        if (!configDir.exists()) {
            configDir.mkpath(".");
        }
        QFile file(mainWindowFilePathFull);
        if (file.open(QIODevice::WriteOnly)) {
            file.close();
        }
        else {
            QMessageBox::critical(this, "Error", "无法创建配置文件mainWindowConfig.xml");
        }
        globalStruct.mainWindowConfig = rw::cdm::ButtonScannerMainWindow();
        globalStruct.saveMainWindowConfig();
        return;
    }
    else {
        globalStruct.ReadMainWindowConfig();
    }
}

void ButtonScanner::read_config_produceLineConfig()
{
    auto& globalStruct = GlobalStruct::getInstance();
    QDir dir;

    QString dlgProduceLineSetFilePath = R"(config/dlgProduceLineSetConfig.xml)";
    QString dlgProduceLineSetFilePathFull = dir.absoluteFilePath(dlgProduceLineSetFilePath);
    QFileInfo dlgProduceLineSetFile(dlgProduceLineSetFilePathFull);

    globalStruct.dlgProduceLineSetFilePath = dlgProduceLineSetFilePathFull;

    if (!dlgProduceLineSetFile.exists()) {
        QDir configDir = QFileInfo(dlgProduceLineSetFilePathFull).absoluteDir();
        if (!configDir.exists()) {
            configDir.mkpath(".");
        }
        QFile file(dlgProduceLineSetFilePathFull);
        if (file.open(QIODevice::WriteOnly)) {
            file.close();
        }
        else {
            QMessageBox::critical(this, "Error", "无法创建配置文件dlgProduceLineSetConfig.xml");
        }
        globalStruct.dlgProduceLineSetConfig = rw::cdm::ButtonScannerProduceLineSet();
        globalStruct.saveDlgProduceLineSetConfig();
        return;
    }
    else {
        globalStruct.ReadDlgProduceLineSetConfig();
    }
}

void ButtonScanner::read_config_productSetConfig()
{
    auto& globalStruct = GlobalStruct::getInstance();
    QDir dir;

    QString dlgProductSetFilePath = R"(config/dlgProdutSetConfig.xml)";
    QString dlgProductSetFilePathFull = dir.absoluteFilePath(dlgProductSetFilePath);
    QFileInfo dlgProductSetFile(dlgProductSetFilePathFull);

    globalStruct.dlgProductSetFilePath = dlgProductSetFilePathFull;

    if (!dlgProductSetFile.exists()) {
        QDir configDir = QFileInfo(dlgProductSetFilePathFull).absoluteDir();
        if (!configDir.exists()) {
            configDir.mkpath(".");
        }
        QFile file(dlgProductSetFilePathFull);
        if (file.open(QIODevice::WriteOnly)) {
            file.close();
        }
        else {
            QMessageBox::critical(this, "Error", "无法创建配置文件dlgProdutSetConfig.xml");
        }
        globalStruct.dlgProductSetConfig = rw::cdm::ButtonScannerDlgProductSet();
        globalStruct.saveDlgProductSetConfig();
        return;
    }
    else {
        globalStruct.ReadDlgProductSetConfig();
    }
}

void ButtonScanner::read_config_exposureTimeSetConfig()
{
    auto& globalStruct = GlobalStruct::getInstance();
    QDir dir;

    QString exposureTimeSetConfigFilePath = R"(config/exposureTimeSetConfig.xml)";
    QString exposureTimeSetConfigFilePathFull = dir.absoluteFilePath(exposureTimeSetConfigFilePath);
    QFileInfo dlgProductSetFile(exposureTimeSetConfigFilePathFull);

    globalStruct.dlgExposureTimeSetFilePath = exposureTimeSetConfigFilePathFull;

    if (!dlgProductSetFile.exists()) {
        QDir configDir = QFileInfo(exposureTimeSetConfigFilePathFull).absoluteDir();
        if (!configDir.exists()) {
            configDir.mkpath(".");
        }
        QFile file(exposureTimeSetConfigFilePathFull);
        if (file.open(QIODevice::WriteOnly)) {
            file.close();
        }
        else {
            QMessageBox::critical(this, "Error", "无法创建配置文件exposureTimeSetConfig.xml");
        }
        globalStruct.dlgExposureTimeSetConfig = rw::cdm::ButtonScannerDlgExposureTimeSet();
        globalStruct.saveDlgExposureTimeSetConfig();
        return;
    }
    else {
        globalStruct.ReadDlgExposureTimeSetConfig();
    }
}

void ButtonScanner::build_camera()
{
    auto& globalStruct = GlobalStruct::getInstance();
    globalStruct.cameraIp1 = "11";
    globalStruct.cameraIp2 = "12";
    globalStruct.cameraIp3 = "13";
    globalStruct.cameraIp4 = "14";

    globalStruct.buildCamera();
}

void ButtonScanner::build_imageProcessorModule()
{
    auto& globalStruct = GlobalStruct::getInstance();

    //
    QString enginePath = R"(model/model.engine)";
    QString namePath = R"(model/index.names)";
    QDir dir;

    QString enginePathFull = dir.absoluteFilePath(enginePath);
    QString namePathFull = dir.absoluteFilePath(namePath);

    QFileInfo engineFile(enginePathFull);
    QFileInfo nameFile(namePathFull);

    if (!engineFile.exists() || !nameFile.exists()) {
        QMessageBox::critical(this, "Error", "Engine file or Name file does not exist. The application will now exit.");
        QApplication::quit();
        return;
    }

    //TODO：使用对话框提示用户

    globalStruct.enginePath = enginePathFull;
    globalStruct.namePath = namePathFull;

    globalStruct.buildImageProcessingModule(2);

    ////连接界面显示和图像处理模块
    QObject::connect(globalStruct.imageProcessingModule1.get(), &ImageProcessingModule::imageReady,
        this, &ButtonScanner::onCamera1Display, Qt::DirectConnection);
    QObject::connect(globalStruct.imageProcessingModule2.get(), &ImageProcessingModule::imageReady,
        this, &ButtonScanner::onCamera2Display, Qt::DirectConnection);
    QObject::connect(globalStruct.imageProcessingModule3.get(), &ImageProcessingModule::imageReady,
        this, &ButtonScanner::onCamera3Display, Qt::DirectConnection);
    QObject::connect(globalStruct.imageProcessingModule4.get(), &ImageProcessingModule::imageReady,
        this, &ButtonScanner::onCamera4Display, Qt::DirectConnection);
}

void ButtonScanner::start_monitor()
{
    auto& globalStruct = GlobalStruct::getInstance();
    globalStruct.startMonitor();
}

void ButtonScanner::build_motion()
{
    auto& globalStruct = GlobalStruct::getInstance();

    //获取Zmotion
    auto& motionPtr = zwy::scc::GlobalMotion::getInstance().motionPtr;

    //下面通过motionPtr进行操作
    bool state = motionPtr.get()->OpenBoard((char*)"192.168.0.11");

    if (state) {
        motionPtr->SetLocationZero(0);
        motionPtr->SetLocationZero(1);
        motionPtr->SetLocationZero(2);
        motionPtr->SetAxisType(1, 3);
        motionPtr->SetAxisType(2, 3);
        motionPtr->SetAxisPulse(1, globalStruct.dlgProduceLineSetConfig.codeWheel);
        motionPtr->SetAxisPulse(2, globalStruct.dlgProduceLineSetConfig.codeWheel);
    }
}

void ButtonScanner::build_monitoringThread()
{
    //线程内部
    QFuture<void>  m_monitorFuture = QtConcurrent::run([this]() {
        while (mark_Thread)
        {
            //运动控制卡实时状态
            {
                //这里获取全局变量
                auto& globalStruct = GlobalStruct::getInstance();

                //获取Zmotion
                auto& motionPtr = zwy::scc::GlobalMotion::getInstance().motionPtr;

                bool  boardState = motionPtr.get()->getBoardState();
                if (boardState == false)
                {
                    motionPtr.get()->OpenBoard((char*)"192.168.0.11");
                }
                else
                {
                }
            }
            //获得相机链接状态
            {
                auto& globalStruct = GlobalStruct::getInstance();

                if (globalStruct.camera1) {
                    if (globalStruct.camera1->getConnectState()) {
                        QMetaObject::invokeMethod(qApp, [this]
                            {
                                ui->label_camera1State->setText("连接成功");
                                ui->label_camera1State->setStyleSheet(QString("QLabel{color:rgb(0, 230, 0);} "));
                            });
                    }
                    else {
                        QMetaObject::invokeMethod(qApp, [this]
                            {
                                ui->label_camera1State->setText("连接失败");
                                ui->label_camera1State->setStyleSheet(QString("QLabel{color:rgb(230, 0, 0);} "));
                            });
                    }
                }

                if (globalStruct.camera2) {
                    if (globalStruct.camera2->getConnectState()) {
                        QMetaObject::invokeMethod(qApp, [this]
                            {
                                ui->label_camera2State->setText("连接成功");
                                ui->label_camera2State->setStyleSheet(QString("QLabel{color:rgb(0, 230, 0);} "));
                            });
                    }
                    else {
                        QMetaObject::invokeMethod(qApp, [this]
                            {
                                ui->label_camera2State->setText("连接失败");
                                ui->label_camera2State->setStyleSheet(QString("QLabel{color:rgb(230, 0, 0);} "));
                            });
                    }
                }

                if (globalStruct.camera3) {
                    if (globalStruct.camera3->getConnectState()) {
                        QMetaObject::invokeMethod(qApp, [this]
                            {
                                ui->label_camera3State->setText("连接成功");
                                ui->label_camera3State->setStyleSheet(QString("QLabel{color:rgb(0, 230, 0);} "));
                            });
                    }
                    else {
                        QMetaObject::invokeMethod(qApp, [this]
                            {
                                ui->label_camera3State->setText("连接失败");
                                ui->label_camera3State->setStyleSheet(QString("QLabel{color:rgb(230, 0, 0);} "));
                            });
                    }
                }

                if (globalStruct.camera4) {
                    if (globalStruct.camera4->getConnectState()) {
                        QMetaObject::invokeMethod(qApp, [this]
                            {
                                ui->label_camera4State->setText("连接成功");
                                ui->label_camera4State->setStyleSheet(QString("QLabel{color:rgb(0, 230, 0);} "));
                            });
                    }
                    else {
                        QMetaObject::invokeMethod(qApp, [this]
                            {
                                ui->label_camera4State->setText("连接失败");
                                ui->label_camera4State->setStyleSheet(QString("QLabel{color:rgb(230, 0, 0);} "));
                            });
                    }
                }
            }

            QThread::msleep(500);
        }
        });
}

void ButtonScanner::build_locationThread()
{
    //线程内部
    QFuture<void>  m_monitorFuture = QtConcurrent::run([this]() {
        while (mark_Thread)
        {
            //获得位置数据

            //1,3相机
            float lacation1 = 0;
            //2，4相机
            float lacation2 = 0;
            //获取两个位置
            zwy::scc::GlobalMotion::getInstance().motionPtr.get()->GetAxisLocation(2, lacation1);
            zwy::scc::GlobalMotion::getInstance().motionPtr.get()->GetAxisLocation(1, lacation2);

            {
                auto& work1 = GlobalStruct::getInstance().productPriorityQueue1;

                int i = work1.size();

                double tifeishijian1 = GlobalStruct::getInstance().dlgProduceLineSetConfig.blowTime1;
                double tifeijuli1 = GlobalStruct::getInstance().dlgProduceLineSetConfig.blowDistance1;

                double nowlocation = work1.peek();

                if (nowlocation != 0 && (abs(lacation1 - nowlocation) > tifeijuli1))
                {
                    work1.top();

                    //吹气
                    zwy::scc::GlobalMotion::getInstance().motionPtr.get()->SetIOOut(5, 5, true, tifeishijian1);
                }
            }
            {
                auto& work2 = GlobalStruct::getInstance().productPriorityQueue2;

                double tifeishijian2 = GlobalStruct::getInstance().dlgProduceLineSetConfig.blowTime2;
                double tifeijuli2 = GlobalStruct::getInstance().dlgProduceLineSetConfig.blowDistance2;

                double nowlocation = work2.peek();
                if (nowlocation != 0 && (abs(lacation2 - nowlocation) > tifeijuli2))
                {
                    work2.top();

                    //吹气
                    zwy::scc::GlobalMotion::getInstance().motionPtr.get()->SetIOOut(1, 4, true, tifeishijian2);
                }
            }

            {
                auto& work3 = GlobalStruct::getInstance().productPriorityQueue3;

                double tifeishijian3 = GlobalStruct::getInstance().dlgProduceLineSetConfig.blowTime3;
                double tifeijuli3 = GlobalStruct::getInstance().dlgProduceLineSetConfig.blowDistance3;

                double nowlocation = work3.peek();
                if (nowlocation != 0 && abs(lacation1 - nowlocation) > tifeijuli3)
                {
                    work3.top();

                    //吹气
                    zwy::scc::GlobalMotion::getInstance().motionPtr.get()->SetIOOut(2, 3, true, tifeishijian3);
                }
            }

            {
                auto& work4 = GlobalStruct::getInstance().productPriorityQueue4;

                double tifeishijian4 = GlobalStruct::getInstance().dlgProduceLineSetConfig.blowTime4;
                double tifeijuli4 = GlobalStruct::getInstance().dlgProduceLineSetConfig.blowDistance4;

                double nowlocation = work4.peek();
                if (nowlocation != 0 && abs(lacation2 - nowlocation) > tifeijuli4)
                {
                    work4.top();

                    //吹气
                    zwy::scc::GlobalMotion::getInstance().motionPtr.get()->SetIOOut(3, 2, true, tifeishijian4);
                }
            }
        }
        });
}

void ButtonScanner::build_ioThread()
{
    //线程内部
    QtConcurrent::run([this]() {
        auto& globalStruct = GlobalStruct::getInstance();
        //获取Zmotion
        auto& motionPtr = zwy::scc::GlobalMotion::getInstance().motionPtr;

        while (mark_Thread)
        {
            bool state = false;
            state = motionPtr->GetIOIn(2);
            //急停

            if (state == true)
            {
                // pidaimove->stop();
                motionPtr->StopAllAxis();
                motionPtr->SetIOOut(1, false);

                motionPtr->SetIOOut(7, false);
            }
            else
            {
                //开始按钮
                bool state = false;
                state = motionPtr->GetIOIn(1);
                //启动程序
                if (state == true)
                {
                    //所有电机上电
                    QtConcurrent::run([this, &motionPtr]() {
                        QThread::msleep(500);
                        motionPtr->SetIOOut(1, true);
                        //启动电机
                        motionPtr->SetAxisType(0, 1);
                        double unit = GlobalStruct::getInstance().dlgProduceLineSetConfig.pulseFactor;
                        motionPtr->SetAxisPulse(0, unit);
                        double acc = GlobalStruct::getInstance().dlgProduceLineSetConfig.accelerationAndDeceleration;
                        motionPtr->SetAxisAcc(0, acc);
                        motionPtr->SetAxisDec(0, acc);
                        double speed = GlobalStruct::getInstance().dlgProduceLineSetConfig.motorSpeed;
                        motionPtr->SetAxisRunSpeed(0, speed);
                        // pidaimove->start(100);
                        motionPtr->AxisRun(0, -1);
                        motionPtr->SetIOOut(7, true);
                        });
                }
                //停止点
                state = motionPtr->GetIOIn(2);
                if (state)
                {
                    motionPtr->StopAllAxis();
                    motionPtr->SetIOOut(1, false);
                    motionPtr->SetIOOut(7, false);
                }

                //获取气压表数据
                auto qiya = motionPtr->GetIOIn(7);
                if (qiya == true) {
                    //气压正常
                    motionPtr->SetIOOut(8, true);
                }
                else {
                    motionPtr->SetIOOut(8, false);
                }

                if (globalStruct.mainWindowConfig.upLight) {
                    motionPtr->SetIOOut(9, true);
                }
                else {
                    motionPtr->SetIOOut(9, false);
                }

                if (globalStruct.mainWindowConfig.downLight) {
                    motionPtr->SetIOOut(10, true);
                }
                else {
                    motionPtr->SetIOOut(10, false);
                }

                if (globalStruct.mainWindowConfig.sideLight) {
                    motionPtr->SetIOOut(0, true);
                }
                else {
                    motionPtr->SetIOOut(0, false);
                }
            }

            QThread::msleep(100);
        }
        });
}

QImage ButtonScanner::cvMatToQImage(const cv::Mat& mat)
{
    if (mat.type() == CV_8UC1) {
        return QImage(mat.data, mat.cols, mat.rows, mat.step[0], QImage::Format_Grayscale8);
    }
    else if (mat.type() == CV_8UC3) {
        return QImage(mat.data, mat.cols, mat.rows, mat.step[0], QImage::Format_RGB888).rgbSwapped();
    }
    else if (mat.type() == CV_8UC4) {
        return QImage(mat.data, mat.cols, mat.rows, mat.step[0], QImage::Format_RGBA8888);
    }
    else {
        return QImage();
    }
}

void ButtonScanner::onCamera1Display(QImage image)
{
    QPixmap pixmap = QPixmap::fromImage(image);
    ui->label_imgDisplay->setPixmap(pixmap.scaled(ui->label_imgDisplay->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ButtonScanner::onCamera2Display(QImage image)
{
    QPixmap pixmap = QPixmap::fromImage(image);
    ui->label_imgDisplay_2->setPixmap(pixmap.scaled(ui->label_imgDisplay_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ButtonScanner::onCamera3Display(QImage image)
{
    QPixmap pixmap = QPixmap::fromImage(image);
    ui->label_imgDisplay_3->setPixmap(pixmap.scaled(ui->label_imgDisplay_3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ButtonScanner::onCamera4Display(QImage image)
{
    QPixmap pixmap = QPixmap::fromImage(image);
    ui->label_imgDisplay_4->setPixmap(pixmap.scaled(ui->label_imgDisplay_4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ButtonScanner::pbtn_set_clicked()
{
    auto passwordValue = new QPushButton(this);
    auto passwordDlg = new NumKeyBord(this, passwordValue, 2);
    passwordDlg->exec();
    auto password = passwordValue->text();
    if (password=="32413135") {
        dlgProduceLineSet->exec();
    }
    else {
        QMessageBox::warning(this, "Error", "密码错误，请重新输入");
    }

    delete passwordValue;
    delete passwordDlg;

}

void ButtonScanner::pbtn_newProduction_clicked()
{

}

void ButtonScanner::pbtn_lightValue_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_lightValue, 2);
    numKeyBoard->exec();

    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.mainWindowConfig.lightValue = ui->pbtn_lightValue->text().toDouble();

    delete numKeyBoard;
}

void ButtonScanner::pbtn_score_clicked()
{
    dlgProductSet->exec();
}

void ButtonScanner::rbtn_debug_ckecked(bool checked)
{
    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.mainWindowConfig.isDebugMode = checked;
    GlobalStruct.saveConfig();
}

void ButtonScanner::rbtn_takePicture_ckecked(bool checked)
{
    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.mainWindowConfig.isTakePictures = checked;
    GlobalStruct.saveConfig();
}

void ButtonScanner::rbtn_removeFunc_ckecked(bool checked)
{
    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.mainWindowConfig.isEliminating = checked;
    GlobalStruct.saveConfig();
}

void ButtonScanner::rbtn_upLight_ckecked(bool checked)
{
    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.mainWindowConfig.upLight = checked;
    GlobalStruct.saveConfig();
}

void ButtonScanner::rbtn_sideLight_ckecked(bool checked)
{
    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.mainWindowConfig.sideLight = checked;
    GlobalStruct.saveConfig();
}

void ButtonScanner::rbtn_downLight_ckecked(bool checked)
{
    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.mainWindowConfig.downLight = checked;
    GlobalStruct.saveConfig();
}

void ButtonScanner::rbtn_defect_ckecked(bool checked)
{
    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.mainWindowConfig.isDefect = checked;
    GlobalStruct.saveConfig();
}

void ButtonScanner::rbtn_ForAndAgainst_ckecked(bool checked)
{
    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.mainWindowConfig.isPositive = checked;
    GlobalStruct.saveConfig();
}

void ButtonScanner::pbtn_exit_clicked()
{
    //TODO: question messagebox

    this->close();
}