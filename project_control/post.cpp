#ifndef POST_CPP
#define POST_CPP

#include <ctime>
#include <string>
#include "post.h"
#include "../../total_control/total_control/timestamp.h"

VK::Comment::Comment() {}



bool VK::Comment::setComment(const json &data)
{
    if(data == nullptr){
        return false;
    }
    if(data.find("from_id") == data.end() ||
       data.find("date") == data.end() ||
       data.find("id") == data.end())
    {
        return false;
    }

    this->_from_id = data.at("from_id").get<size_t>();
    this->_date = data.at("date").get<size_t>();
    this->_id = data.at("id").get<size_t>();
    return true;
}

size_t VK::Comment::getDate()
{
    return this->_date;
}

std::string VK::Comment::getDate_as_string() //YYYY-MM-DD HH:MM
{
    size_t date = this->_date;
    std::time_t rawtime = date;
    std::tm * timeinfo = std::localtime (&rawtime);
    char buffer [256];
    std::strftime(buffer, 256, "%Y-%m-%d %H:%M", timeinfo);
    std::string time_str = buffer;
    return time_str;
}

Timestamp VK::Comment::getDate_as_timestamp()
{
    Timestamp time(this->getDate_as_string());
    return time;
}

std::string VK::Comment::getName(Client &api)
{
    params_map params = { {"user_ids",std::to_string(_from_id)} };
    json jres = api.call("users.get", params);

    Attachment::User user;

    json items = jres.at("response").get<json>();
    json item = items.begin().value();

    std::string name = item.at("first_name").get<std::string>();
    std::string surname = item.at("last_name").get<std::string>();

    return surname + " " + name;
}

void VK::Post::set_post_info(int owner_id, int post_id)
{
    this->_owner_id = owner_id;
    this->_post_id = post_id;
}
void VK::Post::set_post_info(size_t owner_id, bool is_community, size_t post_id)
{
    is_community? this->_owner_id = (-1) * int(owner_id): this->_owner_id = int(owner_id);
    this->_post_id = int(post_id);
}

VK::Post::Post() {}
VK::Post::Post(int owner_id, int post_id)
{
    this->set_post_info(owner_id, post_id);
}
VK::Post::Post(size_t owner_id, bool is_community, size_t post_id)
{
    this->set_post_info(owner_id, is_community, post_id);
}

bool VK::Post::is_set()
{
    return (this->_owner_id != NOT_SET &&
            this->_post_id != NOT_SET);
}

bool VK::Post::get_comments(const size_t offset,
                            const size_t count)
{
    if (this->_owner_id == NOT_SET ||
        this->_post_id == NOT_SET)
    {
        return false;
    }

    VK::params_map params = {
        {"owner_id",std::to_string(_owner_id)},
        {"post_id",std::to_string(_post_id)},
        {"offset", std::to_string(offset)},
        {"count", std::to_string(count)}
    };
    VK::json jres = this->call("wall.getComments", params);
    if(jres == nullptr)
    {
        return false;
    }

    if(jres.find("error") == jres.end())
    {
        VK::json items = jres.at("response").get<VK::json>().at("items").get<VK::json>();
        size_t counter = 0;
        for (VK::json::iterator it = items.begin(); it != items.end() && counter < count; ++it, ++counter)
        {
            VK::json item = it.value();
            Comment newComment;
            if(newComment.setComment(item))
            {
                this->_vector_comments.push_back(newComment);
            }
        }
    }
    return true;
}

bool VK::Post::get_all_comments()
{
    if (!this->is_set())
    {
        return false;
    }

    this->_vector_comments.clear();

    for (size_t offset = 0;;offset += 100)
    {
        if( !this->get_comments(offset, 100) )
            return false;
        if (_vector_comments.size() % 100 != 0) // if was added not 100 comments(end of the list of comments)
            break;
    }
    return true;
}


#endif // POST_CPP
