#ifndef COMMENTS_H
#define COMMENTS_H

#include "../VK-master/src/api.h"

namespace VK {

class Comments : public Client
{
private:
    struct vector_comments
    {

    };

public:
    Comments();

    /* return vector_comments by group_id(int) and topic_id(int) with offset(size_t).
     * Max count = 100.
     */
    vector_comments get_comments(const int group_id,
                                 const int topic_id,
                                 const size_t offset = 0,
                                 const size_t count = 20);

    /* return full vector_comments by group_id(int) and topic_id(int) with offset(size_t)
     */
    vector_comments get_all_comments(const int group_id,
                                     const int topic_id);


//    std::string get_chat_title(const int chat_id);

//    std::string get_username(const int user_id);

//    /* if count == 0 return all attachments */
//    template<typename T> std::vector<T> get_attachments(const int chat_id, const size_t count = 0);

    virtual ~Comments(){}
};

} //namespace VK

#endif // COMMENTS_H
