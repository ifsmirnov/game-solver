#ifndef MINESRECOGNIZERHELPER_HPP
#define MINESRECOGNIZERHELPER_HPP
#include <app_headers/app_recognizer_helper.hpp>
#include <vector>
#include <QImage>

class MinesRecognizerHelper : public AppRecognizerHelper
{
private:
    std::vector<QImage> images_;
    int width_, height_;
    bool firstMove_;
    int warmUpTurns_;
public:
    MinesRecognizerHelper();

    std::vector<QImage> getImages() const;
    void setImages(std::vector <QImage> images);

    int getWidth() const;
    void setWidth(int);

    int getHeight() const;
    void setHeight(int);

    bool isFirstMove() const;
    void setFirstMove(bool);

    int getWarmUpTurns() const;
    void setWarmUpTurns(int);
};

#endif // MINESRECOGNIZERHELPER_HPP
