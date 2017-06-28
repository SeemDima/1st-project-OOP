#include "timestamp.h"

Timestamp::Timestamp(std::string data_str)     // YYYY-MM-DD hh:mm
{
    try
    {
        this->year = stoi(data_str.substr(0, 4));
        this->month = stoi(data_str.substr(5, 7));
        this->day = stoi(data_str.substr(8, 9));
        this->hour = stoi(data_str.substr(11, 12));
        this->minute = stoi(data_str.substr(14, 15));
    }
    catch(...)
    {
    }
}

Timestamp::Timestamp(unsigned a, unsigned b, unsigned c, unsigned d,unsigned e)
{
    this->year = a;
    this->month = b;
    this->day = c;
    this->hour = d;
    this->minute = e;
}

Timestamp::Timestamp(int a, int b, int c, int d,int e)
{
    this->year = a;
    this->month = b;
    this->day = c;
    this->hour = d;
    this->minute = e;
}
std::string tstos(Timestamp &ts)
{
    std::string ts_str;
    ts_str += std::to_string(ts.year) + "-";
    ts_str += std::to_string(ts.month) + "-";
    ts_str += std::to_string(ts.day) + " ";
    ts_str += std::to_string(ts.hour) + ":";
    ts_str += std::to_string(ts.minute);
    return ts_str;
}


Timestamp::operator long long() const
{
    long long ts = (long long)this->year  * 100000000 +
                   (long long)this->month * 1000000 +
                   (long long)this->day   * 10000 +
                   (long long)this->hour  * 100 +
                   (long long)this->minute;
    return ts;
}

bool Timestamp::operator==(const Timestamp &AnotherTs)
{
    return ((long long)(*this) == (long long)AnotherTs);
}

bool Timestamp::operator!=(const Timestamp &AnotherTs)
{
    return (long long)(*this) != (long long)AnotherTs;
}

bool Timestamp::operator<(const Timestamp &AnotherTs)
{
    return ((long long)(*this) - (long long)AnotherTs) < 0;
}

bool Timestamp::operator<=(const Timestamp &AnotherTs)
{
    return ((long long)(*this) - (long long)AnotherTs) <= 0;
}

bool Timestamp::operator>(const Timestamp &AnotherTs)
{
    return ((long long)(*this) - (long long)AnotherTs) > 0;
}

std::istream &operator>>(std::istream &is, Timestamp &ts)
{
    is >> ts.year;
    is.ignore(1) >> ts.month;
    is.ignore(1) >> ts.day;
    is.ignore(1) >> ts.hour;
    is.ignore(1) >> ts.minute;
    return is;
}

Timestamp Timestamp::operator++(int)
{
    this->minute++;
    if (this->minute == 60)
    {
        this->minute = 0;
        this->hour ++;
        if (this->hour == 24)
        {
            this->hour = 0;
            this->day++;

            if (this->day == 29 && this->year % 4 != 0 && this->month == FEBRUARY)
            {
                this->day = 1;
                this->month++;
            }
            if (this->day == 30 && this->year % 4 == 0 && this->month == FEBRUARY)
            {
                this->day = 1;
                this->month++;
            }
            if (this->day == 31 && (this->month == APRIL ||
                                 this->month == JUNE ||
                                 this->month == SEPTEMBER ||
                                 this->month == NOVEMBER))
            {
                this->day = 1;
                this->month++;
            }
            if (this->day == 32 && (this->month == JANUARY ||
                                     this->month == MARCH ||
                                     this->month == MAY ||
                                     this->month == JULY ||
                                     this->month == AUGUST ||
                                     this->month == OCTOBER ||
                                     this->month == DECEMBER))
            {
                this->day = 1;
                this->month++;
            }
            if (this->month == 13)
            {
                this->month = 1;
                this->year++;
            }
        }
    }
    return *this;
}

Timestamp SetTimeRecord(std::string &data_str)
{
    Timestamp ts;
    try
    {
        ts.year = stoi(data_str.substr(0, 4));
        ts.month = stoi(data_str.substr(5, 7));
        ts.day = stoi(data_str.substr(8, 9));
        ts.hour = stoi(data_str.substr(11, 12));
        ts.minute = stoi(data_str.substr(14, 15));
    }
    catch(...)
    {
        return ts; //need to improve
    }
    return ts;
}
