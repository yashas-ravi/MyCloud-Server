#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QLineEdit>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include "auth.h"
#include "login.h"

login::login(QWidget* parent):QDialog(parent){
    setAttribute(Qt::WA_TranslucentBackground);
    resize(1080,700);
    //main window layout
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    // main window widget
    QWidget* mainWindow = new QWidget(this);
    mainWindow->setObjectName("mainWindow");
    //image widget
    QLabel* imgHolder = new QLabel(mainWindow);
    QPixmap img(":assets/login-img.png");
    imgHolder->setPixmap(img);
    imgHolder->setScaledContents(true);
    imgHolder->setFixedSize(300,300);
    imgHolder->show();
    //form widget
    QWidget* formWidget = new QWidget(mainWindow);
    formWidget->setFixedSize(300,500);
    //heading
    QLabel* heading =  new QLabel("Login to MyCloud");
    heading->setObjectName("heading");
    heading->setWordWrap(true);
    //get user name
    auth a;
    std::string userName = a.getUser();
    //label
    QLabel* userLabel = new QLabel(formWidget);
    userLabel->setText("user: "+QString::fromStdString(userName));
    userLabel->setObjectName("userName");
    //password validator
    QRegularExpression passRegix("[A-Za-z0-9]{6,15}");  //for user password
    QValidator* validPass = new QRegularExpressionValidator(passRegix, formWidget);
    //user password
    userPass = new QLineEdit(formWidget);
    userPass->setPlaceholderText("Enter password");
    userPass->setValidator(validPass);
    userPass->setMaxLength(15);
    userPass->setObjectName("userPass");
    //validator text
    valText = new QLabel(formWidget);
    valText->setText("");
    valText->setAlignment(Qt::AlignCenter);
    valText->setObjectName("valText");
    //submit button
    submitbtn = new QPushButton(formWidget);
    submitbtn->setText("Login");
    submitbtn->setObjectName("submitBtn");
    submitbtn->setCursor(Qt::PointingHandCursor);
    submitbtn->setDisabled(true);
    //add things together
    QVBoxLayout* formWrapper = new QVBoxLayout(formWidget);
    formWrapper->addWidget(heading,0,Qt::AlignHCenter);
    formWrapper->addSpacing(40);
    formWrapper->addWidget(userLabel,0,Qt::AlignHCenter);
    formWrapper->addSpacing(10);
    formWrapper->addWidget(userPass);
    formWrapper->addSpacing(40);
    formWrapper->addWidget(valText);
    formWrapper->addSpacing(10);
    formWrapper->addWidget(submitbtn);
    formWrapper->addStretch();
    //add image and form together
    QHBoxLayout* windowWrapper = new QHBoxLayout(mainWindow);
    windowWrapper->addWidget(imgHolder,0,Qt::AlignCenter);
    windowWrapper->addSpacing(20);
    windowWrapper->addWidget(formWidget,0,Qt::AlignCenter);
    windowWrapper->addSpacing(20);
    mainWindow->setLayout(windowWrapper);
    //set main window
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(mainWindow);
    //connect methods to states
    connect(userPass, &QLineEdit::textChanged, this, &login::handleInput);
    connect(submitbtn, &QPushButton::pressed, this, &login::handleSubmit);

    this->setStyleSheet(R"(
        #mainWindow{
            background-color: #1e1e2f;
        }
        #heading{
            font-size: 30px;
            font-weight: bold;
            color: white;
        }
        #userName{
            font-size: 18px;
            color: white;
            font-weight: normal;
            height: fit-content;
        }
        #userPass{
            font-size: 15px;
            color:rgb(201, 204, 205);
            font-weight: normal;
            background-color:rgb(47, 47, 74);
            border: none;
            border-bottom: 2px solid rgb(49, 49, 123);
        }
        #submitBtn{
            color: white;
            background-color: rgb(49, 49, 123);
            padding: 5px;
            border-radius: 5px;
        }
        #submitBtn:disabled{
            color: rgb(200, 200, 200);
            background-color: rgb(29, 29, 94);
        }
        #valText{
            color: transparent;
            background-color: transparent;
            font-size: 15px;
            font-weight: normal;
            padding: 5px;
            border-radius:5px;
        }
        )"
    );
}

void login::handleInput(){
    if(!userPass->hasAcceptableInput()){
        userPass->setStyleSheet("border-bottom: 2px solid rgb(123, 49, 49);");
        submitbtn->setDisabled(true);
    }
    else{
        userPass->setStyleSheet("border-bottom: 2px solid rgb(49, 49, 123);");
        submitbtn->setDisabled(false);
    }
} 

void login::handleSubmit(){
    auth Oauth;
    int getVal = Oauth.validateUser(userPass->text().toStdString());
    if(getVal==1){
        valText->setText("Login Successful");
        valText->setStyleSheet("background-color: rgb(98, 241, 132); color: rgb(14, 131, 25)");
        accept();
    }
    else{
        valText->setText("Wrong Password");
        valText->setStyleSheet("background-color: rgb(250, 109, 109); color: rgb(156, 17, 17)");
    }
}