#include "minesrecognizer.hpp"
#include "minesinternalstate.hpp"
#include "minesexternalstate.hpp"
#include "minesrecognizerhelper.hpp"
#include "app_headers/app_recognizer.hpp"
#include <map>
#include <limits>
#include <iostream>
#include "clickcoordreciever.hpp"
#include "renderarea.hpp"

MinesRecognizer::MinesRecognizer()
{
    posFound = false;
}

int MinesRecognizer::getNearestCluster(int color, int clusterModule) const{
    if (color % clusterModule >= clusterModule / 2)
    {
        return color / clusterModule * clusterModule + clusterModule;
    }
    else
    {
        return color / clusterModule * clusterModule;
    }
}

std::unique_ptr<AppState> MinesRecognizer::recognize(const QImage &image, AppRecognizerHelper* helper_)
{
    MinesRecognizerHelper *helper = dynamic_cast<MinesRecognizerHelper*>(helper_);

    int w = 16, h = 16;

    if (cachedCells.empty())
        cachedCells.assign(w, std::vector<int>(h, 9));
    const static int unopened = 9;
    const static char* display = " 12345678.x+*";

    if(!posFound)
    {
        std::vector<QPoint> clicks = getUserClicks(image);
        pos = bestGridPosition(clicks, w, h);
        //pos = std::make_pair(QPoint(385, 106), 40); // default for fullscreen on IS laptop
        posFound = true;
    }
    /*RenderArea *ra = new RenderArea;
    ra->setImage(image.copy(pos.first.x() - pos.second / 2,
                            pos.first.y() - pos.second / 2,
                            pos.second * w, pos.second * h));
    ra->show();*/
    std::vector<QImage> samples = helper->getImages();
    MinesInternalState* internalState = new MinesInternalState(w, h);
    MinesExternalState* externalState = new MinesExternalState(w, h);
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            QImage img = image.copy(pos.first.x() - pos.second/2 + pos.second * i,
                                    pos.first.y() - pos.second/2 + pos.second * j,
                                    pos.second, pos.second);
            int cell = cachedCells[i][j];
            if (cell == unopened)
            {
                cell = bestVariant(img, samples);
                cachedCells[i][j] = cell;
            }
            internalState->setField(i, j, cell);
            externalState->setCoordinate(i, j, pos.first.x() + pos.second * i, pos.first.y() + pos.second * j);

            std::cerr << display[cell] << std::flush;
        }
        std::cerr << std::endl << std::flush;
    }
    std::cerr << "Recognizer: recognized" << std::endl << std::flush;
    return std::unique_ptr<AppState>(new AppState(internalState, externalState));
}

std::map<QRgb, double> MinesRecognizer::getColorPartition(const QImage& image, QRect rect = QRect()) const
{
    //int clusterModule = 64; //magic
    int clusterModule = 1; // even more magic!
    if (rect.isNull())
        rect = image.rect();
    std::map<QRgb, double> pixelMap;
    for (int i = rect.left(); i <= rect.right(); i++)
    {
        for (int j = rect.top(); j <= rect.bottom(); j++)
        {
            QRgb currColor = image.pixel(i, j);
            int r, g, b;
            r = getNearestCluster(qRed(currColor), clusterModule);
            g = getNearestCluster(qGreen(currColor), clusterModule);
            b = getNearestCluster(qBlue(currColor), clusterModule);
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

std::vector<QPoint> MinesRecognizer::getUserClicks(const QImage &image)
{
    ClickCoordReciever *clickCoordReciever = new ClickCoordReciever;
    return clickCoordReciever->getClicks(image, 5);
}

std::pair<QPoint, int> MinesRecognizer::bestGridPosition(std::vector<QPoint> pts, int fieldW, int fieldH)
{
    if (pts.size() < 2u)
        throw;

    QPoint ul = pts[0], dr = pts[1];
    int probableSize = (dr.x() - ul.x()) / (fieldW - 1);
    int minSize = probableSize*0.9 - 10;
    int maxSize = probableSize*1.1 + 10;
    minSize = std::max(0, minSize);

    long long bestDev = std::numeric_limits<long long>::max();
    std::pair<QPoint, int> res;

    for (int size = minSize; size <= maxSize; size++)
    {
        for (int sx = ul.x() - maxSize; sx <= ul.x() + maxSize; sx++)
        {
            for (int sy = ul.y() - maxSize; sy <= ul.y() + maxSize; sy++)
            {
                long long curDev = 0;
                for (auto it: pts)
                {
                    int bestDist = std::numeric_limits<int>::max();
                    for (int i = 0; i < fieldW; i++)
                    {
                        for (int j = 0; j < fieldH; j++)
                        {
                            int x = sx + size*i, y = sy + size*j;
                            bestDist = std::min(bestDist, (it.x() - x) * (it.x() - x) + (it.y() - y) * (it.y() - y));
                        }
                    }
                    curDev += bestDist;
                }
                if (curDev < bestDev)
                {
                    bestDev = curDev;
                    res = std::make_pair(QPoint(sx, sy), size);
                }
            }
        }
    }
    return res;
}
