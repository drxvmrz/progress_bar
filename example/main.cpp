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
    // Maximum progress = 100.0
    // Intial progress (value where progress-bar starts) = 0.0
    // Length in terminal symbols = 50
    
    Progress::ProgressBar bar{100.0, 0.0};

    // Simulation of some process
    for (int i = 0; i < round(bar.getMaxProgress()); i++)
    {
        if (i % 2 == 0)
        {
            // Printing some message in terminal when i is even number
            bar(1.0) << "Now progress is " << bar.getCurrentProgress() << " percent" << std::endl; 
        }
        else
        {
            // When i is odd it only increase progress without any messages
            bar(1.0);
        }
        // Timer for simulation of any long process
        SLEEP(400);
    }

    return 0;
}