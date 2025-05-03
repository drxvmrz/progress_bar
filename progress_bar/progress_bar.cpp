#include <progress_bar.hpp>

ProgressBar::ProgressBar(double maxProgress, double initProgress, int lenght)
{
    this->lenght = lenght; // Progress-bar lengt in symbols of command line (or terminal)
    this->maxProgress = maxProgress; // Max progress in units of process (not percents)
    this->progress = initProgress; // Initial progress value (where progress-bar starts)
}

/*
Draws progress bar on last string of terminal
*/
void ProgressBar::__drawProgressBar()
{
    int currentProgress = floor(progress/maxProgress*100); // Progress in percents

    string barString = "Progress: ";
    barString.append(to_string(currentProgress));
    barString.append("% [");

    // Size of header "Progress % ["
    size_t headerLen = barString.size();

    // loop starts not from n = 0 due to "Progress: %d ["
    for (int n = headerLen; n < lenght-1; n++)
    {
        if (n <= floor((currentProgress)*(lenght-headerLen)/100) + headerLen)
        {
            barString.append("#"); // You can easly change the progress fill symbol
        }
        else
        {
            barString.append("-"); // Symbol of progress absence
        }
    }
    barString.append("]"); // length + ("]") = length

    // It will look like: Progress: 40% [###########-------------------]
    cout << barString << flush;
}

/*
Increases progress 
Message input is equal to c-language standart output printf("...", ...)

raiseProgress: The number by which progress is increased
*/ 
void ProgressBar::printWithProgress(double raiseProgress, const char* format, ...)
{
    va_list args;
    va_start(args, format);

    char buf[255];
    int res = vsnprintf(buf, sizeof(buf), format, args);
    if (res < 0 || static_cast<size_t>(res) >= sizeof(buf)) 
    {
        cerr << "Buffer not so big! IO ERROR!" << endl;
        return;
    }

    string output = string(buf);
    va_end(args);

    string blankStr;
    for (int i = 0; i < lenght; i++)
    {
        blankStr.append(" ");
    }
    cout << "\r" << blankStr << "\r" << output << endl;

    this->progress += raiseProgress;
    this->__drawProgressBar();
}

/*
Increases progress without message output
*/
void ProgressBar::increaseProgress(double raiseProgress)
{
    string blankStr;
    for (int i = 0; i < lenght; i++)
    {
        blankStr.append(" ");
    }
    cout << "\r" << blankStr << "\r" << flush;

    this->progress += raiseProgress;
    this->__drawProgressBar();
}

