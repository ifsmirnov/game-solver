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

int MinesRecognizerHelper::getWidth() const
{
    return width_;
}

void MinesRecognizerHelper::setWidth(int width)
{
    width_ = width;
}

int MinesRecognizerHelper::getHeight() const
{
    return height_;
}

void MinesRecognizerHelper::setHeight(int height)
{
    height_ = height;
}

bool MinesRecognizerHelper::isFirstMove() const
{
    return firstMove_;
}

void MinesRecognizerHelper::setFirstMove(bool firstMove)
{
    firstMove_ = firstMove;
}

int MinesRecognizerHelper::getWarmUpTurns() const
{
    return warmUpTurns_;
}

void MinesRecognizerHelper::setWarmUpTurns(int warmUpTurns)
{
    warmUpTurns_ = warmUpTurns;
}

