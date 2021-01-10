#include "svgfile.h"
#include <iostream>
#include <sstream>

const std::string svgHeader =
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
    "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" ";

const std::string svgEnding = "\n\n</svg>\n";

/// Effets "Boule en relief", voir données à la fin de ce fichier
extern const std::string svgBallGradients;

std::set<std::string> Svgfile::s_openfiles;

Svgfile::Svgfile(std::string _filename, int _width, int _height) :
    m_filename{_filename}, m_width{_width}, m_height{_height}
{

    std::cout << "Opening SVG output file : "
              << m_filename << std::endl;

    if ( s_openfiles.count(m_filename) )
        throw std::runtime_error( "File " + m_filename + " already open !" );

    m_ostrm.open(m_filename);
    s_openfiles.insert(m_filename);

    if (!m_ostrm)
    {
        std::cout << "Problem opening " << m_filename << std::endl;
        throw std::runtime_error("Could not open file " + m_filename );
    }

    std::cout << "OK" << std::endl;

    // Writing the header into the SVG file
    m_ostrm << svgHeader;
    m_ostrm << "width=\"" << m_width << "\" height=\"" << m_height << "\">\n\n";
}

Svgfile::~Svgfile()
{
    // Writing the ending into the SVG file
    m_ostrm << svgEnding;

    // Removing this file from the list of open files
    s_openfiles.erase(m_filename);

    // No need to explicitly close the ofstream object (automatic upon destruction)
}

// Helper templated function
template<typename T>
std::string attrib(std::string name, T val)
{
    std::ostringstream oss;
    oss << name << "=\"" << val << "\" ";
    return oss.str();
}

void Svgfile::addDisk(double x, double y, double r, std::string color)
{
    m_ostrm << "<circle "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r)
            << attrib("fill", color )
            << "/>\n";
}

void Svgfile::addEllipse(double cx, double cy, double rx, double ry, std::string color)
{
    m_ostrm << "<ellipse "
            << attrib("cx", cx)
            << attrib("cy", cy)
            << attrib("rx",  rx)
            << attrib("ry",  ry)
            << attrib("fill", color )
            << "/>\n";
}

/// <polygon points="200,10 250,190 160,210" style="fill:lime;stroke:purple;stroke-width:1" />



void Svgfile::addRect(Pos pos1, Pos pos2, Pos pos3, Pos pos4, std::string colorFill)
{
        m_ostrm << "<polygon points=\" "
            << pos1.x << "," << pos1.y << " "
            << pos2.x << "," << pos2.y << " "
            << pos3.x << "," << pos3.y<< " "
            << pos4.x << "," << pos4.y
            << "\" style=\"fill:" << colorFill
            << "\" />\n";
}


std::string Svgfile::makeRGB(int r, int g, int b, float a)
{
    std::ostringstream oss;
    oss << "rgba(" << r << "," << g << "," << b << "," << a << ")";
    return oss.str();
}
