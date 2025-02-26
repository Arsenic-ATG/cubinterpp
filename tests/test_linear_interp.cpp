#include <vector>
#include <gtest/gtest.h>
#include <utility>
#include "linear_interp.hpp"

using Vector = std::vector<double>;
using Vector2 = std::vector<std::vector<double>>;
using VectorN2 = cip::VectorN<double, 2>;
using Span = std::span<const double>;
using Pr = std::pair<size_t, size_t>;



TEST(TestLinearCell1D, test_linear_cell_1d) {
    
}


TEST(TestInterp1D, test_linear_interp_1d) {
    
}


TEST(TestLinearCell2D, test_linear_cell_2d) {
    Vector x = {0, 1, 2};
    Vector y = {0, 1, 2};
    Vector2 f = {{1, 2, 2},
                 {2, 3, 3},
                 {3, 3, 4}};

    VectorN2 fvec(f);
    size_t i = 1;
    size_t j = 1;
    cip::LinearCell2D<double> cell(
        fvec.submdspan(Pr{i, i+1}, Pr{j, j+1}),
        Span(&x[i], 2),
        Span(&y[j], 2)
    );
    ASSERT_EQ(cell.eval(1, 1), 3.0);
    ASSERT_EQ(cell.eval(1, 2), 3.0);
    ASSERT_EQ(cell.eval(2, 1), 3.0);
    ASSERT_EQ(cell.eval(2, 2), 4.0);
    ASSERT_EQ(cell.eval(1.5, 1.5), 3.25);
}


TEST(TestInterp2D, test_linear_interp_2d) {
    Vector x = {0.0, 1.0, 2.0};
    Vector y = {0.0, 1.0, 2.0};
    Vector2 f = {{1.0, 2.0, 2.0},
                 {2.0, 3.0, 3.0},
                 {3.0, 3.0, 4.0}};

    cip::LinearInterp2D<double> interp2(x, y, f);
    ASSERT_EQ(interp2.eval(0.5, 0.5), 2.0);
    ASSERT_EQ(interp2.eval(1.5, 0.5), 2.75);
    ASSERT_EQ(interp2.eval(0.5, 1.0), 2.5);
    ASSERT_EQ(interp2.eval(1.0, 2.0), 3.0);


}
