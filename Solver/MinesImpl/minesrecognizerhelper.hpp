#ifndef MINESRECOGNIZERHELPER_HPP
#define MINESRECOGNIZERHELPER_HPP
#include <app_headers/app_recognizer_helper.hpp>
#include <vector>
#include <QImage>

class MinesRecognizerHelper
{
private:
    std::vector<QImage> images_;
public:
    MinesRecognizerHelper();

    std::vector<QImage> getImages() const;

    void setImages(std::vector <QImage> images);
};

#endif // MINESRECOGNIZERHELPER_HPP
