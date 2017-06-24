#ifndef COMMENTS_H
#define COMMENTS_H

#include "../VK-master/src/api.h"

namespace VK {

#define NOT_SET -1

class Comment
{
private:
    size_t _id;      // identifier of comment
    size_t _from_id; // id of the user who wrote the comment
    size_t _date;    // data of comment in format of Unixtime
    Client &_api;    //

public:
    Comment(Client &api);

    Comment(Client &api, const json &data);

    setComment(const json &data);
    /* return name of user who wrote the comment
     * in format: Surname Name
     */
    std::string getName(Client &api);
};

using vector_comments = std::vector< Comment >;

class Post : public Client
{
private:

    int _owner_id = NOT_SET; /* The page owner's identifier (user or community).
                   * Note that the community identifier in the owner_id parameter must be specified with a "-"
                   * For example: "owner_id","-128061542" (AFTI group)
                   */
    int _post_id = NOT_SET;  /* Additive to the address of user or community
                   * For example: https://vk.com/club128061542?w=wall-128061542_52 ( 52 is Necessary addition)
                   */

public:
    Post();

    Post(int owner_id, int post_id);

    Post(size_t owner_id, bool is_community, size_t post_id);

    void set_post_info(int owner_id, int post_id);

    void set_post_info(size_t owner_id, bool is_community, size_t post_id);

    /* set vector_comments by current group_id(int) and topic_id(int) with offset(size_t).
     * Max count = 100.
     */
    vector_comments get_comments(const size_t offset = 0,
                                 const size_t count = 20);

    /* return full vector_comments by group_id(int) and topic_id(int) with offset(size_t)
     */
    vector_comments get_all_comments();


//    std::string get_chat_title(const int chat_id);

//    std::string get_username(const int user_id);

//    /* if count == 0 return all attachments */
//    template<typename T> std::vector<T> get_attachments(const int chat_id, const size_t count = 0);

    virtual ~Post(){}
};

} //namespace VK

#endif // COMMENTS_H
