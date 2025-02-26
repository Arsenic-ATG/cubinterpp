#include <vector>
#include <gtest/gtest.h>
#include <utility>
#include "vectorn.hpp"

using Vector = std::vector<double>;
using Vector2 = std::vector<std::vector<double>>;
using Vector3 = std::vector<std::vector<std::vector<double>>>;

template<class T>unsigned char identify(T&& v) {return v;}


TEST(TestVectorN, test_vectorn)
{
    Vector3 nvec1 = {
                    {
                        {1, 2, 3},
                        {4, 5, 6}
                        },
                    {
                        {7, 8, 9},
                        {10, 11, 12}
                        }
                    };
    cip::VectorN<double, 3> vec1(nvec1);
    ASSERT_EQ(vec1(0, 0, 0), 1);
    ASSERT_EQ(vec1(1, 1, 2), 12);

    Vector2 nvec2 = {{1, 2, 3}, {4, 5, 6}};
    cip::VectorN<double, 2> vec2(nvec2);
    ASSERT_EQ(vec2(0, 1), 2);
    vec2(0, 1) = 10;
    ASSERT_EQ(vec2(0, 1), 10);
    
    Vector nvec3 = {1, 2, 3, 4, 5};
    cip::VectorN<double, 1> vec3(nvec3);
    ASSERT_EQ(vec3(0), 1);
    ASSERT_EQ(vec3(1), 2);
    ASSERT_EQ(vec3(2), 3);
    ASSERT_EQ(vec3(3), 4);
    ASSERT_EQ(vec3(4), 5);
}

using Pair = std::pair<std::size_t, std::size_t>;
using Mdspan = std::mdspan<const double, std::dextents<std::size_t, 2>, std::layout_stride>;

TEST(TestSubmdspan, test_submdspan)
{
    Vector vec = {1, 2, 2, 2, 3, 3, 3, 3, 4};

    //Mdspan33 view = std::mdspan<const double, std::extents<std::size_t, 3, 3>>(vec.data(), 3, 3);
    Mdspan view = std::mdspan(vec.data(), 3, 3);
    ASSERT_EQ(view(0, 0), 1);
    ASSERT_EQ(view(1, 1), 3);

    Mdspan subview = std::submdspan(view, Pair{0, 2}, Pair{0, 2});
    ASSERT_EQ(subview(0, 0), 1);
    ASSERT_EQ(subview(0, 1), 2);
    ASSERT_EQ(subview(0, 2), 2);
    ASSERT_EQ(subview(1, 0), 2);
    ASSERT_EQ(subview(1, 1), 3);
    ASSERT_EQ(subview(1, 2), 3);
    ASSERT_EQ(subview(2, 0), 3);
    ASSERT_EQ(subview(2, 1), 3);
    ASSERT_EQ(subview(2, 2), 4);
}


TEST(TestVectorNMdspan, test_vectorn_mdspan)
{
    Vector2 vec2 = {
                   {1, 2, 2},
                   {2, 3, 3},
                   {3, 3, 4}
                   };

    cip::VectorN<double, 2> nvec2(vec2);

    auto view2 = nvec2.get_mdspan();
    ASSERT_EQ(view2(0, 0), 1);
    ASSERT_EQ(view2(1, 1), 3);

    auto subview2 = nvec2.submdspan(Pair{0, 1}, Pair{0, 1});
    ASSERT_EQ(subview2(0, 0), 1);
    ASSERT_EQ(subview2(0, 1), 2);
    ASSERT_EQ(subview2(1, 0), 2);
    ASSERT_EQ(subview2(1, 1), 3);

    Vector3 vec3 = {
                    {
                        {1, 2, 3},
                        {4, 5, 6}
                        },
                    {
                        {7, 8, 9},
                        {10, 11, 12}
                        }
                    };
    cip::VectorN<double, 3> nvec3(vec3);

    auto view3 = nvec3.get_mdspan();
    ASSERT_EQ(view3(0, 0, 0), 1);
    ASSERT_EQ(view3(1, 1, 2), 12);

    auto subview3 = nvec3.submdspan(Pair{1, 2}, Pair{0, 1}, Pair{1, 2});
    ASSERT_EQ(subview3(0, 0, 0), 8);
    ASSERT_EQ(subview3(0, 0, 1), 9);
    ASSERT_EQ(subview3(0, 1, 0), 11);
    ASSERT_EQ(subview3(0, 1, 1), 12);
}
