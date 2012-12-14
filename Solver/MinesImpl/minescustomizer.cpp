#include "minescustomizer.hpp"

#include <QtGui>
#include <QGridLayout>

MinesCustomizer::MinesCustomizer(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *layout = new QGridLayout;

    submitButton = new QPushButton("OK");
    widthEdit = new QLineEdit;
    heightEdit = new QLineEdit;

    layout->addWidget(widthEdit, 1, 1);
    layout->addWidget(heightEdit, 1, 2);
    layout->addWidget(submitButton, 2, 1, 1, 2, Qt::AlignCenter);

    setLayout(layout);
}
