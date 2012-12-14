#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP

#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNodeList>
#include <QtXml/QDomNode>
#include <QComboBox>
#include <QString>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <QFile>


class ConfigParser {
private:
    std::vector<QString> fieldNames;

public:
    ConfigParser();
    bool checkFile(const std::string&) const;
    bool checkPictures(const QDomElement&) const;
    void loadConfig(QComboBox*);
};



#endif // CONFIGPARSER_HPP
