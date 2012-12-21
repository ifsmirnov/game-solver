#include "configparser.hpp"



ConfigParser::ConfigParser()
{
    QString names[13] = {"opened", "one", "two", "three", "four", "five", "six", "seven", "eight", "unopened", "blown", "flag", "mine"};
    fieldNames.assign(names, names + 13);
}

bool ConfigParser::checkFile(const std::string& path) const
{
    std::ifstream reader(path, std::ios::in);
    if(reader != NULL)
    {
        reader.close();
        return true;
    }
    return false;
}

bool ConfigParser::checkPictures(const QDomElement& versionNode) const
{
    QDomElement child = versionNode.firstChildElement();
    int picturesFound = 0; //amount of pictures which were found, at the end it must equal to 11
    while(!child.isNull())
    {
        std::cout << child.tagName().toStdString() << std::endl;
        if (std::find(fieldNames.begin(), fieldNames.end(), child.tagName()) == fieldNames.end()) {
            return false;
        }
        if (!checkFile(child.text().toStdString())) {
            return false;
        }
        picturesFound++;
        child = child.nextSiblingElement();
    }
    return picturesFound == 13;
}

void ConfigParser::loadConfig(QComboBox* comboBox)
{
    if(checkFile("AppConfig.xml"))
    {
        QDomDocument document = QDomDocument();
        QFile file("AppConfig.xml");
        file.open(QIODevice::ReadOnly);
        document.setContent(&file);
        file.close();
        QDomNodeList childs = document.documentElement().elementsByTagName("versions");
        if(childs.length() == 1)
        {
            QDomElement versionNode = childs.item(0).firstChildElement();
            while(!versionNode.isNull())
            {
                if(checkPictures(versionNode))
                {
                    comboBox->addItem(versionNode.tagName());
                }
                versionNode = versionNode.nextSiblingElement();
            }
        }
    }
}

std::vector<QImage> ConfigParser::getImages(QString gameTypeName) const
{
    std::vector<QImage> res;
    QDomDocument document = QDomDocument();
    QFile file("AppConfig.xml");
    file.open(QIODevice::ReadOnly);
    document.setContent(&file);
    file.close();
    QDomElement child = document.documentElement().elementsByTagName(gameTypeName).item(0).firstChildElement();
    while(!child.isNull())
    {
        res.push_back(QImage(child.text()));
        child = child.nextSiblingElement();
    }
    return res;
}
