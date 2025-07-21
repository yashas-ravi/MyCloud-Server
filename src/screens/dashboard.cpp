#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "dashboard.h"

    Dashboard::Dashboard(QWidget* parent) : QWidget(parent){
        setAttribute(Qt::WA_TranslucentBackground);
        resize(1080,700);

        QVBoxLayout* mainWindowLayout = new QVBoxLayout(this);

        QWidget* widget = new QWidget(this);
        widget->setStyleSheet(
            "background-color:blue;"
        );

        mainWindowLayout->addWidget(widget);
    }