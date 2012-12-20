#include "configdialog.hpp"

ConfigDialog::ConfigDialog(QWidget *parent, ConfigParser* newParser) :
    QDialog(parent)
{
    configParser = newParser;
    createLayout();
}


ConfigDialog::OpenFileTool::OpenFileTool(QString name_, QPushButton* button_, QLineEdit* lineEdit_)
{
    name = name_;
    button = button_;
    lineEdit = lineEdit_;
}

void ConfigDialog::createLayout()
{
    QGridLayout *layout = new QGridLayout;
    QSignalMapper *signalMapper = new QSignalMapper(this);

    QString names[13] = {"unopened", "one", "two", "three", "four", "five", "six", "seven", "eight", "opened", "blown", "flag", "mine"};
    for(int i = 0; i < 13; i++)
    {
        tools.push_back(OpenFileTool(names[i], new QPushButton("Add " + names[i]), new QLineEdit("Push button to add file")));
        connect(tools[i].button, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(tools[i].button, i);
        layout->addWidget(tools[i].lineEdit);
        layout->addWidget(tools[i].button);
        tools[i].lineEdit->setReadOnly(true);
    }
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(clicked(int)));
    setLayout(layout);
}


void ConfigDialog::clicked(int x)
{
    QString filename = QFileDialog::getOpenFileName(
        this,
        tr("Open Document"),
        QDir::currentPath(),
        tr("Image files (*.png *.jpg *.jpeg);;All files (*.*)") );
    if(!filename.isNull()  ||  configParser->checkFile(filename.toStdString()))
    {
        tools[x].lineEdit->setText(filename);
    }
}

