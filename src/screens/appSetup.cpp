//Hello, this program is for setup screen

#include <QWidget>
#include <QHBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QLineEdit>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include "appSetup.h"
#include "auth.h"
using namespace std;

appSetup::appSetup(QWidget* parent) : QDialog(parent){
    setAttribute(Qt::WA_TranslucentBackground);
    resize(1080,700);
    //initilize widgets
    //main window layout
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    //sub main window
    QWidget* mainWindow = new QWidget(this);
    mainWindow->setObjectName("mainWindow");
    //form holder widget
    QWidget* formHolder = new QWidget(mainWindow);
    formHolder->setObjectName("formHolder");
    //
    QWidget* appInfo = new QWidget(mainWindow);
    //widget for holding background image
    QLabel* bgHolder = new QLabel(appInfo);
    //set background image
    QPixmap image(":assets/setup-bg.png");
    bgHolder->setScaledContents(true);
    bgHolder->setPixmap(image); 
    bgHolder->setFixedSize(400,400);
    bgHolder->show();
    //app info
    QLabel* aboutText = new QLabel("Host your own personal cloud server right from your desktop or laptop.\nSync, access, and manage your files remotely.");
    aboutText->setWordWrap(true);
    aboutText->setObjectName("aboutText");
    //MyCloud text 
    QLabel* greetText = new QLabel("MyCloud");
    greetText->setObjectName("greetText");
    //text about our software
    QLabel* aboutInput = new QLabel("User name should be 3-12 characters long. \npassword should be 6-15 characters long.");
    aboutInput->setWordWrap(true);
    aboutInput->setObjectName("aboutInput");

    //form labels and inputs
    //adding validators for user inputs
    QRegularExpression nameRegex("[A-Za-z0-9 ]{3,12}"); //for user name
    QValidator* validName = new QRegularExpressionValidator(nameRegex, formHolder);
    QRegularExpression passRegix("[A-Za-z0-9]{6,15}");  //for user password
    QValidator* validPass = new QRegularExpressionValidator(passRegix, formHolder);

    QLabel* userName  = new QLabel("Your name");
    userName->setObjectName("formInputLabels");
    userName->adjustSize();
    userNameInput = new QLineEdit(formHolder);
    userNameInput->setValidator(validName);
    userNameInput->setMaxLength(12);
    userNameInput->setObjectName("formNameInputs");

    QLabel* userPass  = new QLabel("set server password");
    userPass->setObjectName("formInputLabels");
    userPass->adjustSize();
    userPassInput = new QLineEdit(formHolder);
    userPassInput->setValidator(validPass);
    userPassInput->setMaxLength(15);
    userPassInput->setEchoMode(QLineEdit::Password);
    userPassInput->setObjectName("formPassInputs");

    //submit button
    submitBtn = new QPushButton(formHolder);
    submitBtn->setText("Submit");
    submitBtn->setCursor(Qt::PointingHandCursor);
    submitBtn->setObjectName("formBtn");
    submitBtn->setDisabled(true);
    
    //Image and info layout
    QVBoxLayout* bgInfoWrapper = new QVBoxLayout();
    bgInfoWrapper->addWidget(bgHolder);
    bgInfoWrapper->addWidget(aboutText);

    //form layout
    QVBoxLayout* formWrapper = new QVBoxLayout();
    formWrapper->addWidget(greetText,0,Qt::AlignTop | Qt::AlignCenter);
    formWrapper->addSpacing(20);
    formWrapper->addWidget(aboutInput,0,Qt::AlignCenter);
    formWrapper->addSpacing(50);
    formWrapper->addWidget(userName,0,Qt::AlignLeft);
    formWrapper->addWidget(userNameInput);
    formWrapper->addSpacing(20);
    formWrapper->addWidget(userPass,0,Qt::AlignLeft);
    formWrapper->addWidget(userPassInput);
    formWrapper->addSpacing(40);
    formWrapper->addWidget(submitBtn);
    formWrapper->addStretch();
    
    //form widget
    formHolder->setFixedSize(300, 500);
    formHolder->setLayout(formWrapper);
    //appinfo widget
    appInfo->setFixedSize(400,500);
    appInfo->setLayout(bgInfoWrapper);
    //all widgets holder
    QHBoxLayout* widgetWrapper = new QHBoxLayout();
    widgetWrapper->addWidget(appInfo);
    widgetWrapper->addWidget(formHolder);
  
    //main layout widget
    mainWindow->setLayout(widgetWrapper);

    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(mainWindow);

    //add function to validate inputs
    connect(userNameInput, &QLineEdit::textChanged, this, [=](){handleInput(1);});
    connect(userPassInput, &QLineEdit::textChanged, this, [=](){handleInput(2);});
    connect(submitBtn, &QPushButton::pressed, this, &appSetup::handleSubmit);

    //lets add styling here
    this->setStyleSheet(R"(
        #mainWindow{
            background-color: #1e1e2f;
        }

        #greetText{
            font-size: 30px;
            font-weight: bold;
            color: white;
        }

        #aboutText{
            font-size: 18px;
            font-weight: normal;
            color: white;
            padding: 5px;
        }

        #aboutInput{
            font-size: 15px;
            font-weight: normal;
            color: gray;
            padding: 0px 5px;
        }

        #formInputLabels{
            font-size: 15px;
            color: white;
            font-weight: normal;
            height: fit-content;
        }

        #formNameInputs{
            font-size: 15px;
            color:rgb(201, 204, 205);
            font-weight: normal;
            background-color:rgb(47, 47, 74);
            border: none;
            border-bottom: 2px solid rgb(49, 49, 123);
        }
        
        #formPassInputs{
            font-size: 15px;
            color:rgb(201, 204, 205);
            font-weight: normal;
            background-color:rgb(47, 47, 74);
            border: none;
            border-bottom: 2px solid rgb(49, 49, 123);
        }

        #formBtn{
            color: white;
            background-color: rgb(49, 49, 123);
            padding: 5px;
            border-radius: 5px;
        }
        #formBtn:disabled{
            color: rgb(200, 200, 200);
            background-color: rgb(29, 29, 94);
        }
        
        )"
    );
};

void appSetup::handleInput(int n){
    if(n==1 && !userNameInput->hasAcceptableInput()){
        userNameInput->setStyleSheet("border-bottom: 2px solid rgb(123, 49, 49);");
    }
    else{
        userNameInput->setStyleSheet("border-bottom: 2px solid rgb(49, 49, 123);");
    }
    if(n==2 && !userPassInput->hasAcceptableInput()){
        userPassInput->setStyleSheet("border-bottom: 2px solid rgb(123, 49, 49);");
    }
    else{
        userPassInput->setStyleSheet("border-bottom: 2px solid rgb(49, 49, 123);");
    }
    if(userNameInput->hasAcceptableInput()&&userPassInput->hasAcceptableInput()){submitBtn->setDisabled(false);}
    else{submitBtn->setDisabled(true);}
};

void appSetup::handleSubmit(){
    auth a;
    int status = a.registerUser(userNameInput->text().toStdString(), userPassInput->text().toStdString());
    if(status==0){
        submitBtn->setText("Done");
        submitBtn->setStyleSheet("background-color: rgb(44, 123, 48); color: rgb(5, 209, 49);");
        accept();
    }
    else{
        submitBtn->setText("someting went wrong");
        submitBtn->setStyleSheet("background-color: rgb(123, 49, 49); color: rgb(209, 5, 5);");
    }
};