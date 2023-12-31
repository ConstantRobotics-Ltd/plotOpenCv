
![logo](_static/plot_opencv_logo.png)

# **plotOpenCv C++ library**

**v1.0.1**

------


# Table of contents

- [Overview](#overview)
- [Versions](#versions)
- [plot class description](#plot-class-description)
  - [Class declaration](#class-declaration)
  - [addPlot (1D) method](#addplot-for-1d-dataset-method)
  - [addPlot (2D) method](#addplot-for-2d-dataset-method)
  - [clean method](#show-method)
  - [show method](#clean-method)

- [Example](#example)
- [Build and connect to your project](#build-and-connect-to-your-project)


# Overview

**plotOpenCv** is a C++ library developed to facilitate the visualization of 2-dimensional line charts. This library is built upon the OpenCV, providing users with a convenient and efficient tool for visualizing data through line charts. With plotOpenCv, users can effortlessly create multiple line charts within a single window and tune various chart parameters, such as line width, color, and more.

# Versions

**Table 1** - Library versions.

| Version | Release date | What's new                                                   |
| ------- | ------------ | ------------------------------------------------------------ |
| 1.0.0   | 08.09.2023   | First version.                                               |
| 1.0.1   | 18.09.2023   | Update used container for plots.                             |


# plot class description

## Class declaration

**plot** class declared in **plotOpenCv.h** file. Class declaration:

```cpp
namespace cr
{
namespace utils
{
/**
    * @brief Plot class.
*/
class Plot {
public:
    /**
    * @brief Method to get string of current library version.
    * @return String of current library version.
    */
    static std::string getVersion();
    /**
    * @brief Class constructor.
    * @param name window name.
    * @param width width of window.
    * @param height height of window.
    * @param backgroundColor color of background.
    * @param scaleLineColor color of horizontal scale line.
    */
    Plot(std::string name, int width = 1280, int height = 720, 
         cv::Scalar backgroundColor = cv::Scalar(255, 255, 255),
         cv::Scalar scaleLineColor = cv::Scalar(0, 128, 128));
    /**
    * @brief Class destructor.
    */
    ~Plot();
    /**
    * @brief Method to render plots on window.
    * @param points  vector of points for plot.
    * @param id ploting id for a line chart, can be used to update existing plot 
             or add new one.
    * @param start beginning index for plotting in given vector.
    * @param end ending index for plotting in given vector.
    * @param color printing color of plot.
    * @param thickness line tickness for plot.
    */
    template <typename T>
    void addPlot(std::vector<T>& points, int id, int start = 0, int end = 0,
                cv::Scalar color = cv::Scalar(255, 255, 255), int thickness = 1);
    /**
    * @brief Method to render plots on window.
    * @param points 2D vector of points for plot.
    * @param id ploting id for a line chart, can be used to update existing plot
             or add new one.
    * @param start beginning index for plotting in given vector.
    * @param end ending index for plotting in given vector.
    * @param color printing color of plot.
    * @param thickness line tickness for plot
    */
    template <typename T>
    void addPlot(std::vector<std::vector<T>>& points, int id, 
                int start = 0, int end = 0,
                cv::Scalar color = cv::Scalar(255, 255, 255), int thickness = 1);
    /**
    * @brief Method to clean window.
    */
    void clean();
    /**
    * @brief Method to show window.
    */
    void show();
};
}
}
```



## getVersion method

**getVersion()** method returns string of current version of **plotOpenCv**. Method declaration:

```cpp
static std::string getVersion();
```

Method can be used without **plotOpenCv** class instance:

```cpp
std::cout << "plotOpenCv class version: " << plotOpenCv::getVersion() << std::endl;
```

Console output:

```bash
plotOpenCv class version: 1.0.1
```

## addPlot (for 1D dataset) method

**addPlot(...)** method serves the purpose of incorporating a new line chart into the existing window. It either introduces a new plot if the provided id is not yet present, or updates an existing plot associated with the given identifier. Method declaration:

```cpp
void addPlot(std::vector<T> &points, int id, int start = 0, int end = 0,
            cv::Scalar color = cv::Scalar(255, 255, 255), int thickness = 1);
```

| Parameter | Value                                                        |
| --------- | ------------------------------------------------------------ |
| Points    | One dimentional vector which includes vertical points.Vector format : {y1, y2, ... }  |
| id        | Identifier for chart on a window. Provides user to update a chart or add new one.  |
| start     | Start index of plot from vector when user wants to plot a specific range from a dataset. Should be 0 for whole dataset.|
| end       | End index of plot from vector when user wants to plot a specific range from a dataset. Should be 0 for whole dataset. |
| color     | Color of chart line. |
| thickness  | Thickness of chart line.|

## addPlot (for 2D dataset) method

**addPlot(...)** method serves the purpose of incorporating a new line chart into the existing window. It either introduces a new plot if the provided id is not yet present, or updates an existing plot associated with the given identifier. Method declaration:

```cpp
void addPlot(std::vector<std::vector<T>> &points, int id, int start = 0, int end = 0,
            cv::Scalar color = cv::Scalar(255, 255, 255), int thickness = 1);
```

| Parameter | Value                                                        |
| --------- | ------------------------------------------------------------ |
| Points    | Two dimentional vector which includes vertical and horizontal points. Vector format : {{x1,y1}, {x2,y2}, ... } |
| id        | Identifier for chart on a window. Provides user to update a chart or add new one.  |
| start     | Start index of plot from vector when user wants to plot a specific range from a dataset. Should be 0 for whole dataset.|
| end       | End index of plot from vector when user wants to plot a specific range from a dataset. Should be 0 for whole dataset. |
| color     | Color of chart line. |
| tickness  | Tickness of chart line.|



**Table 2** - Supported data types.

| Supported data types |
| ---------| 
| unsigned char |
| char |
| unsigned int |
| unsigned short |
| short int |
| int |
| float |
| double |
## show method

**show()** method is responsible for displaying a window containing all the plotted line charts. Method declaration:

```cpp
void show();
```

## clean method

**clean()** method is responsible for cleaning a window containing all the plotted line charts. Method declaration:

```cpp
void clean();
```

# Example

```cpp
    plot graph("Test graph", 1280, 720,cv::Scalar(0, 128, 128) cv::Scalar(50, 50, 50));

    std::vector<float> linePoints(9000);
    std::vector<std::vector<float>> linePoints2(5000, std::vector<float>(2));

    graph.addPlot(linePoints,0, 0, 0, cv::Scalar(255,0,0), 5);
    graph.addPlot(linePoints2,1, 0, 0, cv::Scalar(0,255,0), 2);

    graph.show();
    cv::waitKey(0);
```

# Example Charts

![example_1](_static/example_1.png)
![example_2](_static/example_2.png)
![example_3](_static/example_3.png)
![example_combined](_static/example_combined.png)


# Build and connect to your project

Typical commands to build **plotOpenCv** library:

```bash
git clone https://github.com/ConstantRobotics-Ltd/plotOpenCv.git
cd plotOpenCv
mkdir build
cd build
cmake ..
make
```

If you want connect **plotOpenCv** library to your CMake project as source code you can make follow. For example, if your repository has structure:

```bash
CMakeLists.txt
src
    CMakeList.txt
    yourLib.h
    yourLib.cpp
```

You can add repository **plotOpenCv** as submodule by commands:

```bash
cd <your respository folder>
git submodule add https://github.com/ConstantRobotics-Ltd/plotOpenCv.git 3rdparty/plotOpenCv
```

In you repository folder will be created folder **3rdparty/plotOpenCv** which contains files of **plotOpenCv** repository. New structure of your repository:

```bash
CMakeLists.txt
src
    CMakeList.txt
    yourLib.h
    yourLib.cpp
3rdparty
    plotOpenCv
```

Create CMakeLists.txt file in **3rdparty** folder. CMakeLists.txt should contain:

```cmake
cmake_minimum_required(VERSION 3.13)

################################################################################
## 3RD-PARTY
## dependencies for the project
################################################################################
project(3rdparty LANGUAGES CXX)

################################################################################
## SETTINGS
## basic 3rd-party settings before use
################################################################################
# To inherit the top-level architecture when the project is used as a submodule.
SET(PARENT ${PARENT}_YOUR_PROJECT_3RDPARTY)
# Disable self-overwriting of parameters inside included subdirectories.
SET(${PARENT}_SUBMODULE_CACHE_OVERWRITE OFF CACHE BOOL "" FORCE)

################################################################################
## CONFIGURATION
## 3rd-party submodules configuration
################################################################################
SET(${PARENT}_SUBMODULE_PLOT_OPENCV                    ON  CACHE BOOL "" FORCE)
if (${PARENT}_SUBMODULE_PLOT_OPENCV)
    SET(${PARENT}_PLOT_OPENCV                          ON  CACHE BOOL "" FORCE)
endif()

################################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the 3rd-party configuration
################################################################################
if (${PARENT}_SUBMODULE_PLOT_OPENCV)
    add_subdirectory(plotOpenCv)
endif()
```

File **3rdparty/CMakeLists.txt** adds folder **plotOpenCv** to your project. Your repository new structure will be:

```bash
CMakeLists.txt
src
    CMakeList.txt
    yourLib.h
    yourLib.cpp
3rdparty
    CMakeLists.txt
    plotOpenCv
```

Next you need include folder 3rdparty in main **CMakeLists.txt** file of your repository. Add string at the end of your main **CMakeLists.txt**:

```cmake
add_subdirectory(3rdparty)
```

Next you have to include plotOpenCv library in your **src/CMakeLists.txt** file:

```cmake
target_link_libraries(${PROJECT_NAME} plotOpenCv)
```

Done!

