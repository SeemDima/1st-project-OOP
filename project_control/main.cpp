#include <stdio.h>
#include <iostream>
#include "curl/curl.h"
#include "../VK-master/src/api.h"

using namespace std;

struct Record
{
    size_t from_id;
    size_t date;

    std::string getName(VK::Client &api) //return name of user: Name Surname
    {
        VK::params_map params = { {"user_ids",to_string(from_id)} };
        VK::json jres = api.call("users.get", params);

        VK::Attachment::User user;
        //user.parse(jres.at("response").get<VK::json>().at("first_name").get<string>());

        VK::json items = jres.at("response").get<VK::json>();
        VK::json item = items.begin().value();

        string name = item.at("first_name").get<string>();
        string surname = item.at("last_name").get<string>();

        return name + " " + surname;
    }
};

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cout << "[access_token] login pass" << endl;
        return 1;
    }

    string access_token = argv[1];

    VK::Client api;
    if(api.auth("", "", access_token))
    {
        cout << "Auth ok" << endl;
        cout << "Access token: " << api.access_token() << endl << endl;
    }
    else
    {
        cout << "Auth fail" << endl;
    }

    int offset = 0;

    VK::params_map params = {
        {"owner_id","-128061542"},
        {"post_id","52"},
        {"offset", std::to_string(offset)}
    };
    VK::json jres = api.call("wall.getComments", params);
    if(jres == nullptr)
    {
        return 1;
    }

    vector<Record> vecComments;

    if(jres.find("error") == jres.end())
    {
        VK::json items = jres.at("response").get<VK::json>().at("items").get<VK::json>();

        for (VK::json::iterator it = items.begin(); it != items.end(); ++it)
        {
            VK::json item = it.value();
            Record newRecord;
            if(item.find("from_id") == item.end())
                continue;

            newRecord.from_id = item.at("from_id").get<size_t>();

            if(item.find("date") == item.end())
                continue;
            newRecord.date = item.at("date").get<size_t>();

            vecComments.push_back(newRecord);
        }
    }

    cout << vecComments.size() << endl;

    cout << vecComments[0].getName(api);

    return 0;
}


//int offset = 0;

//VK::params_map params = {
//    {"group_id","club128061542"},
//    {"topic_id","128061542_52"},
//    {"offset", std::to_string(offset)}
//};

//VK::json jres = VK::call("messages.getDialogs", params);
//if(jres == nullptr){
//    return std::move(res);
//}

//if(jres.find("error") == jres.end()){

//    json items = jres.at("response").get<json>().at("items").get<json>();

//    for (json::iterator it = items.begin(); it != items.end(); ++it) {
//        json item = it.value();
//        if(item.find("message") == item.end())
//            continue;
//        item = item.at("message").get<json>();
//        VK::DialogInfo dialog;
//        if(dialog.parse(item)){

//            if(dialog.title.empty()){
//                dialog.title = (dialog.is_chat) ?
//                            get_chat_title(dialog.chat_id) : get_username(dialog.chat_id);
//            }

//            res.push_back(std::move(dialog));
//        }
//    }
//}
