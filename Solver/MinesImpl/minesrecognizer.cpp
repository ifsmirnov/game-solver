#include "minesrecognizer.hpp"
#include "app_headers/app_recognizer.hpp"
#include <map>
#include <iostream>


MinesRecognizer::MinesRecognizer()
{
}


std::unique_ptr<AppState> MinesRecognizer::recognize(QImage image)
{
    return std::unique_ptr<AppState>(new AppState(new AppInternalState(), new AppExternalState()));
}


std::map<QRgb, double> MinesRecognizer::getColorPartition(const QImage& image) const
{
    std::map<QRgb, double> pixelMap;
    for (int i = 0; i < image.width(); i++)
    {
        for (int j = 0; j < image.height(); j++)
        {
            QRgb currColor = image.pixel(i, j);
            pixelMap[currColor] += 1;
        }
    }
    std::map<QRgb, double> result;
    for (std::map<QRgb, double>::iterator it = pixelMap.begin(); it != pixelMap.end(); it++)
    {
        result.insert(std::pair<QRgb, double>(it->first, it->second/double(image.width() * image.height())));
    }
    return result;
}

double MinesRecognizer::getDiffInColors(const std::map<QRgb, double>& x, const std::map<QRgb, double>& y) const
{
    std::map<QRgb, double>::const_iterator xIt, yIt;
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

int MinesRecognizer::bestVariant(const QImage& image, const std::vector<QImage>& variants) const
{
    int ans = -1;
    double diff = 3;
    std::map<QRgb, double> colors = getColorPartition(image);
    for (size_t i = 0; i < variants.size(); i++)
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


