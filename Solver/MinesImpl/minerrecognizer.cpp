#include "minerrecognizer.hpp"
#include "app_headers/app_recognizer.hpp"
#include <map>
#include <iostream>

MinerRecognizer::MinerRecognizer()
{
}


std::unique_ptr<AppState> MinerRecognizer::recognize(QImage image)
{

    return std::unique_ptr<AppState>(new AppState(new AppInternalState(), new AppExternalState()));
}


std::map<QRgb, double> MinerRecognizer::getColorPartition(QImage image)
{
    std::map<QRgb, double> tmp;
    for (int i = 0; i < image.width(); i++)
    {
        for (int j = 0; j < image.height(); j++)
        {
            QRgb temp = image.pixel(i, j);
            if (tmp.find(temp) != tmp.end())
            {
                double x = tmp.find(temp)->second;
                tmp.erase(tmp.find(temp));
                tmp.insert(std::pair<QRgb, double>(temp, x + 1));
            }
            else
            {
                tmp.insert(std::pair<QRgb, double>(temp, 1));
            }
        }
    }
    std::map<QRgb, double> result;
    for (std::map<QRgb, double>::iterator it = tmp.begin(); it != tmp.end(); it++)
    {
        result.insert(std::pair<QRgb, double>(it->first, it->second/double(image.width() * image.height())));
    }
    return result;
}

double MinerRecognizer::getDiffInColors(std::map<QRgb, double> x, std::map<QRgb, double> y)
{
    std::map<QRgb, double>::iterator xIt, yIt;
    xIt = x.begin();
    yIt = y.begin();
    double result = 0;
    while(xIt != x.end()  ||  yIt != y.end())
    {
        if (xIt == x.end()  ||  (yIt != y.end()  &&  yIt->first < xIt->first))
        {
            result += yIt->second;
            yIt++;
        }
        else if (yIt == y.end()  ||  (xIt != x.end()  &&  xIt->first < yIt->first))
        {
            result += xIt->second;
            xIt++;
        }
        else
        {
            result += fabs(xIt->second - yIt->second);
            xIt++;
            yIt++;
        }
    }
    return result;
}

int MinerRecognizer::bestVariant(QImage image, std::vector<QImage> variants)
{
    int ans = -1;
    double diff = 3;
    std::map<QRgb, double> colors = getColorPartition(image);
    for (int i = 0; i < variants.size(); i++)
    {
        double temp = getDiffInColors(colors, getColorPartition(variants[i]));
        std::cout << diff << ' ' << temp << std::endl;
        if (temp < diff)
        {
            diff = temp;
            ans = i;
        }
    }
    return ans;
}


