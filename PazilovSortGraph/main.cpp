#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include "point.h"
#include "edge.h"

using namespace std;

bool check(string temp);    //проверка строки (точка или ребро)
void show(vector<point> arr); //вывод вектора точек в консоле
void show(vector<edge> arr); //вывод вектора ребер в консоле
void write(vector<point> dots, string filename); //вывод вектора точек в файл
void write(vector<edge> edges, string filename); //вывод вектора ребер в файл
vector<point> createdots (string filename); //заполнение вектора точек
vector<edge> createedges(string filename);  //заполнение вектора ребер
void sort_bubble(vector<point> &arr);
void hoarasort(vector<point> &a, int first, int last);
void sort_merge(vector<point> &arr, int left, int right, int num);

int main()
{
    fstream file;
    string filename;
    cin>>filename;
    //путь к разбиваемому файлу

    vector <point> dots;
    dots=createdots (filename);     //заполнение вектора точек point.cpp

    string temp=filename;
        while(temp[temp.length()-1]!='/')
            temp.pop_back();
        temp.append("dots.txt");

    write (dots, temp); //вывод вектора точек в файл


    vector <point> dots_bubble;
    dots_bubble=createdots (filename);
    sort_bubble(dots_bubble);

    temp.clear();
    temp=filename;
        while(temp[temp.length()-1]!='/')
            temp.pop_back();
        temp.append("dots_bubble.txt");

    write (dots_bubble, temp); //вывод сортированного вектора точек в файл

    vector <point> dots_hoar;
    dots_hoar=createdots (filename);
    hoarasort(dots_hoar,0,dots_hoar.size()-1);

    temp.clear();
    temp=filename;
        while(temp[temp.length()-1]!='/')
            temp.pop_back();
        temp.append("Hoar.txt");

    write (dots_hoar, temp); //вывод сортированного вектора точек в файл

    vector <point> dots_merge;
    dots_merge=createdots (filename);
    sort_merge(dots_merge,0,dots_merge.size()-1,dots_merge.size());

    temp.clear();
    temp=filename;
        while(temp[temp.length()-1]!='/')
            temp.pop_back();
        temp.append("merge.txt");

    write (dots_merge, temp); //вывод сортированного вектора точек в файл


    //    show(dots);     //вывод вектора точек point.cpp

    vector <edge> edges;
    edges=createedges(filename);    //заполнение вектора ребер edge.cpp
    //    show(edges);    //вывод вектора ребер   edge.cpp

    temp.clear();
    temp=filename;
        while(temp[temp.length()-1]!='/')
            temp.pop_back();
        temp.append("edges.txt");

    write (edges, temp);   //вывод вектора ребер в файл

    return 0;
}

void show(vector <point> arr)
{
    cout<<"Name:"<<"\t\t\t\tColor:\n";
    for (int i=0; i<(signed int)arr.size(); i++)
        arr[i].show();
    cout<<endl;
}

void show(vector<edge> arr)
{
    for(int i=0; i<(signed int)arr.size(); i++)
        arr[i].view();
}

bool check(string temp)
{
    int begin=temp.find_first_of ('"', 1);
    int end=-1;
    end=temp.find("->", begin);
    if (end==-1) return true;
    else return false;
}

void write (vector<point> dots, string filename)
{
    fstream file;
    file.open(filename, ios_base::out | ios_base::trunc);
    if (!file.is_open()) {cout<<"Error, file not open"<<endl;}
    else
    {
        for (int i=0; i<(signed)dots.size(); i++)
            file<<dots[i].getName()<<endl
               <<dots[i].getColor()<<"\t"<<dots[i].getFontsize()<<endl<<endl;
    }
    file.close();
    cout<<"File "<<filename<<" was written..."<<endl;
}

void write (vector<edge> edges, string filename)
{
    fstream file;
    file.open(filename, ios_base::out | ios_base::trunc);
    if (!file.is_open()) {cout<<"Error, file not open"<<endl;}
    else
    {
        for (int i=0; i<(signed)edges.size(); i++)
            edges[i].write(file);
    }
    file.close();
    cout<<"File "<<filename<<" was written..."<<endl;
}

