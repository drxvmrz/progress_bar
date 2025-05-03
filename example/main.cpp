/**
 * Just an example how to use library
 */

// Windows
#ifdef _WIN32
#include <Windows.h>
#define SLEEP(x) Sleep(x)
#else
// UNIX and UNIX-Like
#include <unistd.h>
#define SLEEP(x) usleep(x)
#endif

#include <progress_bar.hpp>

int main()
{
    // Create the progress bar
    // Maximum progress = 100.0 (default, optional)
    // Intial progress (value where progress-bar starts) = 0.0 (default, optional)
    // Lenght in terminal symbols = 50 (default, optional)
    // !!! Progress is not equal to percents of progress, it's an absolute value !!!
    ProgressBar bar{100.0, 0.0, 50};

    // Simulation of some processing
    for (int i = 0; i < bar.maxProgress; i++)
    {
        if (i % 2 == 0)
        {
            // Printing some message in terminal when i is even number
            bar.printWithProgress(1.0, "Progress added! Now it = %.3f", bar.progress);
        }
        else
        {
            // When i is odd it only increase progress without any messages
            bar.increaseProgress(1.0);
        }
        // Timer for simulation of any long process
        SLEEP(10);
    }

    return 0;
}