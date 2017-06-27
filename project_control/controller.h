#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <map>
#include "../../total_control/total_control/timestamp.h"
#include "post.h"

class Controller
{
private :
    std::multimap<Timestamp, int> _time_line;

public :
    std::vector<double> _time_distribution;

    Controller() {}

    Controller(VK::vector_comments &data_vector);

    size_t get_number_of_events() { return _time_line.size(); }

    /* Initializes multimap by time(in format of Timestamp) with comment id;
     */
    void init_timeline(VK::vector_comments &data_vector);

    /* Returns a vector[24] filled with a percentage of the amount of comments
     * at vector[0] number of comments which were wrote from 00:00 to 01:00
     * at vector[1] number of comments which were wrote from 01:00 to 02:00
     * etc...
     * at vector[23] number of comments which were wrote from 23:00 to 00:00 of the next day
     */
    void calculate_time_distribution();

    std::vector<int> find_spamer_in_post(VK::Post &post);
};

#endif // CONTROLLER_H
