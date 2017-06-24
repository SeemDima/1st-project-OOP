#ifndef COMMENTS_CPP
#define COMMENTS_CPP

#include <string>
#include "comments.h"


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



#endif // COMMENTS_CPP
