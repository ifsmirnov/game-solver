#ifndef MINERRECOGNIZER_HPP
#define MINERRECOGNIZER_HPP

#include "app_headers/app_recognizer.hpp"
#include <memory>
#include <map>
#include <cmath>

class MinesRecognizer : public AppRecognizer
{
public:
    MinesRecognizer();
    std::unique_ptr<AppState> recognize(QImage);
    std::map<QRgb, double> getColorPartition(const QImage&) const;
    int bestVariant(const QImage& c,const std::vector<QImage>&) const;
    double getDiffInColors(const std::map<QRgb, double>&, const std::map<QRgb, double>&) const;
};

#endif // MINERRECOGNIZER_HPP
