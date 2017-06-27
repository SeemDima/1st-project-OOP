#include <limits.h>
#include "gtest/gtest.h"
#include "post.h"
#include "controller.h"

using namespace std;

class TestPost : public ::testing::Test
{
protected:
    static void SetUpTestCase()
    {
        foo = new VK::Post;
        if(foo->auth("********", "********"))
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

    EXPECT_EQ(foo->_vector_comments[0].getText(), "Источник: http://www.phys.nsu.ru/ok03/Manuals.html");
}

TEST_F(TestPost, test_all_comments_anacondaz)
{
    foo->set_post_info(-2736916, 93458);
    ASSERT_EQ(foo->is_set(), true);

    foo->get_all_comments();
    ASSERT_EQ(foo->_vector_comments.size(), unsigned(35));
}

TEST_F(TestPost, test_all_comments_academeg)
{
    foo->set_post_info(225756388, 677461);
    ASSERT_EQ(foo->is_set(), true);

    foo->get_all_comments();
    ASSERT_EQ(foo->_vector_comments.size(), unsigned(722));
}

TEST_F(TestPost, test_all_comments_povar)
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

TEST_F(TestPost, controller_time_distribution_1st)
{
    foo->set_post_info(-128061542, 52);
    ASSERT_EQ(foo->is_set(), true);

    foo->get_all_comments();
    ASSERT_EQ(foo->_vector_comments.size(), unsigned(2));

    Controller controller(foo->_vector_comments);
    ASSERT_EQ(controller.get_number_of_events(), unsigned(2));

    controller.calculate_time_distribution();

    EXPECT_NEAR(controller._time_distribution[11], 50, 0.1);
    EXPECT_NEAR(controller._time_distribution[22], 50, 0.1);
}

TEST_F(TestPost, controller_time_distribution_2nd)
{
    foo->set_post_info(225756388, 677461);
    ASSERT_EQ(foo->is_set(), true);

    foo->get_all_comments();
    ASSERT_EQ(foo->_vector_comments.size(), unsigned(722));

    Controller controller(foo->_vector_comments);
    ASSERT_EQ(controller.get_number_of_events(), unsigned(722));

    controller.calculate_time_distribution();

    EXPECT_NEAR(controller._time_distribution[18], 0, 0.1);

    double count = 0;

    for (size_t it=0; it < controller._time_distribution.size(); ++it)
    {
        count += controller._time_distribution[it];
        it < 10? cout << "0": cout << "";
        cout << it << ":00 - ";
        it + 1 < 10? cout << "0" << it + 1: cout << it + 1;
        cout << ":00 -> " << controller._time_distribution[it] << endl;
    }
    EXPECT_NEAR(count, 100, 0.1);
}
TEST_F(TestPost, test_controller_spamer)
{
    foo->set_post_info(-22541491, 483806);
    ASSERT_EQ(foo->is_set(), true);

    foo->get_all_comments();

    Controller controller;
    vector<int> A = controller.find_spamer_in_post(*foo, size_t(6));
    ASSERT_EQ(A.size(), size_t(1));
    EXPECT_EQ(A[0] ,11782003);
}

