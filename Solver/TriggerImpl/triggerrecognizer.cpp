#include "triggerrecognizer.hpp"

#include "renderarea.hpp"

#include <QApplication>

#include <iostream>
#include <vector>

const QPoint TriggerRecognizer::directions[] = {QPoint(1, 0),
                                                QPoint(0, 1),
                                                QPoint(-1, 0),
                                                QPoint(0, -1)
                                               };
const QRgb TriggerRecognizer::blue = QColor(Qt::blue).rgb();
const QRgb TriggerRecognizer::red = QColor(Qt::red).rgb();

TriggerRecognizer::TriggerRecognizer()
{
}

std::vector<std::vector<QRgb> > TriggerRecognizer::getPixmap() // QPixmap?
{
    std::vector<std::vector<QRgb> > pixmap(image.width(), std::vector<QRgb>(image.height(), 0));
    for (int i = 0; i < image.width(); i++)
    {
        for (int j = 0; j < image.height(); j++)
        {
            pixmap[i][j] = image.pixel(i, j);
        }
    }
    return pixmap;
}

void TriggerRecognizer::displayImage() const
{
    std::cerr << "displayImage" << std::endl;

    QWidget *activeWindow = QApplication::activeWindow();

    RenderArea *renderArea = new RenderArea;
    QObject::connect(activeWindow,
                     SIGNAL(closed()),
                     renderArea,
                     SLOT(close())
                     );
    renderArea->setImage(image);

    renderArea->show();
    renderArea->update();

    std::cerr << "Recognizer: created new RenderArea and displayed it" << std::endl;
}

bool operator< (const QPoint& a, const QPoint &b)
{
    return a.x() < b.x() || (a.x() == b.x() && a.y() < b.y());
}

void TriggerRecognizer::exploreRegion(QPoint point,
                                      const std::vector<std::vector<QRgb> > &pixmap,
                                      std::set<QPoint> &visited,
                                      QRgb color)
{
    for (int i = 0; i < directionsNumber; i++)
    {
        QPoint nextPoint = point + directions[i];
        if (QRect(0, 0, pixmap.size()-1, pixmap[0].size()-1).contains(nextPoint) &&
                pixmap[nextPoint.x()][nextPoint.y()] == color &&
                !visited.count(nextPoint))
        {
            visited.insert(nextPoint);
            exploreRegion(nextPoint, pixmap, visited, color);
        }
    }
}

QPoint TriggerRecognizer::meanPoint(const std::set<QPoint> &points)
{
    QPointF sum(0, 0);
    for (auto i: points)
        sum += i;
    sum /= points.size();
    return QPoint(sum.x(), sum.y());
}

AppState* TriggerRecognizer::recognize(QImage image_)
{
    image = image_;

    auto pixmap = getPixmap();

    std::set<QPoint> visited;
    std::vector<std::pair<QRgb, QPoint> > cells;
    for (int i = 0; i < image.width(); i++)
        for (int j = 0; j < image.height(); j++)
        {
            if ( (pixmap[i][j] == red || pixmap[i][j] == blue) && !visited.count(QPoint(i, j)))
            {
                std::set<QPoint> tmp;
                exploreRegion(QPoint(i, j), pixmap, tmp, pixmap[i][j]);
                if ((int)tmp.size() >= minRegionSize)
                {
                    cells.push_back(std::make_pair(pixmap[i][j], meanPoint(tmp)));
                    visited.insert(tmp.begin(), tmp.end());
                }
            }
        }

    std::cerr << "game consists of " << cells.size() << " cells" << std::endl;

    QCursor cursor;

    for (auto i: cells)
    {
        std::cerr << (i.first == blue ? "Blue" : "Red") << std::endl << std::flush;
        cursor.setPos(i.second);
        cursor.pos();
        sleep(1);
    }

    return new AppState(new AppInternalState, new AppExternalState);
}
