#include "configdialog.hpp"


ConfigDialog::ConfigDialog(QWidget *parent, ConfigParser* newParser) :
    QDialog(parent)
{
    QString names_[13] = {"opened", "one", "two", "three", "four", "five", "six", "seven", "eight", "unopened", "blown", "flag", "mine"};
    names.assign(names_, names_ + 13);
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
    versionName = new QLineEdit("Type name of version here (no spaces)");
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(versionName);
    QSignalMapper *signalMapper = new QSignalMapper(this);

    for(int i = 0; i < 13; i++)
    {
        tools.push_back(OpenFileTool(names[i], new QPushButton("Add " + names[i]), new QLineEdit("Push button to add file")));
        connect(tools[i].button, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(tools[i].button, i);
        layout->addWidget(tools[i].lineEdit);
        layout->addWidget(tools[i].button);
        tools[i].lineEdit->setReadOnly(true);
    }
    QPushButton* okButton = new QPushButton("OK");
    connect(okButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(okButton, 13);
    layout->addWidget(okButton);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(clicked(int)));
    setLayout(layout);
}


void ConfigDialog::clicked(int x)
{
    if(x == 13)
    {
        QString boxText;
        bool fail = false;
        for(int i = 0; i < 13; i++)
        {
            boxText = tools[i].lineEdit->text();
            if (boxText.isNull()  ||  boxText.isEmpty()  ||  boxText == "Push button to add file"  ||  !configParser->checkFile(boxText.toStdString()))
            {
                QMessageBox qmBox;
                qmBox.setText("Error while opening files");
                qmBox.exec();
                fail = true;
                break;
            }
        }
        boxText = versionName->text();
        if (boxText.isNull()  ||  boxText.isEmpty()  ||  boxText == "Type name of version here (no spaces)"  ||  boxText.contains(" "))
        {
            QMessageBox qmBox;
            qmBox.setText("Error in version name");
            qmBox.exec();
            fail = true;
        }
        if(!fail)
        {
            std::cerr << "HERE";
            QDomDocument document = QDomDocument();
            QFile file("AppConfig.xml");
            file.open(QIODevice::ReadOnly);
            document.setContent(&file);
            file.close();
            QString destinationDir = QString("img") + QDir::separator() + boxText;
            if(!QDir(destinationDir).exists())
            {
                QDir().mkdir(destinationDir);
            }
            QDomNodeList versions = document.elementsByTagName("versions");
            QDomElement newVersion = document.createElement(boxText);
            for(int i = 0; i < 13; i++)
            {
                QDomElement newImage = document.createElement(names[i]);
                QString destinationFile = destinationDir + QDir::separator() + names[i] + ".png";
                QFile::copy(tools[i].lineEdit->text(), destinationFile);
                QDomText text = document.createTextNode(destinationFile);
                newImage.appendChild(text);
                newVersion.appendChild(newImage);
            }
            versions.item(0).appendChild(newVersion);
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream stream(&file);
            stream << document.toString();
            file.close();
            close();
        }
        return;
    }
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

