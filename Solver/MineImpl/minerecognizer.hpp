#ifndef MINERECOGNIZER_HPP
#define MINERECOGNIZER_HPP

#include <vector>

#include "app_headers/app_recognizer.hpp"

class MineRecognizer : public AppRecognizer
{
public:
    MineRecognizer();

    // virtual std::unique_ptr<AppState> recognize(QImage image);

public: // TODO: make private after testing
    static int imageCongruence(QImage image1, QImage image2);
    static int assignmentProblemSolver(std::vector<std::vector<int> > a);

};

#endif // MINERECOGNIZER_HPP
