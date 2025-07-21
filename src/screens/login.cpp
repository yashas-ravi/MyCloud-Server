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
    QHBoxLayout* mainWrapper = new QHBoxLayout(this);
    // main window widget
    QWidget* mainWindow = new QWidget(this);
    mainWindow->setObjectName("mainWindow");
    //image widget
    QLabel* imgHolder = new QLabel(mainWindow);
    QPixmap img("/assets/login-img.png");
    imgHolder->setPixmap(img);
    imgHolder->setScaledContents(true);
    imgHolder->setFixedSize(400,400);
    imgHolder->show();
    //form widget
    QWidget* formWidget = new QWidget(mainWindow);
    //heading
    QLabel* heading =  new QLabel("Login to MyCloud");
    heading->setObjectName("heading");
    heading->setWordWrap(true);
    //get user name
    auth a;
    std::string userName = a.getUser();
    //label
    QLabel* userLabel = new QLabel(formWidget);
    userLabel->setText(QString::fromStdString(userName));
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
    //submit button
    submitbtn = new QPushButton(formWidget);
    submitbtn->setText("Login");
    submitbtn->setCursor(Qt::PointingHandCursor);
    submitbtn->setDisabled(true);
    submitbtn->setStyleSheet("submitBtn");
    //add things together
    QVBoxLayout* formWrapper = new QVBoxLayout(formWidget);
    formWrapper->addWidget(heading);
    formWrapper->addSpacing(20);
    formWrapper->addWidget(userLabel);
    formWrapper->addSpacing(10);
    formWrapper->addWidget(userPass);
    formWrapper->addStretch();
    //add image and form together
    mainWrapper->addWidget(imgHolder);
    mainWrapper->addSpacing(10);
    mainWrapper->addWidget(formWidget);
    //set main window
    mainWindow->setLayout(mainWrapper);

    connect(userPass, &QLineEdit::textChanged, this, &login::handleInput);
    connect(submitbtn, &QPushButton::pressed, this, &login::handleSubmit);

    this->setStyleSheet(R"(
        #mainWindow{
            backgound-color: #1e1e2f;
        }
        #heading{
            font-size: 30px;
            font-weight: bold;
            color: white;
        }
        #userName{
            font-size: 15px;
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
    accept();
}