#include "configparser.hpp"



ConfigParser::ConfigParser()
{
    QString names[11] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "opened", "unopened", "blown"};
    fieldNames.assign(names, names + 11);
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

bool ConfigParser::checkPictures(const QDomElement& vesionNode) const
{
    QDomElement child = vesionNode.firstChildElement();
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
    return true;
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
            QDomElement vesionNode = childs.item(0).firstChildElement();
            bool fail = false;
            while(!vesionNode.isNull())
            {
                if(checkPictures(vesionNode))
                {
                    comboBox->addItem(vesionNode.tagName());
                }
                vesionNode = vesionNode.nextSiblingElement();
            }
        }
    }
}


