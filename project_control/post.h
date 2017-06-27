#ifndef POST_H
#define POST_H

#include "../VK-master/src/api.h"
#include "../../total_control/total_control/timestamp.h"

namespace VK {

#define NOT_SET -1

class Comment
{
private:
    int _id;      // identifier of comment
    int _from_id; // id of the user who wrote the comment
    size_t _date;    // data of comment in format of Unixtime
    std::string _text;

public:
    Comment();

    Comment(int from_id, const json &data);

    bool setComment(const json &data);

    /* return name of user who wrote the comment
     * in format: Surname Name
     */
    std::string getName(Client &api);

    int getId() { return _id; }

    std::string getText() { return _text;}

    size_t getDate();
    std::string getDate_as_string(); //YYYY-MM-DD HH:MM
    Timestamp getDate_as_timestamp();
};

using vector_comments = std::vector< Comment >;

class Post : public Client
{
private:

    int _owner_id = NOT_SET; /* The page owner's identifier (user or community).
                   * Note that the community identifier in the owner_id parameter must be specified with a "-"
                   * For example: https://vk.com/club128061542
                   *              "owner_id","-128061542" (AFTI group)
                   */
    int _post_id = NOT_SET;  /* Additive to the address of user or community
                   * For example: https://vk.com/club128061542?w=wall-128061542_52 ( 52 is Necessary addition)
                   *              "post_id","52"
                   */
public:
    vector_comments _vector_comments;

    Post();

    Post(int owner_id, int post_id);

    Post(size_t owner_id, bool is_community, size_t post_id);

    void set_post_info(int owner_id, int post_id);

    void set_post_info(size_t owner_id, bool is_community, size_t post_id);

    bool is_set();

    /* set vector_comments by current group_id(int) and topic_id(int) with offset(size_t).
     * Max count = 100.
     */
    bool get_comments(const size_t offset = 0,
                      const size_t count = 20);

    /* set full vector_comments by group_id(int) and topic_id(int)
     */
    bool get_all_comments();

    virtual ~Post(){ /*std::cout <<"object Post was deleted" << std::endl;*/ }
};

} //namespace VK

#endif // POST_H
