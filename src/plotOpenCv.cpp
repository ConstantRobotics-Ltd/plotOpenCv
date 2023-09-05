#include "plotOpenCv.h"
#include "plotOpenCvVersion.h"



using namespace cr::utils;



// Linear interpolation method.
float map(float x, float in_min, float in_max, float out_min, float out_max) 
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



// This method will be used for some future features like zoom in, move along x,y etc.
void CallBackFuncMouse(int event, int x, int y, int flags, void* userdata)
{
    // window which event is captured.
    window * current_window = static_cast<window *>(userdata);

    if  ( event == cv::EVENT_LBUTTONDOWN )
    {
       // cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    }
    else if  ( event == cv::EVENT_RBUTTONDOWN )
    {
        //cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    }
    else if  ( event == cv::EVENT_MBUTTONDOWN )
    {
       // cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    }
    else if ( event == cv::EVENT_MOUSEMOVE )
    {
       // cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
    }
}



std::string window::getVersion()
{
    return PLOT_OPENCV_VERSION;
}



window::window(std::string name, int width, int height)
{
    // Create a window.
    cv::namedWindow(name,0);
    
    // remember window name for showing
    m_name=name;

    // background image (white) for window
    m_image = new cv::Mat(height, width, CV_8UC3, cv::Scalar(255, 255, 255));

    // remember window size
    m_width = width;
    m_heigth= height;

    //set the callback function for event
    cv::setMouseCallback(name, CallBackFuncMouse, this);

    //draw horizontal scale line
    cv::line(*m_image, cv::Point(0, height/2), cv::Point(width, height/2), cv::Scalar(0, 128, 128),5);


    // draw grid lines
    for (int i = 0; i<height; i += 50)
       cv::line(*m_image, cv::Point(0, i), cv::Point(width, i), cv::Scalar(0, 0, 0));

    for (int i = 0; i<width; i += 50)
       cv::line(*m_image, cv::Point(i, 0), cv::Point(i, height), cv::Scalar(0, 0, 0));
}



window::~window()
{
    delete m_image;
}



void window::renderPlot(std::vector<float>* Points, int dt, cv::Scalar color, int tickness)
{
    // Temp plot object to render graph on image.
    _2Dplot plot(Points);

    // Update current plot params with respect to current window
    plot.m_outMax = m_heigth * (plot.m_scale/100);

    // offset value is different for dataset which has negative values
    if(plot.m_inMin<0)
    {
        plot.m_offsetY = m_heigth/2 - plot.m_outMax/2;
    }

    // Temporary points to draw a line
    cv::Point currentPoint;
    cv::Point previousPoint;

    // Time period in x axis
    int t = 0;

    // Lines between points
    for(int i = 1; i<plot.m_points1d->size() ; ++i)
    {
        // line between two points
        previousPoint.x=t;
        previousPoint.y = (::map(plot.m_points1d->at(i - 1), plot.m_inMin, plot.m_inMax, plot.m_outMax, plot.m_outMin) + plot.m_offsetY);
        t+=dt;
        currentPoint.x=t;
        currentPoint.y=(::map(plot.m_points1d->at(i),plot.m_inMin,plot.m_inMax,plot.m_outMax,plot.m_outMin) + plot.m_offsetY );

        cv::line(*m_image,previousPoint ,currentPoint,color,tickness, cv::LINE_8);
    }
}

void window::renderPlot(std::vector<std::vector<float>> *Points,
    cv::Scalar color, int tickness) 
{
    // Temp plot object to render graph on image.
    _2Dplot plot(Points);

    // Update current plot params with respect to current window
    plot.m_outMax = m_heigth * (plot.m_scale / 100);

    // offset value is different for dataset which has negative values
    if (plot.m_inMin < 0)
    {
        plot.m_offsetY = m_heigth / 2 - plot.m_outMax / 2;
    }

    // Temporary points to draw a line
    cv::Point currentPoint;
    cv::Point previousPoint;

    // Time period in x axis
    int t = 0;

    // Lines between points
    for (int i = 1; i < plot.m_points2d->size(); ++i)
    {
        // line between two points
        previousPoint.x = (*plot.m_points2d)[i-1][0];
        previousPoint.y = (*plot.m_points2d)[i - 1][1];
        currentPoint.x = (*plot.m_points2d)[i][0];
        currentPoint.y = (*plot.m_points2d)[i][1];

        cv::line(*m_image, previousPoint, currentPoint, color, tickness, cv::LINE_8);
    }
}



void window::show()
{
    cv::imshow(m_name, *m_image);
}