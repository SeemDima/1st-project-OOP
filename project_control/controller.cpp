#include "controller.h"
#include <cmath>

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

using MapTs_Int_iterator = std::multimap<Timestamp, int>::iterator;

void Controller::calculate_time_distribution()
{
    if (_time_line.size() == 0)
    {
        return ;
    }
    _time_distribution.clear();
    _time_distribution.resize(24);
    //time_distribution.reserve(24);

    for (std::multimap<Timestamp, int>::iterator b_it = _time_line.begin(), e_it = _time_line.end();
         b_it != _time_line.end();
         b_it = e_it)
    {
        Timestamp theKey = (*b_it).first;
        std::pair<MapTs_Int_iterator, MapTs_Int_iterator> keyRange = _time_line.equal_range(theKey);

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

using MapInt_String_iterator = std::multimap<int, std::string>::iterator;


std::vector<int> Controller::find_spamer_in_post(VK::Post &post, size_t critical_amount)
{
    std::multimap<int, std::string> A; // user_id, text of comment
    std::vector<int> ouput_vec;
    for (size_t it = 0; it < post._vector_comments.size(); ++it)
    {
        A.insert({post._vector_comments[it].getFromId(), post._vector_comments[it].getText()});
    }
    for (MapInt_String_iterator b_it = A.begin();  b_it !=  A.end();)
    {
        int theKey = (*b_it).first;
        std::pair<MapInt_String_iterator, MapInt_String_iterator> keyRange = A.equal_range(theKey);

        // user with this id wrote less comment then crit amount
        size_t dist = size_t(abs(std::distance(keyRange.first,keyRange.second)));
        if (dist < critical_amount)
        {
            std::advance (b_it,dist);
            continue;
        }

        std::string comment_text = keyRange.first->second;
        size_t count = 0;
        MapInt_String_iterator e_it;
        for (e_it = keyRange.first++;  e_it != keyRange.second;  ++e_it)
        {
            if (e_it->second == comment_text)
                ++count;
        }
        if (count >= critical_amount)
            ouput_vec.push_back(keyRange.first->first);

        std::advance (b_it, dist);
        count = 0;

    }
    return ouput_vec;
}
