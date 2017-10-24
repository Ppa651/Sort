#ifndef EDGE_H
#define EDGE_H
#include <string.h>
#include "point.h"

class edge : private point
{
private:
    point e_begin;
    point e_end;
    std::string e_label;
    std::string e_color;
public:
    edge();
    edge (edge *temp);
    edge (point begin, point end);
    edge (point begin, point end, std::string label);
    edge (point begin, point end, std::string label, std::string color);
    edge (std::string temp);
    edge &operator = (edge temp);
    edge operator = (std::string temp);
    bool checkdata (std::string temp);
    void view ();
    void write (std::fstream &file);
};

#endif // EDGE_H
