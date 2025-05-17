![](https://github.com/drxvmrz/progress_bar/blob/main/assets/anim.gif)

# The simple cross-platform progress bar for console apps!
The easy-to-use progress bar for your own terminal/console/CLI applications on c++. No need to pre-compile or pre-build anything. Just please add two [files](https://github.com/drxvmrz/progress_bar/tree/main/progress_bar) to your app's sources and include them into your code!!

# Features
- [x] Nothing to pre-build or pre-compile
- [x] Easy to customize for your own style
- [x] Only cross-platform standart libraries
- [x] Always below the real-time console outputs
- [x] It is possible to use floats (as double) for progress 
- [x] Automatic progress bar adjustment to the current progress value relative to the maximum

# Quick start

# Example
There are a simple [example](https://github.com/drxvmrz/progress_bar/tree/main/example) to demonstrate a functionality. This example implements a simulation of a process with tracking of its progress. To see how it works just follow these steps:

## 1. Download the [example](https://github.com/drxvmrz/progress_bar/tree/main/example) folder
Then add into this folder root two source files from [progress_bar](https://github.com/drxvmrz/progress_bar/tree/main/progress_bar).

## 2. Build it via CMAKE and run :)
Open your terminal in a root of downloaded ```example``` folder. Make sure that the CMAKE is specified in your ```PATH``` variable. Then invoke following commands:
```
mkdir build && cmake -B ./build && cmake --build ./build && cd ./build/Debug && ./main
```
Use ```main``` instead of ```./main``` if you're in windows command prompt.
