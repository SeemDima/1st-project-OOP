#include <stdio.h>
#include <iostream>

#include "curl/curl.h"
#include "../VK-master/src/api.h"
#include "post.h"
#include "../gtest/googletest/include/gtest/gtest.h"

using namespace std;

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
