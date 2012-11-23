#include "minerecognizer.hpp"

#include <algorithm>
#include <limits>
#include <QColor>

MineRecognizer::MineRecognizer()
{
}

int MineRecognizer::imageCongruence(QImage image1, QImage image2)
{
    int width = std::max(image1.width(), image2.width()),
        height = std::max(image1.height(), image2.height());
    int size = width * height;
    std::vector<std::vector<int> > a(size, std::vector<int>(size, std::numeric_limits<int>::max()));

    for (int i1 = 0; i1 < image1.width(); i1++)
        for (int j1 = 0; j1 < image1.height(); j1++)
            for (int i2 = 0; i2 < image2.width(); i2++)
                for (int j2 = 0; j2 < image2.height(); j2++)
                {
                    QRgb c1 = image1.pixel(i1, j1);
                    QRgb c2 = image2.pixel(i2, j2);
                    int colorDiff = std::abs(qRed(c1)-qRed(c2)) +
                            std::abs(qGreen(c1)-qGreen(c2)) +
                            std::abs(qBlue(c1)-qBlue(c2));
                    int posDiff = std::abs(i1-i2) + std::abs(j1-j2);
                    a[i1*height + j1][i2*height + j2] = colorDiff + posDiff * 1000;
                }
    return assignmentProblemSolver(a);
}

int MineRecognizer::assignmentProblemSolver(std::vector<std::vector<int> > a)
{
    int size = a.size();
    std::vector<std::pair<int, std::pair<int, int> > > costs;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            costs.push_back(std::make_pair(a[i][j], std::make_pair(i, j)));
    sort(costs.begin(), costs.end());

    std::vector<int> usedW(size, 0), usedH(size, 0);
    int res = 0;
    int left = size;

    for (int it = 0; it < size*size && left; it++)
    {
        if (costs[it].first == std::numeric_limits<int>::max())
            break;
        int i = costs[it].second.first, j = costs[it].second.second;
        if (!usedW[i] && !usedH[j])
        {
            res += costs[it].first;
            usedW[i] = 1;
            usedH[j] = 1;
            --left;
        }
    }
    return left ? std::numeric_limits<int>::max() : res;
}
