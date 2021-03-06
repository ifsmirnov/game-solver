#ifndef TRIGGERRECOGNIZER_HPP
#define TRIGGERRECOGNIZER_HPP

#include "app_headers/app_recognizer.hpp"

#include <QPoint>
#include <QColor>

#include <vector>
#include <set>

class TriggerRecognizer : public AppRecognizer
{
public:
    TriggerRecognizer();

    AppState *recognize(QImage);

private:
    std::vector<std::vector<QRgb> > getPixmap(); // maybe not const?
    void displayImage() const;
    void exploreRegion(QPoint, // that's simply a dfs
                       const std::vector<std::vector<QRgb> >&,
                       std::set<QPoint>&,
                       QRgb);
    QPoint meanPoint(const std::set<QPoint>&);
    std::vector<std::vector<std::pair<QRgb, QPoint> > > cluster(std::vector<std::pair<QRgb, QPoint> >);

    static bool clusterCmp(const std::pair<QRgb, QPoint> &lhs, const std::pair<QRgb, QPoint> &rhs);

private:
    QImage image;

    const static int minRegionSize = 20;
    const static QPoint directions[];
    const static int directionsNumber = 4;

    const static QRgb red, blue;
};

#endif // TRIGGERRECOGNIZER_HPP
