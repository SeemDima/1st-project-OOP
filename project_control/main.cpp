#include <stdio.h>
#include <iostream>
#include "curl/curl.h"
#include "../VK-master/src/api.h"

using namespace std;

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
        cout << api.call("account.getInfo");
        //cout << api.call("wall.post", "owner_id=12345&message=Test");
    }
    else
    {
        cout << "Auth fail" << endl;
    }
}
