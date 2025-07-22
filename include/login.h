#pragma once
#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>

class login : public QDialog {
    public:
        explicit login(QWidget* parent=nullptr);
    private:
        QPushButton* submitbtn;
        QLineEdit* userPass;
        QLabel* valText;
        void handleInput();
        void handleSubmit();
};

#endif
