#ifndef PROGRESS
#define PROGRESS

#include <stdarg.h>

#include <iostream>
#include <string>

using namespace std;

class ProgressBar
{
    public:
        double maxProgress; // Max progress in units of process (not percents)
        double progress; // current progress value

        int lenght; // Progress-bar lengt in symbols of command line (or terminal)

        // It should be a default parameters of progress bar
        ProgressBar(double maxProgress = 100.0, double initProgress = 0.0, int lenght = 50);

        void printWithProgress(double raiseProgress, const char* format, ...);
        void increaseProgress(double raiseProgress);
        
    private:
        void __drawProgressBar();
};

#endif
