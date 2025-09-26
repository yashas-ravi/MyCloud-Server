#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QIcon>
#include "dashboard.h"

    Dashboard::Dashboard(QWidget* parent) : QWidget(parent){
        setAttribute(Qt::WA_TranslucentBackground);
        resize(1080,700);
        //window layout and widgets
        QVBoxLayout* mainWindowLayout = new QVBoxLayout(this);
        QWidget* mainWidget = new QWidget(this);
        mainWidget->setObjectName("mainWindow");

        QVBoxLayout* widgetsWrapper = new QVBoxLayout();
        mainWidget->setLayout(widgetsWrapper);

        //header
        QWidget* header = new QWidget(this);
        QHBoxLayout* headerLayout = new QHBoxLayout();
        header->setObjectName("header");
        header->setFixedHeight(100);
        header->setLayout(headerLayout);
        // title
        QLabel* title = new QLabel("MyCloud  Server");
        title->setObjectName("title");
        // home button
        QPushButton* homeBtn = new QPushButton;
        homeBtn->setIcon(QIcon(":assets/dashboard.png"));
        homeBtn->setIconSize(QSize(32, 32));
        homeBtn->setCursor(Qt::PointingHandCursor);
        homeBtn->setFixedSize(35,35);
        homeBtn->setObjectName("headerBtns");
        homeBtn->setFlat(true);
        // connection button
        QPushButton* connectionBtn = new QPushButton;
        connectionBtn->setIcon(QIcon(":assets/globe.png"));
        connectionBtn->setIconSize(QSize(32, 32));
        connectionBtn->setFixedSize(35,35);
        connectionBtn->setObjectName("headerBtns");
        connectionBtn->setCursor(Qt::PointingHandCursor);
        connectionBtn->setFlat(true);
        // settings button
        QPushButton* settingsBtn = new QPushButton;
        settingsBtn->setIcon(QIcon(":assets/settings.png"));
        settingsBtn->setIconSize(QSize(32, 32));
        settingsBtn->setFixedSize(35,35);
        settingsBtn->setObjectName("headerBtns");
        settingsBtn->setCursor(Qt::PointingHandCursor);
        settingsBtn->setFlat(true);

        headerLayout->addSpacing(20);
        headerLayout->addWidget(title);
        headerLayout->addStretch();
        headerLayout->addWidget(homeBtn);
        headerLayout->addSpacing(100);
        headerLayout->addWidget(connectionBtn);
        headerLayout->addSpacing(100);
        headerLayout->addWidget(settingsBtn);
        headerLayout->addSpacing(100);

        //tabs
        QStackedWidget* stackScreen = new QStackedWidget;

        //
        //home screen
        QWidget *home = new QWidget;
        QVBoxLayout *homeLayout = new QVBoxLayout;
        //address bar
        QWidget* addressBar = new QWidget;
        QHBoxLayout* addressBarLayout = new QHBoxLayout;
        addressBar->setLayout(addressBarLayout);
        QLabel* addrText1 = new QLabel("Server is Running on ");
        addrText1->setObjectName("addrText1");
        addressBarLayout->addWidget(addrText1);
        homeLayout->addWidget(addressBar);
        homeLayout->addStretch();
        home->setLayout(homeLayout);

        //
        //connections screen
        QWidget *connections = new QWidget;
        QVBoxLayout *connectionsLayout = new QVBoxLayout;
        QLabel* conText1 = new QLabel("Connected Devices");
        conText1->setObjectName("conText1");
        connectionsLayout->addWidget(conText1);
        connectionsLayout->addStretch();
        connections->setLayout(connectionsLayout);
        
        //
        //settings screen
        QWidget *settings = new QWidget;
        QVBoxLayout *settingsLayout = new QVBoxLayout;
        QLabel* settingText = new QLabel("Settings");
        settingText->setObjectName("settingText");
        settingsLayout->addWidget(settingText);
        settingsLayout->addStretch();
        settings->setLayout(settingsLayout);
        //
        stackScreen->addWidget(home);
        stackScreen->addWidget(connections);
        stackScreen->addWidget(settings);
        stackScreen->setCurrentIndex(0);

        //body
        QWidget* body = new QWidget(this);
        body->setObjectName("body");
        body->setFixedHeight(600);
        QVBoxLayout* bodyLayout = new QVBoxLayout();

        bodyLayout->addWidget(stackScreen);
        body->setLayout(bodyLayout);

        //set widgets and layouts
        widgetsWrapper->addWidget(header);
        widgetsWrapper->addWidget(body);
        mainWindowLayout->setContentsMargins(0,0,0,0);
        mainWindowLayout->addWidget(mainWidget);

        connect(homeBtn, &QPushButton::clicked,[=](){stackScreen->setCurrentIndex(0);});
        connect(connectionBtn, &QPushButton::clicked,[=](){stackScreen->setCurrentIndex(1);});
        connect(settingsBtn, &QPushButton::clicked,[=](){stackScreen->setCurrentIndex(2);});

        this->setStyleSheet(R"(
                #mainWindow{
                    background-color: #1e1e2f;
                }
                #header{
                    border-radius: 15px;
                    background-color: #3d3d5eff;
                }
                #title{
                    font-size: 25px;
                    font-weight: bold;
                    color: white;
                }
                QPushButton{
                    border: none;
                }
                #addrText1, #conText1, #settingText{
                    font-size: 18px;
                    font-weight: normal;
                    color: white;
                }
            )");
    }