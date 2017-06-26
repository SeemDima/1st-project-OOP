#include <limits.h>
#include "gtest/gtest.h"
#include "post.h"

using namespace std;

class TestPost : public ::testing::Test
{
protected:
    static void SetUpTestCase()
    {
        foo = new VK::Post;
        if(foo->auth("dimintr", "temppass"))
        {
            cout << "Auth ok" << endl;
            cout << "Access token: " << foo->access_token() << endl << endl;
        }
        else
        {
            cout << "Auth fail" << endl;
        }
    }
    static void TearDownTestCase()
    {
        delete foo;
        foo = nullptr;
    }

    static VK::Post *foo;
};

VK::Post* TestPost::foo = nullptr;

TEST_F(TestPost, test_limited_comments)
{
    foo->set_post_info(-128061542, 52);
    ASSERT_EQ(foo->is_set(), true);
    foo->_vector_comments.clear();

    foo->get_comments();
    ASSERT_EQ(foo->_vector_comments.size(), unsigned(2));
}
TEST_F(TestPost, test_all_comments_15305)
{
    foo->set_post_info(-128061542, 52);
    ASSERT_EQ(foo->is_set(), true);

    foo->get_all_comments();
    ASSERT_EQ(foo->_vector_comments.size(), unsigned(2));
}

TEST_F(TestPost, test_all_comments_anacondaz)
{
    foo->set_post_info(-2736916, 93458);
    ASSERT_EQ(foo->is_set(), true);

    foo->get_all_comments();
    ASSERT_EQ(foo->_vector_comments.size(), unsigned(35));
}

TEST_F(TestPost, DISABLED_test_all_comments_academeg)
{
    foo->set_post_info(225756388, 677461);
    ASSERT_EQ(foo->is_set(), true);

    foo->get_all_comments();
    ASSERT_EQ(foo->_vector_comments.size(), unsigned(723));
}

TEST_F(TestPost,DISABLED_test_all_comments_povar)
{
    foo->set_post_info(-48618580, 6);
    ASSERT_EQ(foo->is_set(), true);

    foo->get_all_comments();
    ASSERT_EQ(foo->_vector_comments.size(), unsigned(180));
}

TEST_F(TestPost, time_parser)
{
    foo->set_post_info(-128061542, 52);
    ASSERT_EQ(foo->is_set(), true);

    foo->get_all_comments();
    ASSERT_EQ(foo->_vector_comments.size(), unsigned(2));

    cout << endl << "time: " << foo->_vector_comments[0].getDate_as_string() << endl;
}
