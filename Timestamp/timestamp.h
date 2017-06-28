#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <string>
#include <istream>

enum Month { JANUARY = 1,
             FEBRUARY = 2,
             MARCH = 3,
             APRIL = 4,
             MAY = 5,
             JUNE = 6,
             JULY = 7,
             AUGUST = 8,
             SEPTEMBER = 9,
             OCTOBER = 10,
             NOVEMBER = 11,
             DECEMBER = 12};

//#define JANUARY 1
//#define FEBRUARY 2
//#define MARCH 3
//#define APRIL 4
//#define MAY 5
//#define JUNE 6
//#define JULY 7
//#define AUGUST 8
//#define SEPTEMBER 9
//#define OCTOBER 10
//#define NOVEMBER 11
//#define DECEMBER 12

struct Timestamp //1997-12-31 10:35
{
    unsigned year = 0;
    unsigned month = 0;
    unsigned day = 0;
    unsigned hour = 0;
    unsigned minute = 0;

    Timestamp() {}

    Timestamp(std::string data_str);

    Timestamp(unsigned a, unsigned b, unsigned c, unsigned d,unsigned e);

    Timestamp(int a, int b, int c, int d,int e);


    operator long long() const;

    bool operator==(const Timestamp &AnotherTs);

    bool operator!=(const Timestamp &AnotherTs);

    bool operator<=(const Timestamp &AnotherTs);

    bool operator<(const Timestamp &AnotherTs);

    bool operator>(const Timestamp &AnotherTs);

    Timestamp operator++(int);
};

std::string tstos(Timestamp &ts);

std::istream &operator>>(std::istream &is, Timestamp &ts);

struct TimeRecord
{
    Timestamp startTs;
    Timestamp endTs;
    std::string person_id;
    int place_id;
};
#endif // TIMESTAMP_H