vector <point> createdots (string filename)
{
    std::vector<point> dots;
    std::fstream file;
    file.open(filename, ios_base::in);
    if (!file.is_open()) {cout<<"Error, file not open"<<endl;}
    else
    {
        char buf[101];
        file.getline(buf, 100);
        string temp=buf;
        string color="blue";
        int fontsize=5;
        while (temp.find('"')!=0)
        {
            if (temp.find("node")!=string::npos) {
                if (temp.find("color=")!=string::npos) {
                    int begin=temp.find("color=")+strlen("color=");
                    int end=temp.find(',');
                    color.clear();
                    color.append(temp, begin, end-begin );
                }
                if (temp.find("fontsize=")!=string::npos) {
                    int begin=temp.find("fontsize=")+strlen("fontsize=");
                    int end=temp.find(']');
                    string font;
                    font.append(temp, begin, end-begin);
                    fontsize=atoi(font.c_str());
                }
            }
            file.getline(buf, 100);
            temp=buf;
        }
        while (check(temp)==true)
        {
            point p(temp, color, fontsize);
            dots.insert(dots.end(), p);
            file.getline(buf, 100);
            temp=buf;
        }
    }
    file.close();
    return dots;
}

vector<edge> createedges(string filename)
{
    fstream file;
    vector<edge> edges;
    file.open(filename, ios_base::in);
    if (!file.is_open()) {cout<<"Error, file not open"<<endl;}
    else
    {
        char buf[251];
        file.getline(buf, 250);
        string temp=buf;
        while (temp.find("}")!=0)
        {
            if(check(temp)==false)
            {
                edge p(temp);
                edges.insert(edges.end(), p);
            }
            file.getline(buf, 250);
            temp=buf;
        }
    }
    file.close();
    return edges;
}

void sort_bubble(vector<point> &arr)
{

    int num=arr.size();
    for (int i=0; i<num-1; i++)
        for (int j=0; j<num-i-1; j++)
        {
            if (arr[j].getName()>arr[j+1].getName())
            {
                string temp=arr[j+1].getName();
                arr[j+1].setName(arr[j].getName());
                arr[j].setName(temp);
            }
        }
}

void hoarasort(vector <point> &a, int first, int last)
{

    int i = first, j = last;
    string tmp, x = a[(first + last) / 2].getName();

    do {
        while (a[i].getName() < x)
            i++;
        while (a[j].getName() > x)
            j--;

        if (i <= j)
        {
            if (i < j)
            {
                tmp=a[i].getName();
                a[i].setName(a[j].getName());
                a[j].setName(tmp);
            }
            i++;
            j--;
        }
    } while (i <= j);

    if (i < last)
        hoarasort(a, i, last);
    if (first < j)
        hoarasort(a, first, j);
}

void sort_merge (vector<point> &arr, int left, int right, int num)
{
    if (left==right) return;
    if (right-left==1)
    {
        if (arr[left].getName()>arr[right].getName())
        {
            string temp=arr[left].getName();
            arr[left].setName(arr[right].getName());
            arr[right].setName(temp);
        }
        return;
    }
    int mid=(left+right)/2;
    sort_merge(arr, left, mid, num);
    sort_merge(arr, mid+1, right, num);
    vector<point> arr_temp;
    arr_temp.resize(num);
    int _left=left;
    int _right=mid+1;
    int cur=0;
    while (right-left+1 != cur)
    {
        if (_left>mid)
            arr_temp[cur++].setName(arr[_right++].getName());
        else if (_right>right)
            arr_temp[cur++].setName(arr[_left++].getName());
        else if (arr[_left].getName()>arr[_right].getName())
            arr_temp[cur++].setName(arr[_right++].getName());
        else arr_temp[cur++].setName(arr[_left++].getName());
    }
    for (int i=0; i<cur; i++)
        arr[i+left].setName(arr_temp[i].getName());
}

