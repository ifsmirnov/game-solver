#include "solver.hpp"

#include <QtGui>
#include <QGridLayout>

#include <iostream>
#include <cmath>

#include <app_headers/app_state.hpp>

Solver::Solver(QWidget *parent) :
    QWidget(parent)
{
    // how to call basic constructor from some other one?
    createLayout();
}

Solver::Solver(AppFactory *factory_, SysEventsEmulator *emulator_, QWidget *parent) :
    QWidget(parent)
{
    createLayout();
    emulator = std::unique_ptr<SysEventsEmulator>(emulator_);
    setApp(factory_);
}

void Solver::createLayout()
{
    QGridLayout *layout = new QGridLayout;
    renderArea = std::unique_ptr<RenderArea>(new RenderArea);
    layout->addWidget(renderArea.get());
    if(QWidget::layout() != 0)
    {
        delete(QWidget::layout());
    }
    setLayout(layout);
}

void Solver::setApp(AppFactory *factory)
{
    executor = std::unique_ptr<AppActionExecutor>(factory->createExecutor());
    interactor = std::unique_ptr<AppInteractor>(factory->createInteractor());
    recognizer = std::unique_ptr<AppRecognizer>(factory->createRecognizer());
}

void Solver::setSysEventsEmulator(SysEventsEmulator *emulator_)
{
    emulator = std::unique_ptr<SysEventsEmulator>(emulator_);
}

std::map<QRgb, double> Solver::getColorPartition(QImage image)
{
    std::map<QRgb, double> tmp;
    for (int i = 0; i < image.width(); i++)
    {
        for (int j = 0; j < image.height(); j++)
        {
            QRgb temp = image.pixel(i, j);
            if (tmp.find(temp) != tmp.end())
            {
                double x = tmp.find(temp)->second;
                tmp.erase(tmp.find(temp));
                tmp.insert(std::pair<QRgb, double>(temp, x + 1));
            }
            else
            {
                tmp.insert(std::pair<QRgb, double>(temp, 1));
            }
        }
    }
    std::map<QRgb, double> result;
    for (std::map<QRgb, double>::iterator it = tmp.begin(); it != tmp.end(); it++)
    {
        result.insert(std::pair<QRgb, double>(it->first, it->second/double(image.width() * image.height())));
    }
    return result;
}

double Solver::getDiffInColors(std::map<QRgb, double> x, std::map<QRgb, double> y)
{
    std::map<QRgb, double>::iterator xIt, yIt;
    xIt = x.begin();
    yIt = y.begin();
    double result = 0;
    while(xIt != x.end()  ||  yIt != y.end())
    {
        if (xIt == x.end()  ||  (yIt != y.end()  &&  yIt->first < xIt->first))
        {
            result += yIt->second;
            yIt++;
        }
        else if (yIt == y.end()  ||  (xIt != x.end()  &&  xIt->first < yIt->first))
        {
            result += xIt->second;
            xIt++;
        }
        else
        {
            result += fabs(xIt->second - yIt->second);
            xIt++;
            yIt++;
        }
    }
    return result;
}

int Solver::bestVariant(QImage image, std::vector<QImage> variants)
{
    int ans = -1;
    double diff = 100;
    std::map<QRgb, double> colors = getColorPartition(image);
    for (int i = 0; i < variants.size(); i++)
    {
        double temp = getDiffInColors(colors, getColorPartition(variants[i]));
        std::cout << diff << ' ' << temp << std::endl;
        if (temp < diff)
        {
            diff = temp;
            ans = i;
        }
    }
    return ans;
}

QImage Solver::printScreen()
{
    return QPixmap::grabWindow(QApplication::desktop()->winId()).toImage();
}

void Solver::makeMove()
{
    std::cerr << "Making move" << std::endl;

    std::unique_ptr<AppState> recognizerResult = recognizer->recognize(printScreen());
    AppInternalState *internalState = recognizerResult->internalState();
    AppExternalState *externalState = recognizerResult->externalState();

    std::unique_ptr<AppAction> action(interactor->nextAction(internalState));

    if (action->hasAction())
    {
        std::cerr << "executing..." << std::endl;
        executor->execute(externalState, action.get(), emulator.get());
    }
}

void Solver::mousePressEvent(QMouseEvent *)
{
    makeMove();
    /*
    QImage image = printScreen();
    std::cerr << "pre img size:" << image.width() << " " << image.height() << std::endl;
    renderArea->setImage(image);
    update();
    std::cerr << "image set" << std::endl;
    */
}




void Solver::closeEvent(QCloseEvent *event)
{
    std::vector <QImage> variants;
    QImage image = printScreen();
    for (int i = 0; i < 10; i++)
    {
        variants.push_back(printScreen());
    }
    std::cout << bestVariant(image, variants) << std::endl;
    delete(QWidget::layout());
    emit closed();
    event->accept();
}
