//
// Created by Bard on 04/04/2024.
//

#include <bardrix/dimension4.h>

class dimension4_test : public bardrix::dimension4 {
public:
    dimension4_test() : dimension4_test(0, 0, 0, 0) {}

    dimension4_test(double x, double y, double z, double w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    std::ostream& print(std::ostream& os) const override {
        return os << "dimension3_test: (" << x << ", " << y << ", " << z << ", " << w << ")";
    }
};

/// \brief Test the addition of two dimension4
TEST(dimension4, add) {
    dimension4_test dim4(1, 2, 3, 4);
    dimension4_test dim4_positive(5, 6, 7, 8);

    dimension4_test result = dim4 + dim4_positive;

    EXPECT_EQ(result, dimension4_test(6, 8, 10, 12));
}

/// \brief Test the addition of a dimension4 by a scalar
TEST(dimension4, add_scalar) {
    dimension4_test dim4{1, 2, 3, 4};
    double scalar = 2;

    dimension4_test dim4_result = dim4 + scalar;
    dimension4_test dim4_result_inverse = scalar + dim4;

    // Test the addition of a dimension4 by a scalar
    ASSERT_EQ(dim4_result, dimension4_test(3, 4, 5, 6));
    ASSERT_EQ(dim4_result_inverse, dimension4_test(3, 4, 5, 6));
}

/// \brief Test the degenerate cases of the addition of a dimension4 by a scalar, using the + operator
TEST(dimension4, add_degenerate) {
    dimension4_test dim4{1, 2, 3, 4};
    dimension4_test dim4_zero{0, 0, 0, 0};
    dimension4_test dim4_negative{-4, -5, -6, -7};

    double zero_scalar = 0;
    double negative_scalar = -4;

    dimension4_test dim4_result = dim4 + dim4_zero;
    ASSERT_EQ(dim4_result, dimension4_test(1, 2, 3, 4));

    dim4_result = dim4 + dim4_negative;
    ASSERT_EQ(dim4_result, dimension4_test(-3, -3, -3, -3));

    dim4_result = dim4 + zero_scalar;
    ASSERT_EQ(dim4_result, dimension4_test(1, 2, 3, 4));

    dim4_result = dim4 + negative_scalar;
    ASSERT_EQ(dim4_result, dimension4_test(-3, -2, -1, 0));
}

/// \brief Test the subtraction of two dimension4
TEST(dimension4, subtract) {
    dimension4_test dim4(1, 2, 3, 4);
    dimension4_test dim4_positive(5, 6, 7, 8);

    dimension4_test result = dim4 - dim4_positive;

    EXPECT_EQ(result, dimension4_test(-4, -4, -4, -4));
}

/// \brief Test the subtraction of a dimension4 by a scalar
TEST(dimension4, subtract_scalar) {
    dimension4_test dim4{1, 2, 3, 4};
    double scalar = 2;

    dimension4_test dim4_result = dim4 - scalar;
    dimension4_test dim4_result_inverse = scalar - dim4;

    // Test the subtraction of a dimension4 by a scalar
    ASSERT_EQ(dim4_result, dimension4_test(-1, 0, 1, 2));
    ASSERT_EQ(dim4_result_inverse, dimension4_test(1, 0, -1, -2));
}

/// \brief Test the degenerate cases of the subtraction of a dimension4 by a scalar, using the - operator
TEST(dimension4, subtract_degenerate) {
    dimension4_test dim4{1, 2, 3, 4};
    dimension4_test dim4_zero{0, 0, 0, 0};
    dimension4_test dim4_negative{-4, -5, -6, -7};

    double zero_scalar = 0;
    double negative_scalar = -4;

    dimension4_test dim4_result = dim4 - dim4_zero;
    ASSERT_EQ(dim4_result, dimension4_test(1, 2, 3, 4));

    dim4_result = dim4 - dim4_negative;
    ASSERT_EQ(dim4_result, dimension4_test(5, 7, 9, 11));

    dim4_result = dim4 - zero_scalar;
    ASSERT_EQ(dim4_result, dimension4_test(1, 2, 3, 4));

    dim4_result = dim4 - negative_scalar;
    ASSERT_EQ(dim4_result, dimension4_test(5, 6, 7, 8));
}

/// \brief Test the multiplication of a dimension4 by a scalar
TEST(dimension4, multiply_scalar) {
    dimension4_test dim4{1, 2, 3, 4};
    double scalar = 2;

    dimension4_test dim4_result = dim4 * scalar;
    dimension4_test dim4_result_inverse = scalar * dim4;

    // Test the multiplication of a dimension4 by a scalar
    ASSERT_EQ(dim4_result, dimension4_test(2, 4, 6, 8));
    ASSERT_EQ(dim4_result_inverse, dimension4_test(2, 4, 6, 8));
}

/// \brief Test the degenerate cases of the multiplication of a dimension4 by a scalar, using the * operator
TEST(dimension4, multiply_degenerate) {
    dimension4_test dim4{1, 2, 3, 4};
    double zero_scalar = 0;
    double negative_scalar = -4;

    dimension4_test dim4_result = dim4 * zero_scalar;
    ASSERT_EQ(dim4_result, dimension4_test(0, 0, 0, 0));

    dim4_result = dim4 * negative_scalar;
    ASSERT_EQ(dim4_result, dimension4_test(-4, -8, -12, -16));
}

/// \brief Test the division of a dimension4 by a scalar
TEST(dimension4, divide_scalar) {
    dimension4_test dim4{1, 2, 3, 4};
    double scalar = 2;

    dimension4_test dim4_result = dim4 / scalar;

    // Test the division of a dimension4 by a scalar
    ASSERT_EQ(dim4_result, dimension4_test(0.5, 1, 1.5, 2));
}

/// \brief Test the degenerate cases of the division of a dimension4 by a scalar, using the / operator
TEST(dimension4, divide_degenerate) {
    dimension4_test dim4{1, 2, 3, 4};
    dimension4_test dim4_zero{0, 0, 0, 0};
    double zero_scalar = 0;
    double negative_scalar = -4;

    ASSERT_THROW(dim4 / zero_scalar, std::invalid_argument);
    ASSERT_THROW(negative_scalar / dimension4_test(0, 1, 1, 1), std::invalid_argument);
    ASSERT_THROW(negative_scalar / dimension4_test(1, 0, 1, 1), std::invalid_argument);
    ASSERT_THROW(negative_scalar / dimension4_test(1, 1, 0, 1), std::invalid_argument);
    ASSERT_THROW(negative_scalar / dimension4_test(1, 1, 1, 0), std::invalid_argument);
    ASSERT_THROW(dim4 /= zero_scalar, std::invalid_argument);

    ASSERT_NO_THROW(dim4 / negative_scalar);
    ASSERT_NO_THROW(negative_scalar / dimension4_test(1, 1, 1, 1));
    ASSERT_NO_THROW(zero_scalar / dimension4_test(1, 1, 1, 1));
    ASSERT_NO_THROW(dim4_zero / negative_scalar);
    ASSERT_NO_THROW(dim4_zero /= negative_scalar);

    dimension4_test dim4_result = dim4 / negative_scalar;
    ASSERT_EQ(dim4_result, dimension4_test(-0.25, -0.5, -0.75, -1));
}

/// \brief Test the equality of two dimension4
TEST(dimension4, equal) {
    dimension4_test dim4{1, 2, 3, 4};
    dimension4_test dim4_positive{1, 2, 3, 4};
    dimension4_test dim4_negative{-1, -2, -3, -4};

    // Test the equality of two dimension4
    ASSERT_TRUE(dim4 == dim4_positive);
    ASSERT_FALSE(dim4 == dim4_negative);
}

/// \brief Test the equality of dimension3 and n, using the == operator
TEST(dimension4, equal_scalar) {
    dimension4_test dim4{1, 2, 3, 4};
    double scalar = 2;

    dimension4_test dim4_zero{0, 0, 0, 0};
    double scalar_zero = 0;

    // Test the equality of dimension3 and n
    ASSERT_FALSE(dim4 == scalar);
    ASSERT_TRUE(dim4_zero == scalar_zero);
}

/// \brief Test the inequality of two dimension4
TEST(dimension4, not_equal) {
    dimension4_test dim4{1, 2, 3, 4};
    dimension4_test dim4_positive{1, 2, 3, 4};
    dimension4_test dim4_negative{-1, -2, -3, -4};

    // Test the inequality of two dimension4
    ASSERT_FALSE(dim4 != dim4_positive);
    ASSERT_TRUE(dim4 != dim4_negative);
}

/// \brief Test the output stream of a dimension4
TEST(dimension4, output_stream) {
    dimension4_test dim4{1, 2, 3, 4};

    std::stringstream ss;
    ss << dim4;

    ASSERT_EQ(ss.str(), "dimension3_test: (1, 2, 3, 4)");
}