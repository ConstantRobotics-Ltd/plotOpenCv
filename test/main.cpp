#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include "PlotOpenCv.h"

using namespace cr::utils;

int main()
{
    std::cout << "plotOpenCv v" << Plot::getVersion() << " test" << std::endl;

    // Create plotting window.
    Plot graph("Test graph", 1280, 640, PlotColor(50, 50, 50));

    // Prepare 1d vector for plotting.
    std::vector<double> linePoints(9000);
    double degree = 0.0;
    for(int i =0 ; i < 5000; i++ )
    {
        linePoints.at(i) = sin(degree);
        degree += 0.01;
    }
    for (int i = 5000; i < 7000; i++)
    {
        linePoints.at(i) = (0.3f);
    }
    double temp=0;
    for(int i = 7000; i<9000; i++)
    {
        temp += 0.00015f;
        linePoints.at(i) = 0.3f - temp;
    }

    // Prepare 1D vector for plotting.
    std::vector<float> linePoints2(1000);
    degree=0;
    for(int i =0 ; i < 1000; i++ )
    {
        linePoints2.at(i) = static_cast<float>(degree * degree);
        degree += 0.5;
    }

    std::vector<int> linePoints3(1000);

    for (int i = 0; i < 1000; i++)
    {
        linePoints3.at(i) = i;
    }

    // Put charts on graph.
    graph.addPlot(linePoints, 0, 0, 0, PlotColor(255, 0, 0), 1);
    graph.addPlot(linePoints2, 1, 0, 0, PlotColor(0, 255, 0), 1);
    graph.addPlot(linePoints3, 2, 0, 0, PlotColor(0, 0, 255), 1);

    // Prepare 2d vector for plotting.
    std::vector<std::vector<double>> linePoints4(9000, std::vector<double>(2));

    // Generate the data for sin wave and store it in the vector.
    int time = 0;
    for (int i = 0; i < 9000; ++i)
    {
        linePoints4[i][0] = time;
        linePoints4[i][1] = sin(2.0 * 3.14 * 10 * time);
        time += 1;
    }

    // Put chart on graph.
    graph.addPlot(linePoints4, 3, 0, 5000, PlotColor(0, 0, 255), 2);

    // Show graph and wait.
    graph.show();
    cv::waitKey(0);
    return 0;
}