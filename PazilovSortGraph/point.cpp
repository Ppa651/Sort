#include "point.h"

point::point()
{
    this->s_color="no_color";
    this->s_fontsize=0;
    this->s_name="no_name";
}

point::point (std::string temp)
{
    if (this->check(temp)==true)
    {
        int begin=temp.find_first_of('"', 0);
        int end=temp.find_first_of('"', begin+1);
        s_name.clear();
        s_name.append(temp, begin+1, end-begin-1);
        s_color="blue";
        s_fontsize=10;
    }
    else std::cerr<<"Error, it's not a dot (constructor)"<<std::endl;
}

point::point (std::string temp, std::string color)
{
    if (this->check(temp)==true)
    {
        int begin=temp.find_first_of('"', 0);
        int end=temp.find_first_of('"', begin+1);
        s_name.clear();
        s_name.append(temp, begin+1, end-begin-1);
        s_color=color;
        s_fontsize=10;
    }
    else std::cerr<<"Error, it's not a dot (constructor)"<<std::endl;
}

point::point (std::string temp, int fontsize)
{
    if (this->check(temp)==true)
    {
        int begin=temp.find_first_of('"', 0);
        int end=temp.find_first_of('"', begin+1);
        s_name.clear();
        s_name.append(temp, begin+1, end-begin-1);
        s_color="blue";
        s_fontsize=fontsize;
    }
    else std::cerr<<"Error, it's not a dot (constructor)"<<std::endl;
}

point::point (std::string temp, std::string color, int fontsize)
{
    if (this->check(temp)==true)
    {
        int begin=temp.find_first_of('"', 0);
        int end=temp.find_first_of('"', begin+1);
        s_name.clear();
        s_name.append(temp, begin+1, end-begin-1);
        s_color=color;
        s_fontsize=fontsize;
    }
    else std::cerr<<"Error, it's not a dot (constructor)"<<std::endl;
}

point::point (point *temp)
{
    this->s_name=temp->s_name;
    this->s_color=temp->s_color;
    this->s_fontsize=temp->s_fontsize;
}

bool point::check(std::string temp)
{
    int begin=temp.find_first_of ('"', 1);
    int end=-1;
    end=temp.find("->", begin);
    if (end==-1) return true;
    else return false;
}

point& point::operator =(point temp)
{
    this->s_name=temp.s_name;
    this->s_color=temp.s_color;
    this->s_fontsize=temp.s_fontsize;
    return *this;
}

point& point::operator =(std::string temp)
{
    if (check(temp)==true)
    {
        int begin=temp.find_first_of('"', 0);
        int end=temp.find_first_of('"', begin+1);
        s_name.clear();
        s_name.append(temp, begin+1, end-begin-1);
        if (s_color=="no_color") s_color="blue";
        if (s_fontsize==0)s_fontsize=10;
    }
    else std::cerr<<"Error, it's not a dot (operator =)"<<std::endl;
    return *this;
}

std::string point::getName()
{return s_name;}

std::string point::getColor()
{return s_color;}

int point::getFontsize()
{return s_fontsize;}

point point::setName(std::__cxx11::string temp)
{
    this->s_name=temp;
    return this;
}

point point::setColor(std::__cxx11::string temp)
{
    this->s_color=temp;
    return this;
}

point point::setFontsize(int fontsize)
{
    this->s_fontsize=fontsize;
    return this;
}

void point::show(int size)
{
    std::cout<<"Name:"<<" \t\t\tColor:\n";
    for (int i=0; i<size; i++)
    {
        std::cout<<this[i].s_name<<" \t"<<this[i].s_color
                <<" \t"<<this[i].s_fontsize<<std::endl;
    }
}

void point::show()
{
    std::cout<<this->s_name<<" \t\t\t"<<this->s_color<<
               " \t"<<this->s_fontsize<<std::endl;
}


