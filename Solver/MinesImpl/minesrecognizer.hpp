#ifndef MINERRECOGNIZER_HPP
#define MINERRECOGNIZER_HPP

#include "app_headers/app_recognizer.hpp"
#include <memory>
#include <map>
#include <cmath>
#include <QRect>

#include "clickcoordreciever.hpp"

class MinesRecognizer : public AppRecognizer
{
public:
    MinesRecognizer();
    std::unique_ptr<AppState> recognize(QImage);

    // TODO: make this all private after testing
    int getNearestCluster(int, int) const;
    std::map<QRgb, double> getColorPartition(const QImage&, QRect) const;
    int bestVariant(const QImage& c,
                    const std::vector<QImage>&) const;
    double getDiffInColors(const std::map<QRgb, double>&,
                           const std::map<QRgb, double>&) const;

    std::vector<std::vector<double> > gridSimilarity(const QImage &image,
                                                     const std::vector<QImage> &patterns,
                                                     int size) const;

    std::vector<QPoint> getUserClicks(const QImage&);

public:
    std::pair<QPoint, int> bestGridPosition(std::vector<QPoint> pts, int fieldW, int fieldH);
};

#endif // MINERRECOGNIZER_HPP
