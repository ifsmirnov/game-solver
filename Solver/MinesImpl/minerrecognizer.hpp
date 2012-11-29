#ifndef MINERRECOGNIZER_HPP
#define MINERRECOGNIZER_HPP

#include "app_headers/app_recognizer.hpp"
#include <memory>
#include <map>
#include <cmath>

class MinerRecognizer : public AppRecognizer
{
public:
    MinerRecognizer();
    std::unique_ptr<AppState> recognize(QImage);
    std::map<QRgb, double> getColorPartition(QImage);
    int bestVariant(QImage, std::vector<QImage>);
    double getDiffInColors(std::map<QRgb, double>, std::map<QRgb, double>);
};

#endif // MINERRECOGNIZER_HPP
