#pragma once
#ifndef APPSETUP_H
#define APPSETUP_H

#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class appSetup : public QDialog{
    public:
       explicit appSetup(QWidget* parent = nullptr);
    private:
        QLineEdit* userNameInput;
        QLineEdit* userPassInput;
        QPushButton* submitBtn;
        void handleInput(int n);
        void handleSubmit();
};

#endif