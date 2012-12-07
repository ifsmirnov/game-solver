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

std::map<QRgb, double> MinesRecognizer::getColorPartition(const QImage& image, QRect rect = QRect()) const
{
    int clusterModule = 64; //magic
    if (rect.isNull())
        rect = image.rect();
    std::map<QRgb, double> pixelMap;
    for (int i = rect.left(); i <= rect.right(); i++)
    {
        for (int j = rect.top(); j <= rect.bottom(); j++)
        {
            QRgb currColor = image.pixel(i, j);
            int r, g, b;
            if (qRed(currColor) % clusterModule >= clusterModule / 2) {
                r = (qRed(currColor) / clusterModule) * clusterModule + clusterModule;
            } else {
                r = (qRed(currColor) / clusterModule) * clusterModule;
            }
            if (qGreen(currColor) % clusterModule >= clusterModule / 2) {
                g = (qGreen(currColor) / clusterModule) * clusterModule + clusterModule;
            } else {
                g = (qGreen(currColor) / clusterModule) * clusterModule;
            }
            if (qBlue(currColor) % clusterModule >= clusterModule / 2) {
                b = (qBlue(currColor) / clusterModule) * clusterModule + clusterModule;
            } else {
                b = (qBlue(currColor) / clusterModule) * clusterModule;
            }
            pixelMap[qRgb(r, g, b)] += 1;
        }
    }
    double factor = rect.width() * rect.height();
    std::map<QRgb, double> result;
    for (std::map<QRgb, double>::iterator it = pixelMap.begin(); it != pixelMap.end(); it++)
    {
        result.insert(std::pair<QRgb, double>(it->first, it->second/factor));
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
    return result / 2.0;
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

std::vector<std::vector<double> > MinesRecognizer::gridSimilarity(const QImage &image, const std::vector<QImage> &patterns, int size) const
{
    std::vector<std::map<QRgb, double> > patternColoring;
    for (const auto &i: patterns)
        patternColoring.push_back(getColorPartition(i));

    std::vector<std::vector<double> > res(image.width() - size + 1, std::vector<double>(image.height() - size + 1));

    for (int i = 0; i < image.width() - size + 1; i++)
    {
        for (int j = 0; j < image.height() - size + 1; j++)
        {
            double min = 1.0;
            for (const auto &pattern: patternColoring)
                min = std::min(min, getDiffInColors(pattern, getColorPartition(image, QRect(i, j, size, size))));
            res[i][j] = min;
        }
    }
    return res;
}
