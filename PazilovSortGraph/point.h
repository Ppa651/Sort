#ifndef POINT_H
#define POINT_H
#include <string>
#include <iostream>
#include <fstream>


class point
{
protected:
    std::string s_name;
    std::string s_color;
    int s_fontsize;
public:
    point();
    point (std::string temp);
    point (std::string temp, std::string color);
    point (std::string temp, int fontsize);
    point (std::string temp, std::string color, int fontsize);
    point (point *temp);
    point &operator = (point temp);
    point &operator = (std::string temp);
    std::string getName();
    std::string getColor();
    int getFontsize();
    point setName (std::string temp);
    point setColor (std::string temp);
    point setFontsize (int fontsize);
    bool check(std::string temp);
    void show (int size);
    void show ();

};

#endif // POINT_H
