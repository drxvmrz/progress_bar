#ifndef PROGRESS
#define PROGRESS

#include <stdarg.h>

#include <iostream>
#include <string>
#include <cmath>

namespace Progress
{
    ///////////////// DECLARATION WITH DEFAULT SETTINGS (IT MAY BE CHANGED) ////////////////////

    class ProgressBar
    {
        public:
            ProgressBar();
            ProgressBar(double maxProgress, double initProgress);

            // For setting current progress
            ProgressBar& set(double value);
            ProgressBar& operator=(double value);

            // For raising or decreasing progress
            ProgressBar& add(double value);
            ProgressBar& operator()(double value);

            // Messages output
            template<typename T>
            ProgressBar& operator<<(const T& output);

            // Manipulators overload
            ProgressBar& operator<<(std::ostream& (*func)(std::ostream&));

            // Appearance settings
            void setInitString(const std::string& str);
            void setUnitSymbol(const std::string& unit);
            void setBoxSymbols(const std::string& open, const std::string& close);
            void setProgressSymbols(const std::string& isProgress, const std::string& noProgress);

            // Get progress status
            double getCurrentProgress();
            double getMaxProgress();

            // Setting max progress in real-time
            ProgressBar& setMaxProgress(double value);
            
        private:
            /* PROGRESS STATUS */
            double maxProgress; // Max progress in units of process (not percents)
            double progress; // current progress value

            /* APPEARANCE */
            unsigned int length; // Progress-bar length in symbols of command line (or terminal)
            std::string initString;
            std::string measurementUnit;
            std::string openBoxSymbol;
            std::string closeBoxSymbol;
            std::string isProgressSymbol;
            std::string noProgressSymbol;

            /* Too tracking if progress bar in a current row now */
            bool barIsDrawed = false;

            void setStandartAppearance();

            void drawProgressBar();
            void clearString();
    };

    //////////////////// IMPLEMENTATION BELOW ///////////////////////

    ProgressBar::ProgressBar()
    {
        this->maxProgress = 100.0;
        this->progress = 0.0;

        setStandartAppearance();
    }

    ProgressBar::ProgressBar(double maxProgress, double initProgress)
    {
        if (length <= 0) throw std::out_of_range("Progress bar length should be more than zero!");
        if (maxProgress <= 0) throw std::out_of_range("Progress can not be less than or equal to zero!");
        if (maxProgress < initProgress) throw std::out_of_range("Max progress should be more than or equal to initial progress!");

        this->maxProgress = maxProgress; // Max progress in units of process (not percents)
        this->progress = initProgress; // Initial progress value (where progress-bar starts)

        setStandartAppearance();
    }

    ProgressBar& ProgressBar::set(double value)
    {
        if (value < 0) throw std::out_of_range("Progress should be more than or equal to zero");
        if (value > maxProgress) throw std::out_of_range("Progress should be less than or equal to maxProgress");

        this->progress = value;
        drawProgressBar();
        return *this;
    }

    ProgressBar& ProgressBar::operator=(double value)
    {
        return set(value);
    }

    ProgressBar& ProgressBar::add(double value)
    {
        if (progress + value < 0) throw std::out_of_range("Progress after calculation should be more than or equal to zero");
        if (progress + value > maxProgress) throw std::out_of_range("Progress after calculation should be less than or equal to maxProgress");

        this->progress += value;
        drawProgressBar();
        return *this;
    }

    ProgressBar& ProgressBar::operator()(double value)
    {
        return add(value);
    }

    template<typename T>
    ProgressBar& ProgressBar::operator<<(const T& output)
    {
        if (barIsDrawed) clearString();

        std::cout << output;
        return *this;
    }

    ProgressBar& ProgressBar::operator<<(std::ostream& (*func)(std::ostream&))
    {
        func(std::cout);
        drawProgressBar();
        return *this;
    }

    double ProgressBar::getCurrentProgress()
    {
        return this->progress;
    }

    double ProgressBar::getMaxProgress()
    {
        return this->maxProgress;
    }

    ProgressBar& ProgressBar::setMaxProgress(double value)
    {
        if (value < 0) throw std::out_of_range("Progress should be more than or equal to zero");

        this->maxProgress = value;
        drawProgressBar();
        return *this;
    }

    void ProgressBar::setInitString(const std::string& str)
    {
        this->initString = str;
    }

    void ProgressBar::setUnitSymbol(const std::string& unit)
    {
        this->measurementUnit = unit;
    }

    void ProgressBar::setBoxSymbols(const std::string& open, const std::string& close)
    {
        this->openBoxSymbol = open;
        this->closeBoxSymbol = close;
    }

    void ProgressBar::setProgressSymbols(const std::string& isProgress, const std::string& noProgress)
    {
        this->isProgressSymbol = isProgress;
        this->noProgressSymbol = noProgress;
    }
    

    void ProgressBar::setStandartAppearance()
    {
        this->length = 50;

        setInitString("Progress: ");
        setUnitSymbol("% ");
        setBoxSymbols("[", "]");
        setProgressSymbols("#", "-");
        
        // With these values of settings it will look like:
        // Progress: 40% [###########-------------------] on default
    }

    /* 
    Draws progress bar on last string of terminal 
    */
    void ProgressBar::drawProgressBar()
    {
        clearString();

        int currentProgress = floor(progress/maxProgress*100); // Progress in percents

        std::string barString = this->initString;
        barString.append(std::to_string(currentProgress));
        barString.append(measurementUnit);
        barString.append(this->openBoxSymbol);

        // Size of header "Progress % ["
        size_t headerLen = barString.size();

        // loop starts not from n = 0 due to "Progress: %d ["
        for (int n = headerLen; n < length-1; n++)
        {
            if (n <= floor((currentProgress)*(length-headerLen)/100) + headerLen)
            {
                barString.append(this->isProgressSymbol); // You can easly change the progress fill symbol
            }
            else
            {
                barString.append(this->noProgressSymbol); // Symbol of progress absence
            }
        }
        barString.append(this->closeBoxSymbol); // length-1 + ("]") = length
        std::cout << barString << std::flush;

        barIsDrawed = true;
    }

    /*
    Clears current string on terminal
    */
    void ProgressBar::clearString()
    {
        std::string blankStr;
        for (int i = 0; i < initString.size() + length; i++)
        {
            blankStr.append(" ");
        }
        std::cout << "\r" << blankStr << "\r";// << std::flush;
        barIsDrawed = false;
    }

} // namespace Progress

#endif // PROGRESS
