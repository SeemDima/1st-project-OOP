#include "controller.h"
void Controller::init_timeline(VK::vector_comments &data_vector)
{
    for (size_t it = 0; it < data_vector.size(); ++it)
    {
        this->_time_line.insert({data_vector[it].getDate_as_timestamp(), it});
    }
}
Controller::Controller(VK::vector_comments &data_vector)
{
    this->init_timeline(data_vector);
}

using MyMM_iterator = std::multimap<Timestamp, int>::iterator;

void Controller::calculate_time_distribution()
{
    if (_time_line.size() == 0)
    {
        return ;
    }
    _time_distribution.clear();
    _time_distribution.resize(24);
    //time_distribution.reserve(24);

    for (MyMM_iterator b_it = _time_line.begin(), e_it = _time_line.end();
         b_it != _time_line.end();
         b_it = e_it)
    {
        Timestamp theKey = (*b_it).first;
        std::pair<MyMM_iterator, MyMM_iterator> keyRange = _time_line.equal_range(theKey);

        // Iterate over all map elements with key == theKey
        for (e_it = keyRange.first;  e_it != keyRange.second;  ++e_it)
        {
            unsigned hour = e_it->first.hour;
            if (hour < 24)
            {
                _time_distribution[hour]++;
            }
            else
            {
                _time_distribution.clear();
                return;
            }
        }
    }
    size_t comments_amount = _time_line.size();
    for (auto &it: _time_distribution)
    {
        it = (it / double(comments_amount)) * 100;
    }

}

std::vector<int> Controller::find_spamer_in_post(VK::Post &post)
{
    std::multimap<int, std::string> A;


    std::vector<int> empty_vec;
    return empty_vec;
}
