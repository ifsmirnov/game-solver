#include "minesrecognizerhelper.hpp"

MinesRecognizerHelper::MinesRecognizerHelper()
{
}


std::vector<QImage> MinesRecognizerHelper::getImages() const
{
    return images_;
}

void MinesRecognizerHelper::setImages(std::vector <QImage> images)
{
    images_ = images;
}
