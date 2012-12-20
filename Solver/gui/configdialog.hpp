#ifndef CONFIGDIALOG_HPP
#define CONFIGDIALOG_HPP

#include <QDialog>
#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QFileDialog>
#include <QSignalMapper>
#include <memory>
#include "configparser.hpp"

class ConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfigDialog(QWidget *parent, ConfigParser* newParser);
    void createLayout();
signals:
    void released();
private slots:
    void clicked(int x);
private:
    class OpenFileTool
    {
    public:
        explicit OpenFileTool(QString, QPushButton*, QLineEdit*);

        QPushButton* button;
        QLineEdit* lineEdit;
        QString name;
    };

    ConfigParser* configParser;
    std::vector<OpenFileTool> tools;
};

#endif // CONFIGDIALOG_HPP
