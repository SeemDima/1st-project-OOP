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
    /* Vector designed to fill the number of events by the clock */
    std::vector<double> _time_distribution;

    Controller() {}

    /* Constructor for controlling comments
     */
    Controller(VK::vector_comments &data_vector);

    /* Returns amount of events at time_line
     */
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

    /* Returns a vector<int> filled with users_id who wrote more than critical_amount same comments
     */
    std::vector<int> find_spamer_in_post(VK::Post &post, size_t critical_amount);
};

#endif // CONTROLLER_H
