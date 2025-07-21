#pragma once
#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QPushButton>

class login : public QDialog {
    public:
        explicit login(QWidget* parent=nullptr);
    private:
        QPushButton* submitbtn;
        QLineEdit* userPass;
        void handleInput();
        void handleSubmit();
};

#endif
