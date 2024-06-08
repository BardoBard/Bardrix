//
// Created by Bard on 15/03/2024.
//

#include <bardrix/dimension3.h>

class dim3_test : public bardrix::dimension3 {
public:
    dim3_test(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    std::ostream& print(std::ostream& os) const override {
        return os << "(" << x << ", " << y << ", " << z << ")";
    }
};

/// \brief Test min function
TEST(dimension3, min) {
    dim3_test dim3{1, 2, 3};
    dim3_test dim3_positive{4, 5, 6};
    dim3_test dim3_2{0,3,4};

    ASSERT_EQ(dim3.min(dim3_positive), dim3_test(1, 2, 3));
    ASSERT_EQ(dim3.min(dim3_2), dim3_test(0, 2, 3));
}

/// \brief Test max function
TEST(dimension3, max) {
    dim3_test dim3{1, 2, 3};
    dim3_test dim3_positive{4, 5, 6};
    dim3_test dim3_2{0,3,4};

    ASSERT_EQ(dim3.max(dim3_positive), dim3_test(4, 5, 6));
    ASSERT_EQ(dim3.max(dim3_2), dim3_test(1, 3, 4));
}

/// \brief Test the addition of two dimension3, using the + operator
TEST(dimension3, add) {
    dim3_test dim3{1, 2, 3};
    dim3_test dim3_positive{4, 5, 6};

    dim3_test dim3_result = dim3 + dim3_positive;
    ASSERT_EQ(dim3_result, dim3_test(5, 7, 9));
}

/// \brief Test the addition of a dimension3 by a scalar, using the + operator
TEST(dimension3, add_scalar) {
    dim3_test dim3{1, 2, 3};
    double scalar = 2;

    dim3_test dim3_result = dim3 + scalar;
    dim3_test dim3_result_inverse = scalar + dim3;

    // Test the addition of a dimension3 by a scalar
    ASSERT_EQ(dim3_result, dim3_test(3, 4, 5));
    ASSERT_EQ(dim3_result_inverse, dim3_test(3, 4, 5));
}

/// \brief Test the degenerate cases of the addition of a dimension3 by a scalar, using the + operator
TEST(dimension3, add_degenerate) {
    dim3_test dim3{1, 2, 3};
    dim3_test dim3_zero{0, 0, 0};
    dim3_test dim3_negative{-4, -5, -6};

    double zero_scalar = 0;
    double negative_scalar = -4;

    dim3_test dim3_result = dim3 + dim3_zero;
    ASSERT_EQ(dim3_result, dim3_test(1, 2, 3));

    dim3_result = dim3 + dim3_negative;
    ASSERT_EQ(dim3_result, dim3_test(-3, -3, -3));

    dim3_result = dim3 + zero_scalar;
    ASSERT_EQ(dim3_result, dim3_test(1, 2, 3));

    dim3_result = dim3 + negative_scalar;
    ASSERT_EQ(dim3_result, dim3_test(-3, -2, -1));
}

/// \brief Test the subtraction of two dimension3, using the - operator
TEST(dimension3, subtract) {
    dim3_test dim3{1, 2, 3};
    dim3_test dim3_positive{4, 5, 6};

    dim3_test dim3_result = dim3 - dim3_positive;
    ASSERT_EQ(dim3_result, dim3_test(-3, -3, -3));
}

/// \brief Test the subtraction of a dimension3 by a scalar, using the - operator
TEST(dimension3, subtract_scalar) {
    dim3_test dim3{1, 2, 3};
    double scalar = 2;

    dim3_test dim3_result = dim3 - scalar;
    dim3_test dim3_result_inverse = scalar - dim3;

    // Test the subtraction of a dimension3 by a scalar
    ASSERT_EQ(dim3_result, dim3_test(-1, 0, 1));
    ASSERT_EQ(dim3_result_inverse, dim3_test(1, 0, -1));
}

/// \brief Test the degenerate cases of the subtraction of a dimension3 by a scalar, using the - operator
TEST(dimension3, subtract_degenerate) {
    dim3_test dim3{1, 2, 3};
    dim3_test dim3_zero{0, 0, 0};
    dim3_test dim3_negative{-4, -5, -6};

    double zero_scalar = 0;
    double negative_scalar = -4;

    dim3_test dim3_result = dim3 - dim3_zero;
    ASSERT_EQ(dim3_result, dim3_test(1, 2, 3));

    dim3_result = dim3 - dim3_negative;
    ASSERT_EQ(dim3_result, dim3_test(5, 7, 9));

    dim3_result = dim3 - zero_scalar;
    ASSERT_EQ(dim3_result, dim3_test(1, 2, 3));

    dim3_result = dim3 - negative_scalar;
    ASSERT_EQ(dim3_result, dim3_test(5, 6, 7));
}

/// \brief Test the multiplication of a dimension3 by a scalar, using the * operator
TEST(dimension3, multiply) {
    dim3_test dim3{1, 2, 3};
    double scalar = 2;

    dim3_test dim3_result = dim3 * scalar;
    dim3_test dim3_result_inverse = scalar * dim3;

    // Test the multiplication of a dimension3 by a scalar
    ASSERT_EQ(dim3_result, dim3_test(2, 4, 6));
    ASSERT_EQ(dim3_result_inverse, dim3_test(2, 4, 6));
}

/// \brief Test the degenerate cases of the multiplication of a dimension3 by a scalar, using the * operator
TEST(dimension3, multiply_degenerate) {
    dim3_test dim3{1, 2, 3};
    dim3_test dim3_zero{0, 0, 0};
    dim3_test dim3_negative{-4, -5, -6};

    double zero_scalar = 0;
    double positive_scalar = 2;
    double negative_scalar = -4;

    dim3_test dim3_result = dim3_zero * positive_scalar;
    ASSERT_EQ(dim3_result, dim3_test(0, 0, 0));

    dim3_result = dim3_zero * negative_scalar;
    ASSERT_EQ(dim3_result, dim3_test(0, 0, 0));

    dim3_result = dim3 * zero_scalar;
    ASSERT_EQ(dim3_result, dim3_test(0, 0, 0));

    dim3_result = dim3 * positive_scalar;
    ASSERT_EQ(dim3_result, dim3_test(2, 4, 6));

    dim3_result = dim3 * negative_scalar;
    ASSERT_EQ(dim3_result, dim3_test(-4, -8, -12));

    dim3_result = zero_scalar * dim3;
    ASSERT_EQ(dim3_result, dim3_test(0, 0, 0));

    dim3_result = positive_scalar * dim3;
    ASSERT_EQ(dim3_result, dim3_test(2, 4, 6));

    dim3_result = negative_scalar * dim3;
    ASSERT_EQ(dim3_result, dim3_test(-4, -8, -12));
}

/// \brief Test the division of a dimension3 by a scalar, using the / operator
TEST(dimension3, divide) {
    dim3_test dim3{1, 2, 3};
    double scalar = 2;

    dim3_test dim3_result = dim3 / scalar;
    dim3_test dim3_result_inverse = scalar / dim3;

    // Test the division of a dimension3 by a scalar
    ASSERT_EQ(dim3_result, dim3_test(0.5, 1, 1.5));
    ASSERT_EQ(dim3_result_inverse, dim3_test(2, 1, 2.0 / 3.0));
}

/// \brief Test the degenerate cases of the division of a dimension3 by a scalar, using the / operator
TEST(dimension3, divide_degenerate) {
    dim3_test dim3{1, 2, 3};
    dim3_test dim3_zero{0, 0, 0};
    dim3_test dim3_negative{-4, -5, -6};

    double zero_scalar = 0;
    double positive_scalar = 2;
    double negative_scalar = -4;

    // throw if the divisor is zero
    ASSERT_THROW(dim3 / zero_scalar, std::invalid_argument);
    ASSERT_THROW(positive_scalar / dim3_zero, std::invalid_argument);
    ASSERT_THROW(negative_scalar / dim3_zero, std::invalid_argument);
    ASSERT_NO_THROW(dim3 / negative_scalar);
    ASSERT_NO_THROW(dim3 / positive_scalar);
    ASSERT_NO_THROW(zero_scalar / dim3);

    dim3_test dim3_result = dim3_zero / positive_scalar;
    ASSERT_EQ(dim3_result, dim3_test(0, 0, 0));

    dim3_result = dim3_negative / negative_scalar;
    ASSERT_EQ(dim3_result, dim3_test(1, 1.25, 1.5));

    dim3_result = dim3 / positive_scalar;
    ASSERT_EQ(dim3_result, dim3_test(0.5, 1, 1.5));

    dim3_result = dim3 / negative_scalar;
    ASSERT_EQ(dim3_result, dim3_test(-0.25, -0.5, -0.75));
}

/// \brief Test the modulo of a dimension3 by a scalar, using the % operator
TEST(dimension3, modulo) {
    dim3_test dim3{1, 2, 3};
    double scalar = 2;

    dim3_test dim3_result = dim3 % scalar;
    dim3_test dim3_result_inverse = scalar % dim3;

    // Test the modulo of a dimension3 by a scalar
    ASSERT_EQ(dim3_result, dim3_test(1, 0, 1));
    ASSERT_EQ(dim3_result_inverse, dim3_test(0, 0, 2));
}

/// \brief Test the degenerate cases of the modulo of a dimension3 by a scalar, using the % operator
TEST(dimension3, modulo_degenerate) {
    dim3_test dim3{1, 2, 3};
    dim3_test dim3_zero{0, 0, 0};
    dim3_test dim3_negative{-4, -5, -6};

    double zero_scalar = 0;
    double positive_scalar = 2;
    double negative_scalar = -4;

    // throw if the divisor is zero
    ASSERT_THROW(negative_scalar % dim3_zero, std::invalid_argument);
    ASSERT_THROW(positive_scalar % dim3_zero, std::invalid_argument);
    ASSERT_THROW(dim3 % zero_scalar, std::invalid_argument);
    ASSERT_NO_THROW(dim3 % negative_scalar);
    ASSERT_NO_THROW(dim3 % positive_scalar);

    dim3_test dim3_result = dim3_negative % negative_scalar;
    ASSERT_EQ(dim3_result, dim3_test(0, -1, -2));

    dim3_result = dim3 % negative_scalar;
    ASSERT_EQ(dim3_result, dim3_test(1, 2, 3));

    dim3_result = dim3 % positive_scalar;
    ASSERT_EQ(dim3_result, dim3_test(1, 0, 1));
}


/// \brief Test the equality of two dimension3, using the == operator
TEST(dimension3, equal) {
    dim3_test dim3{1, 2, 3};
    dim3_test dim3_positive{1, 2, 3};
    dim3_test dim3_negative{-4, -5, -6};

    // Test the equality of two dimension3
    ASSERT_TRUE(dim3 == dim3_positive);
    ASSERT_FALSE(dim3 == dim3_negative);
}

/// \brief Test the equality of dimension3 and n, using the == operator
TEST(dimension3, equal_scalar) {
    dim3_test dim3{1, 2, 3};
    double scalar = 2;

    dim3_test dim3_zero{0, 0, 0};
    double scalar_zero = 0;

    // Test the equality of dimension3 and n
    ASSERT_FALSE(dim3 == scalar);
    ASSERT_TRUE(dim3_zero == scalar_zero);
}

/// \brief Test the inequality of two dimension3, using the != operator
TEST(dimension3, not_equal) {
    dim3_test dim3{1, 2, 3};
    dim3_test dim3_positive{1, 2, 3};
    dim3_test dim3_negative{-4, -5, -6};

    // Test the inequality of two dimension3
    ASSERT_FALSE(dim3 != dim3_positive);
    ASSERT_TRUE(dim3 != dim3_negative);
}

/// \brief Test the less than comparison of two dimension3, using the < operator
TEST(dimension3, less) {
    dim3_test dim3{1, 2, 3};
    dim3_test dim3_positive{4, 5, 6};
    dim3_test dim3_negative{-4, -5, -6};

    // Test the less than comparison of two dimension3
    ASSERT_TRUE(dim3 < dim3_positive);
    ASSERT_FALSE(dim3 < dim3_negative);
}

/// \brief Test the greater than comparison of two dimension3, using the > operator
TEST(dimension3, greater) {
    dim3_test dim3{1, 2, 3};
    dim3_test dim3_positive{4, 5, 6};
    dim3_test dim3_negative{-4, -5, -6};

    // Test the greater than comparison of two dimension3
    ASSERT_FALSE(dim3 > dim3_positive);
    ASSERT_TRUE(dim3 > dim3_negative);
}

/// \brief Test the less than or equal comparison of two dimension3, using the <= operator
TEST(dimension3, less_equal) {
    dim3_test dim3{1, 2, 3};
    dim3_test dim3_positive{4, 5, 6};
    dim3_test dim3_negative{-4, -5, -6};

    // Test the less than or equal comparison of two dimension3
    ASSERT_TRUE(dim3 <= dim3_positive);
    ASSERT_FALSE(dim3 <= dim3_negative);
}

/// \brief Test the greater than or equal comparison of two dimension3, using the >= operator
TEST(dimension3, greater_equal) {
    dim3_test dim3{1, 2, 3};
    dim3_test dim3_positive{4, 5, 6};
    dim3_test dim3_negative{-4, -5, -6};

    // Test the greater than or equal comparison of two dimension3
    ASSERT_FALSE(dim3 >= dim3_positive);
    ASSERT_TRUE(dim3 >= dim3_negative);
}

/// \brief Test the negation of a dimension3, using the - operator
TEST(dimension3, negate) {
    dim3_test dim3{1, 2, 3};

    dim3_test dim3_result = -dim3;

    // Test the negation of a dimension3
    ASSERT_EQ(dim3_result, dim3_test(-1, -2, -3));
}

/// \brief Test the degenerate cases of the negation of a dimension3, using the - operator
TEST(dimension3, negate_degenerate) {
    dim3_test dim3_zero{0, 0, 0};
    dim3_test dim3_negative{-4, -5, -6};

    dim3_test dim3_result = -dim3_zero;
    ASSERT_EQ(dim3_result, dim3_test(0, 0, 0));

    dim3_result = -dim3_negative;
    ASSERT_EQ(dim3_result, dim3_test(4, 5, 6));
}

/// \brief Test the increment of a dimension3, using the ++ operator
TEST(dimension3, increment) {
    dim3_test dim3{1, 2, 3};

    dim3_test dim3_result = ++dim3;

    // Test the increment of a dimension3
    ASSERT_EQ(dim3_result, dim3_test(2, 3, 4));
    ASSERT_EQ(dim3, dim3_test(2, 3, 4));
}

/// \brief Test the decrement of a dimension3, using the -- operator
TEST(dimension3, decrement) {
    dim3_test dim3{1, 2, 3};

    dim3_test dim3_result = --dim3;

    // Test the decrement of a dimension3
    ASSERT_EQ(dim3_result, dim3_test(0, 1, 2));
    ASSERT_EQ(dim3, dim3_test(0, 1, 2));
}

/// \brief Test the increment of a dimension3, using the ++ operator
TEST(dimension3, increment_post) {
    dim3_test dim3{1, 2, 3};

    dim3_test dim3_result = dim3++;

    // Test the increment of a dimension3
    ASSERT_EQ(dim3_result, dim3_test(1, 2, 3));
    ASSERT_EQ(dim3, dim3_test(2, 3, 4));
}

/// \brief Test the decrement of a dimension3, using the -- operator
TEST(dimension3, decrement_post) {
    dim3_test dim3{1, 2, 3};

    dim3_test dim3_result = dim3--;

    // Test the decrement of a dimension3
    ASSERT_EQ(dim3_result, dim3_test(1, 2, 3));
    ASSERT_EQ(dim3, dim3_test(0, 1, 2));
}

/// \brief Test degenerate cases of %= operator
TEST(dimension3, modulo_equals_degenerate) {
    dim3_test dim3{1, 2, 3};
    dim3_test dim3_zero{0, 0, 0};
    dim3_test dim3_negative{-4, -5, -6};

    double zero_scalar = 0;
    double positive_scalar = 2;
    double negative_scalar = -4;

    //throw if the divisor is zero
    ASSERT_THROW(dim3 %= zero_scalar, std::invalid_argument);
    ASSERT_NO_THROW(dim3 %= negative_scalar);
    ASSERT_NO_THROW(dim3 %= positive_scalar);
}

/// \brief Test the degenerate cases of /= operator
TEST(dimension3, divide_equals_degenerate) {
    dim3_test dim3{1, 2, 3};
    dim3_test dim3_zero{0, 0, 0};
    dim3_test dim3_negative{-4, -5, -6};

    double zero_scalar = 0;
    double positive_scalar = 2;
    double negative_scalar = -4;

    //throw if the divisor is zero
    ASSERT_THROW(dim3 /= zero_scalar, std::invalid_argument);
    ASSERT_NO_THROW(dim3 /= negative_scalar);
    ASSERT_NO_THROW(dim3 /= positive_scalar);
}

/// \brief Test << operator
TEST(dimension3, stream) {
    dim3_test dim3{1, 2, 3};
    std::stringstream ss;
    ss << dim3;
    ASSERT_EQ(ss.str(), "(1, 2, 3)");
}
