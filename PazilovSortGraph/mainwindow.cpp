#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include "point.h"
#include <QTime>
#include <QVector>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->b_Open,SIGNAL(clicked(bool)),this,SLOT(openFile()));
    connect(ui->b_Sort,SIGNAL(clicked(bool)),this,SLOT(sortDot()));
    connect(ui->b_Find,SIGNAL(clicked(bool)),this,SLOT(findName()));
}

bool check(string temp);    //проверка строки (точка или ребро)
void write(vector<point> dots, string filename); //вывод вектора точек в файл
vector<point> createdots (string filename); //заполнение вектора точек
void sort_bubble(vector<point> &arr);
void hoarasort(vector<point> &arr, int first, int last);
void sort_merge(vector<point> &arr, int left, int right, int num);
int search_binary(vector <point> &arr, int left, int right, string key);

void MainWindow::sortDot()
{

    string filename;
    filename+=ui->le_path->text().toStdString();
    vector <point> dots;

    string temp=filename;
    while(temp[temp.length()-1]!='/')
        temp.pop_back();
    temp.append("dots.txt");

    dots=createdots (filename);     //заполнение вектора точек point.cpp
    write (dots, temp); //вывод вектора точек в файл

    if(ui->rbBubble->isChecked())
    {
        vector <point> dots_bubble;
        dots_bubble=createdots (filename);
        QTime time;
        time.start();
        sort_bubble(dots_bubble);
        ui->l_bubble->setText(QString::number(time.elapsed()));

        string temp=filename;
        while(temp[temp.length()-1]!='/')
            temp.pop_back();
        temp.append("dotsSortOfBubble.txt");


        write (dots_bubble, temp); //вывод сортированного вектора точек в файл
    }

    else if(ui->rbHoar->isChecked())
    {
        vector <point> dots_hoar;
        dots_hoar=createdots (filename);
        QTime time;
        time.start();
        hoarasort(dots_hoar,0,dots_hoar.size()-1);
        ui->l_hoar->setText(QString::number(time.elapsed()));


        string temp=filename;
        while(temp[temp.length()-1]!='/')
            temp.pop_back();
        temp.append("dotsSortOfHoar.txt");

        write (dots_hoar, temp); //вывод сортированного вектора точек в файл
    }

    else if(ui->rbMerge->isChecked())
    {
        vector <point> dots_merge;
        dots_merge=createdots (filename);
        QTime time;
        time.start();
        sort_merge(dots_merge,0,dots_merge.size()-1,dots_merge.size());
        ui->l_merge->setText(QString::number(time.elapsed()));

        string temp=filename;
        while(temp[temp.length()-1]!='/')
            temp.pop_back();
        temp.append("dotsSortOfMerge.txt");

        write (dots_merge, temp); //вывод сортированного вектора точек в файл
    }

}

void MainWindow::openFile()
{
    string filename;
    filename+=ui->le_path->text().toStdString();

    if(ui->rbBubble->isChecked())
    {
        string temp=filename;
        while(temp[temp.length()-1]!='/')
            temp.pop_back();

        temp.append("dotsSortOfBubble.txt");
        string sys="notepad.exe ";
        sys.append(temp);
        const char* tmp=sys.c_str();
        system(tmp);
    }
    else if(ui->rbHoar->isChecked())
    {
        string temp=filename;
        while(temp[temp.length()-1]!='/')
            temp.pop_back();

        temp.append("dotsSortOfHoar.txt");
        string sys="notepad.exe ";
        sys.append(temp);
        const char* tmp=sys.c_str();
        system(tmp);

    }

    else if(ui->rbMerge->isChecked())
    {
        string temp=filename;
        while(temp[temp.length()-1]!='/')
            temp.pop_back();

        temp.append("dotsSortOfMerge.txt");
        string sys="notepad.exe ";
        sys.append(temp);
        const char* tmp=sys.c_str();
        system(tmp);
    }
}

void MainWindow::findName()
{
    string filename;
    filename+=ui->le_path->text().toStdString();
    vector <point> dots;

    string temp=filename;

    dots=createdots (filename);     //заполнение вектора точек point.cpp

    sort_bubble(dots);


    string s_name=ui->le_name->text().toStdString();
    int result=search_binary(dots,0,dots.size()-1,s_name);
    ui->l_name->setText(QString::number(result));
}

MainWindow::~MainWindow()
{
    delete ui;
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

bool check(string temp)
{
    int begin=temp.find_first_of ('"', 1);
    int end=-1;
    end=temp.find("->", begin);
    if (end==-1) return true;
    else return false;
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

void hoarasort(vector <point> &arr, int first, int last)
{

    int i = first, j = last;
    string tmp, x = arr[(first + last) / 2].getName();

    do {
        while (arr[i].getName() < x)
            i++;
        while (arr[j].getName() > x)
            j--;

        if (i <= j)
        {
            if (i < j)
            {
                tmp=arr[i].getName();
                arr[i].setName(arr[j].getName());
                arr[j].setName(tmp);
            }
            i++;
            j--;
        }
    } while (i <= j);

    if (i < last)
        hoarasort(arr, i, last);
    if (first < j)
        hoarasort(arr, first, j);
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

int search_binary(vector <point> &arr, int left, int right, string key)
{
    int midd = 0;
    while (1)
    {
        midd = (left + right) / 2;

        if (key < arr[midd].getName())       // если искомое меньше значения в ячейке
            right = midd - 1;      // смещаем правую границу поиска
        else if (key > arr[midd].getName())  // если искомое больше значения в ячейке
            left = midd + 1;	   // смещаем левую границу поиска
        else                       // иначе (значения равны)
            return midd;           // функция возвращает индекс ячейки

        if (left > right)          // если границы сомкнулись
            return -1;
    }
}
