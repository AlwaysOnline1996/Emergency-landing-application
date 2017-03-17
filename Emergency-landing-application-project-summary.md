# Emergency-landing application project summary

### 1.Description

A program called **mayday** that prints a list of airports and runways that are closets to a given location.The program will lists airports that have runways longer than a given minimum length.It will also print the distance from the given location to the airport . In a fictional scenario,a pilot who encounters an emergency situation would use program to get a list of the nearest landing options .The pilot would enter his/her current location as latitude and longitude(in degree decimal) as well as the minimum runway length needed to land(in ft.) 

### 2.Program specification

The mayday program will read the current position (latitude and longitude in degrees decimal)
and minimum runway length from the command line arguments.
The program should then open and read the text files, create appropriate Facility and
Runway objects, and store them using STL vectors. The facilities should then be sorted in order
of proximity to the current location using the STL sort algorithm and a function object
Closer defined in the file Closer.h . The program should then examine each facility in
order of proximity and search for runways that belong to this facility (as identified by the site
number) and have a length larger than or equal to the minimum runway length required. This
search will use the STL find_if algorithm and a function object SiteNumber defined in
the file SiteNumber.h . For each facility (up to a maximum of 10 facilities) the program will
print the type, code, name, and distance from the current position, followed by a list of runways
having a sufficient length.

以上是源文档给出的程序简述。描述了一个实现飞机在实现**紧急降落**过程中，帮助飞行员快速查找距离最近且符合降落条件的机场设施的程序。现在把实现过程中遇到的问题做一个小节。

#### 一.零碎点回顾：

1. 类中常成员变量的初始化必须在初始化列表内进行，初始化列表里可以调用常成员函数用于初始化常成员变量。例：

```c++
class Facility
{
  public:
    Facility(std::string s);
    std::string site_number(void) const;
    std::string type(void) const;
    std::string code(void) const;
    std::string name(void) const;
    double latitude(void) const;
    double longitude(void) const;
    double distance(double lat, double lon) const;
  private:
    const std::string site_number_;
    const std::string type_;
    const std::string code_;
    const std::string name_;
    const double longitude_, latitude_;
    double convert_latitude(std::string s) const;
    double convert_longitude(std::string s) const;
};
```

对于常成员变量longitude_ 可初始化为：

```C++
Facility::Facility(std::string s):latitude_(convert_latitude(s)),longitude_(convert_longitude(s)),site_number_(s.substr(0,10)),type_(s.substr(11,13)),code_(s.substr(24,4)),name_(s.substr(130,50)){
}
```

2. STL 库函数使用： 

   1. > std::sort 
      >
      > 这里程序限定了使用STL 库函数并给出了照如下方式实现排序：
      >
      > ```c++
      > sort(facalities.begin(),facilities.end(),Closer(current_latitude,currentu_longitude));
      > // vector<Facility*> facilities;`
      > ```
      >
      > 查阅官方文档，给出的Compare 自定义比较函数，看似都没有传参数进去。而程序中，传入了两个从命令行接收到的经纬度数值作为参数，用来同facilities 对象内的经纬度进行计算，然后根据计算出的数值来给vector<Facility*>排序。官方文档中，没有类似写法，Google了一遍也没找到类似的实现。辗转反侧最后这样实现解决了问题，talk is cheap ,show you the code
      >
      > ```c++
      > // Created by ZengTong on 17-3-15.
      > //
      > #ifndef CLOSER_H
      > #define CLOSER_H
      >
      > #include "Facility.h"
      > class Closer
      > {
      > public:
      >     Closer(const double cur_lat,const double cur_lon);
      >     bool operator() (Facility* &a,Facility* &b);
      > private:
      >     const double cur_la;
      >     const double cur_lo;
      > };
      > #endif //CLOSER_H
      >
      > // Close.cpp implmentation as follow
      >
      > #include <vector>
      > #include "Closer.h"
      > Closer::Closer(const double cur_lat,const double cur_lon):cur_la(cur_lat),cur_lo(cur_lon){
      > }
      > bool Closer::operator() (Facility* &a,Facility* &b){
      >     return a->distance(cur_la,cur_lo) < b->distance(cur_la,cur_lo);
      > }
      > ```
      >
      > 从上面的实现可以看出来，sort里的Compare 是个函数指针，sort执行时回调Compare并传入待排序的变量，这一步不需要我们手动写，函数自动执行。将Closer写成类构造函数，参数传入facilities，并 对() 进行重载。代码可以看出来，Closer(current_latitude,currentu_longitude) 实际是调用了类的()重载函数，而facilities由构造函数传进去了。所以可以实现经纬度距离的计算，并由()重载函数实现比较函数。参见：[函数指针](https://zh.wikipedia.org/wiki/%E5%87%BD%E6%95%B0%E6%8C%87%E9%92%88)
      >
      > ​

   2. > ```c++
      > InputIterator find_if(InputIterator first,InputIterator last,UnaryPredicate pred);
      > ```
      >
      > 这个函数内的自定义条件函数用法与sort()函数的自定义比较函数类似，不做赘述咯。
      >
      > ```c++
      > //
      > // Created by zengtong on 17-3-15.
      > //
      > #ifndef SITENUMBER_H
      > #define SITENUMBER_H
      >
      > #include "Facility.h"
      > #include "Runway.h"
      > class SiteNumber
      > {
      > public:
      >     SiteNumber(Facility* &f, const int le);
      >     bool operator() (Runway* &r);
      > private:
      >     const int min_runway_length;
      >     const Facility* f;
      > };
      > #endif //SITENUMBER_H
      >
      > for(vector<Runway*>::iterator it =runways.begin(); it != runways.end() && *it != NULL;it++){
      >         it = find_if(it,runways.end(),SiteNumber(a,min_runway_length));
      >   		if(*it == NULL)
      >             break;
      >         else
      >           good_runways.push_back(*it);
      > }
      > ```