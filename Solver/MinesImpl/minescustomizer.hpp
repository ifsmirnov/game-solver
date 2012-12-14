#ifndef MINESCUSTOMIZER_HPP
#define MINESCUSTOMIZER_HPP

#include <QWidget>
#include <QtGui>

class MinesCustomizer : public QWidget
{
    Q_OBJECT
public:
    explicit MinesCustomizer(QWidget *parent = 0);

private:
    QPushButton *submitButton;
    QLineEdit *widthEdit, *heightEdit;

};

#endif // MINESCUSTOMIZER_HPP
