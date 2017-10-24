#include "edge.h"

edge::edge()
{
    point a,b;
    this->e_begin=a;
    this->e_end=b;
    this->e_label="no_label";
    this->e_color="no_color";
}

edge::edge (edge *temp)
{
    this->e_begin=temp->e_begin;
    this->e_end=temp->e_end;
    this->e_color=temp->e_color;
    this->e_label=temp->e_label;
}

edge::edge (point begin, point end)
{
    this->e_begin=begin;
    this->e_end=end;
    this->e_label="name_me_please";
    this->e_color="black";
}

edge::edge (point begin, point end, std::string label)
{
    this->e_begin=begin;
    this->e_end=end;
    this->e_label=label;
    this->e_color="black";
}

edge::edge (std::string temp)
{
    if (check(temp)==false)
    {
        std::string str;
        int begin, end;
        if ( temp.find("];")!=std::string::npos)
        {
            begin=temp.find("color=");
            end=temp.find(',', begin);
            begin=begin+strlen("color=");
            str.append(temp, begin, end-begin);
//            e_begin.setColor(str);
//            e_end.setColor(str);
            e_color.clear();
            e_color=str;
            begin=temp.find("label=");
            begin=begin+strlen("label=")+1;
            end=temp.find("];");
            end--;
            e_label.clear();
            e_label.append(temp, begin, end-begin);

        }
        begin=temp.find_first_of('"', 0);
        end=temp.find_first_of('"', begin+1);
        str.clear();
        str.append (temp, begin+1, end-begin-1);
        this->e_begin=str;
        begin=temp.find_first_of('"', end+1);
        end=temp.find_first_of('"', begin+1);
        str.clear();
        str.append(temp, begin+1, end-begin-1);
        this->e_end=str;
    }
}

edge &edge::operator =(edge temp)
{
    this->e_begin=temp.e_begin;
    this->e_end=temp.e_end;
    this->e_label=temp.e_label;
    return *this;
}

edge edge::operator =(std::string temp)
{
    if (check(temp)==false)
    {
        std::string str;
        int begin, end;
        if ( temp.find("];")!=std::string::npos)
        {
            begin=temp.find("color=");
            end=temp.find(',', begin);
            begin=begin+strlen("color=");
            str.append(temp, begin, end-begin);
            e_begin.setColor(str);
            e_end.setColor(str);
            e_color.clear();
            e_color=str;
            begin=temp.find("label=");
            begin=begin+strlen("label=")+1;
            end=temp.find(']');
            end--;
            e_label.clear();
            e_label.append(temp, begin, end-begin);

        }
        begin=temp.find_first_of('"', 0);
        end=temp.find_first_of('"', begin+1);
        str.clear();
        str.append (temp, begin+1, end-begin-1);
        this->e_begin=str;
        begin=temp.find_first_of('"', end+1);
        end=temp.find_first_of('"', begin+1);
        str.clear();
        str.append(temp, begin+1, end-begin-1);
        this->e_end=str;
    }
    return *this;
}

void edge::view()
{
    std::cout<<this->e_begin.getName()<<" -> "<<this->e_end.getName()
            <<std::endl<<this->e_color<<" \t"<<this->e_label<<std::endl<<std::endl
              ;
}

void edge::write(std::fstream &file)
{
    file<<"Begin: "<<this->e_begin.getName()<<std::endl<<"End: "
       <<this->e_end.getName()<<std::endl<<"Label: "<<this->e_label
      <<std::endl<<"Color: "<<this->e_color<<std::endl<<std::endl;
}

