//
// Created by Bard on 04/04/2024.
//

#pragma once

#include <bardrix/bardrix.h>

namespace bardrix {

    /// \brief Abstract class to represent 4 dimensions (x, y, z, w)
    /// \note This class is not meant to be used directly, but to be inherited by other classes
    /// \details This class implements the basic operations for 4 dimensions (+, +=, -, -=, *, *=, /, /=, %, %=, ==, !=, <, >, <=, >=, -, ++, --, <<)
    /// \example quaternion : public dimension4
    class dimension4 {

    public:
        /// \brief A template to check if a type is a derived class of dimension4
        /// \tparam T Type to check
        /// \tparam Result Type to return if T is a derived class of dimension4
        /// \note Usage: template<typename T>
        /// \note Example: Add<std::string>(20) -> error
        template<typename T, typename Result>
        using enable_if_dimension4 = std::enable_if_t<std::is_base_of_v<dimension4, T>, Result>;

    public:
        double x{}, y{}, z{}, w{};

        // https://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B
        // https://en.cppreference.com/w/cpp/language/operators
        // Operator overloading

        // Arithmetic operators

        /// \brief Add a dimension4 to another dimension4 (T result = dim4 + dim4)
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4_lhs dimension4 to add
        /// \param dimension4_rhs dimension4 to add
        /// \return A copy of the dimension4 with the result of the addition
        template<typename T>
        NODISCARD friend auto operator+(const T& dimension4_lhs, const T& dimension4_rhs) noexcept -> enable_if_dimension4<T, T> {
            T result = dimension4_lhs;
            result += dimension4_rhs;
            return result;
        }

        /// \brief Add a double to a dimension4 (T result = n + dim4)
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param n Value to add
        /// \param dimension4 dimension4 to add
        /// \return A copy of the dimension4 with the result of the addition
        template<typename T>
        NODISCARD friend auto operator+(double n, const T& dimension4) noexcept -> enable_if_dimension4<T, T> {
            return dimension4 + n;
        }

        /// \brief Add a dimension4 to a double (T result = dim4 + n)
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4 dimension4 to add
        /// \param n Value to add
        /// \return A copy of the dimension4 with the result of the addition
        template<typename T>
        NODISCARD friend auto operator+(const T& dimension4, double n) noexcept -> enable_if_dimension4<T, T> {
            T result = dimension4;
            result += n;
            return result;
        }

        /// \brief Add a dimension4 to another dimension4 (dim4 += dim4)
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4_lhs dimension4 containing the result
        /// \param dimension4_rhs dimension4 to add
        /// \return A reference to the dimension4 with the result of the addition
        template<typename T>
        friend auto operator+=(T& dimension4_lhs, const T& dimension4_rhs) noexcept -> enable_if_dimension4<T, const T&> {
            dimension4_lhs.x += dimension4_rhs.x;
            dimension4_lhs.y += dimension4_rhs.y;
            dimension4_lhs.z += dimension4_rhs.z;
            dimension4_lhs.w += dimension4_rhs.w;
            return dimension4_lhs;
        }

        /// \brief Add a double to a dimension4 (dim4 += n)
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4 dimension4 containing the result
        /// \param n Value to add
        /// \return A reference to the dimension4 with the result of the addition
        template<typename T>
        friend auto operator+=(T& dimension4, double n) noexcept -> enable_if_dimension4<T, const T&> {
            dimension4.x += n;
            dimension4.y += n;
            dimension4.z += n;
            dimension4.w += n;
            return dimension4;
        }

        /// \brief Subtract a dimension4 to another dimension4 (T result = dim4 - y)
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4_lhs dimension4 to subtract
        /// \param dimension4_rhs dimension4 to subtract
        /// \return A copy of the dimension4 with the result of the subtraction
        template<typename T>
        NODISCARD friend auto operator-(const T& dimension4_lhs, const T& dimension4_rhs) noexcept -> enable_if_dimension4<T, T> {
            T result = dimension4_lhs;
            result -= dimension4_rhs;
            return result;
        }

        /// \brief Subtract a dimension4 to a double (T result = n - dim4)
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param n Value to subtract
        /// \param dimension4 dimension4 to subtract
        /// \return A copy of the dimension4 with the result of the subtraction
        template<typename T>
        NODISCARD friend auto operator-(double n, const T& dimension4) noexcept -> enable_if_dimension4<T, T> {
            T result = dimension4;
            result.x = n - dimension4.x;
            result.y = n - dimension4.y;
            result.z = n - dimension4.z;
            result.w = n - dimension4.w;
            return result;
        }

        /// \brief Subtract a double to a dimension4 (T result = dim4 - n)
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4 dimension4 to subtract
        /// \param n Value to subtract
        /// \return A copy of the dimension4 with the result of the subtraction
        template<typename T>
        NODISCARD friend auto operator-(const T& dimension4, double n) noexcept -> enable_if_dimension4<T, T> {
            T result = dimension4;
            result -= n;
            return result;
        }

        /// \brief Subtract a dimension4 to another dimension4 (dim4 -= dim4)
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4_lhs dimension4 containing the result
        /// \param dimension4_rhs dimension4 to subtract
        /// \return A reference to the dimension4 with the result of the subtraction
        template<typename T>
        friend auto operator-=(T& dimension4_lhs, const T& dimension4_rhs) noexcept -> enable_if_dimension4<T, const T&> {
            dimension4_lhs.x -= dimension4_rhs.x;
            dimension4_lhs.y -= dimension4_rhs.y;
            dimension4_lhs.z -= dimension4_rhs.z;
            dimension4_lhs.w -= dimension4_rhs.w;
            return dimension4_lhs;
        }

        /// \brief Subtract a double to a dimension4 (dim4 -= n)
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4 dimension4 containing the result
        /// \param n Value to subtract
        /// \return A reference to the dimension4 with the result of the subtraction
        template<typename T>
        friend auto operator-=(T& dimension4, double n) noexcept -> enable_if_dimension4<T, const T&> {
            dimension4.x -= n;
            dimension4.y -= n;
            dimension4.z -= n;
            dimension4.w -= n;
            return dimension4;
        }

        /// \brief Multiply a dimension4 by a scalar (T result = dim4 * n)
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4 dimension4 to multiply
        /// \param n Value to multiply (scalar)
        /// \return A copy of the dimension4 with the result of the multiplication
        template<typename T>
        NODISCARD friend auto operator*(const T& dimension4, double n) noexcept -> enable_if_dimension4<T, T> {
            T result = dimension4;
            result *= n;
            return result;
        }

        /// \brief Multiply a dimension4 by a scalar (T result = n * dim4)
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param n Value to multiply (scalar)
        /// \param dimension4 dimension4 to multiply
        /// \return A copy of the dimension4 with the result of the multiplication
        template<typename T>
        NODISCARD friend auto operator*(double n, const T& dimension4) noexcept -> enable_if_dimension4<T, T> {
            return dimension4 * n;
        }

        /// \brief Multiply a dimension4 by a scalar (dim4 *= n)
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4 dimension4 containing the result
        /// \param n Value to multiply (scalar)
        /// \return A reference to the dimension4 with the result of the multiplication
        template<typename T>
        friend auto operator*=(T& dimension4, double n) noexcept -> enable_if_dimension4<T, const T&> {
            dimension4.x *= n;
            dimension4.y *= n;
            dimension4.z *= n;
            dimension4.w *= n;
            return dimension4;
        }

        /// \brief Divide a dimension4 by a scalar (T result = dim4 / n)
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4 dimension4 to divide
        /// \param n Value to divide (scalar)
        /// \throws std::invalid_argument If n is 0
        /// \return A copy of the dimension4 with the result of the division
        template<typename T>
        NODISCARD friend auto operator/(const T& dimension4, double n) -> enable_if_dimension4<T, T> {
            if (nearly_equal(n, 0))
                throw std::invalid_argument("Division by zero");

            T result = dimension4;
            result /= n;
            return result;
        }

        /// \brief Divide a dimension4 by a scalar (T result = n / dim4)
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param n Value to divide (scalar)
        /// \param dimension4 dimension4 to divide
        /// \throws std::invalid_argument If any of the dimension4 values is 0
        /// \return A copy of the dimension4 with the result of the division
        template<typename T>
        NODISCARD friend auto operator/(double n, const T& dimension4) -> enable_if_dimension4<T, T> {
            if (nearly_equal(dimension4.x, 0) || nearly_equal(dimension4.y, 0) || nearly_equal(dimension4.z, 0) ||
                nearly_equal(dimension4.w, 0))
                throw std::invalid_argument("Division by zero");

            T result = dimension4;
            result.x = n / dimension4.x;
            result.y = n / dimension4.y;
            result.z = n / dimension4.z;
            result.w = n / dimension4.w;
            return result;
        }

        /// \brief Divide a dimension4 by a scalar (dim4 /= n)
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4 dimension4 containing the result
        /// \param n Value to divide (scalar)
        /// \throws std::invalid_argument If n is 0
        /// \return A reference to the dimension4 with the result of the division
        template<typename T>
        friend auto operator/=(T& dimension4, double n) -> enable_if_dimension4<T, const T&> {
            if (nearly_equal(n, 0))
                throw std::invalid_argument("Division by zero");

            dimension4.x /= n;
            dimension4.y /= n;
            dimension4.z /= n;
            dimension4.w /= n;
            return dimension4;
        }

        /// \brief Modulus operator (T result = dim4 % n)
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4 dimension4 to calculate the modulus
        /// \param n Value to calculate the modulus
        /// \throws std::invalid_argument If n is 0
        /// \note It used the std::fmod function to calculate the modulus
        /// \return A copy of the dimension4 with the result of the modulus
        template<typename T>
        NODISCARD friend auto operator%(const T& dimension4, double n) -> enable_if_dimension4<T, T> {
            if (nearly_equal(n, 0))
                throw std::invalid_argument("Division by zero");

            T result = dimension4;
            result %= n;
            return result;
        }

        /// \brief Modulus operator (T result = n % dim4)
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param n Value to calculate the modulus
        /// \note It used the std::fmod function to calculate the modulus
        /// \param dimension4 dimension4 to calculate the modulus
        /// \throws std::invalid_argument If any of the dimension4 values is 0
        /// \return A copy of the dimension4 with the result of the modulus
        template<typename T>
        NODISCARD friend auto operator%(double n, const T& dimension4) -> enable_if_dimension4<T, T> {
            if (nearly_equal(dimension4.x, 0) || nearly_equal(dimension4.y, 0) || nearly_equal(dimension4.z, 0) ||
                nearly_equal(dimension4.w, 0))
                throw std::invalid_argument("Division by zero");

            T result = dimension4;
            result.x = std::fmod(n, result.x);
            result.y = std::fmod(n, result.y);
            result.z = std::fmod(n, result.z);
            result.w = std::fmod(n, result.w);
            return result;
        }

        /// \brief Modulus operator (dim4 %= n)
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4 dimension4 to calculate the modulus
        /// \param n Value to calculate the modulus
        /// \throws std::invalid_argument If n is 0
        /// \note It used the std::fmod function to calculate the modulus
        /// \return A reference to the dimension4 with the result of the modulus
        template<typename T>
        friend auto operator%=(T& dimension4, double n) -> enable_if_dimension4<T, const T&> {
            if (nearly_equal(n, 0))
                throw std::invalid_argument("Division by zero");

            dimension4.x = std::fmod(dimension4.x, n);
            dimension4.y = std::fmod(dimension4.y, n);
            dimension4.z = std::fmod(dimension4.z, n);
            dimension4.w = std::fmod(dimension4.w, n);
            return dimension4;
        }

        // Equality operators

        /// \brief Check if two dimension4 are equal
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4_lhs dimension4 to compare
        /// \param dimension4_rhs dimension4 to compare
        /// \return True if the two dimension4 are equal, false otherwise
        template<typename T>
        NODISCARD friend auto operator==(const T& dimension4_lhs, const T& dimension4_rhs) noexcept -> enable_if_dimension4<T, bool> {
            return nearly_equal(dimension4_lhs.x, dimension4_rhs.x) &&
                   nearly_equal(dimension4_lhs.y, dimension4_rhs.y) &&
                   nearly_equal(dimension4_lhs.z, dimension4_rhs.z) &&
                   nearly_equal(dimension4_lhs.w, dimension4_rhs.w);
        }

        /// \brief Check if a dimension4 is equal to a value
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4 dimension4 to compare
        /// \param n Value to compare
        /// \return True if the dimension4 is equal to the value, false otherwise
        template<typename T>
        NODISCARD friend auto operator==(const T& dimension4, double n) noexcept -> enable_if_dimension4<T, bool> {
            return nearly_equal(dimension4.x, n) && nearly_equal(dimension4.y, n) &&
                   nearly_equal(dimension4.z, n) && nearly_equal(dimension4.w, n);
        }

        /// \brief Check if two dimension4 are different
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4_lhs dimension4 to compare
        /// \param dimension4_rhs dimension4 to compare
        /// \return True if the two dimension4 are different, false otherwise
        template<typename T>
        NODISCARD friend auto operator!=(const T& dimension4_lhs, const T& dimension4_rhs) noexcept -> enable_if_dimension4<T, bool> {
            return !(dimension4_lhs == dimension4_rhs);
        }

        /// \brief Check if a dimension4 is less than another dimension4
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4_lhs dimension4 to compare
        /// \param dimension4_rhs dimension4 to compare
        /// \return True if the first dimension4 is less than the second dimension4, false otherwise
        template<typename T>
        NODISCARD friend auto operator<(const T& dimension4_lhs, const T& dimension4_rhs) noexcept -> enable_if_dimension4<T, bool> {
            return dimension4_lhs.x < dimension4_rhs.x && dimension4_lhs.y < dimension4_rhs.y &&
                   dimension4_lhs.z < dimension4_rhs.z && dimension4_lhs.w < dimension4_rhs.w;
        }

        /// \brief Check if a dimension4 is greater than another dimension4
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4_lhs dimension4 to compare
        /// \param dimension4_rhs dimension4 to compare
        /// \return True if the first dimension4 is greater than the second dimension4, false otherwise
        template<typename T>
        NODISCARD friend auto operator>(const T& dimension4_lhs, const T& dimension4_rhs) noexcept -> enable_if_dimension4<T, bool> {
            return dimension4_lhs.x > dimension4_rhs.x && dimension4_lhs.y > dimension4_rhs.y &&
                   dimension4_lhs.z > dimension4_rhs.z && dimension4_lhs.w > dimension4_rhs.w;
        }

        /// \brief Check if a dimension4 is less than or equal to another dimension4
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4_lhs dimension4 to compare
        /// \param dimension4_rhs dimension4 to compare
        /// \return True if the first dimension4 is less than or equal to the second dimension4, false otherwise
        template<typename T>
        NODISCARD friend auto operator<=(const T& dimension4_lhs, const T& dimension4_rhs) noexcept -> enable_if_dimension4<T, bool> {
            return less_than_or_nearly_equal(dimension4_lhs.x, dimension4_rhs.x) &&
                   less_than_or_nearly_equal(dimension4_lhs.y, dimension4_rhs.y) &&
                   less_than_or_nearly_equal(dimension4_lhs.z, dimension4_rhs.z) &&
                   less_than_or_nearly_equal(dimension4_lhs.w, dimension4_rhs.w);
        }

        /// \brief Check if a dimension4 is greater than or equal to another dimension4
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4_lhs dimension4 to compare
        /// \param dimension4_rhs dimension4 to compare
        /// \return True if the first dimension4 is greater than or equal to the second dimension4, false otherwise
        template<typename T>
        NODISCARD friend auto operator>=(const T& dimension4_lhs, const T& dimension4_rhs) noexcept -> enable_if_dimension4<T, bool> {
            return greater_than_or_nearly_equal(dimension4_lhs.x, dimension4_rhs.x) &&
                   greater_than_or_nearly_equal(dimension4_lhs.y, dimension4_rhs.y) &&
                   greater_than_or_nearly_equal(dimension4_lhs.z, dimension4_rhs.z) &&
                   greater_than_or_nearly_equal(dimension4_lhs.w, dimension4_rhs.w);
        }

        // Increment, decrement and unary operators

        /// \brief Inverts the sign of the dimension4
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4 dimension4 to invert
        /// \return A copy of the dimension4 with the inverted sign
        template<typename T>
        NODISCARD friend auto operator-(const T& dimension4) noexcept -> enable_if_dimension4<T, T> {
            T result = dimension4;
            result.x = -result.x;
            result.y = -result.y;
            result.z = -result.z;
            result.w = -result.w;
            return result;
        }

        /// \brief Prefix increment operator
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4 dimension4 to increment
        /// \return A reference to the dimension4 after the increment
        template<typename T>
        friend auto operator++(T& dimension4) noexcept -> enable_if_dimension4<T, T&> {
            ++dimension4.x;
            ++dimension4.y;
            ++dimension4.z;
            ++dimension4.w;
            return dimension4;
        }

        /// \brief Postfix increment operator
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4 dimension4 to increment
        /// \return A copy of the dimension4 before the increment
        template<typename T>
        NODISCARD friend auto operator++(T& dimension4, int) noexcept -> enable_if_dimension4<T, T> {
            T result = dimension4;
            ++dimension4;
            return result;
        }

        /// \brief Prefix decrement operator
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4 dimension4 to decrement
        /// \return A reference to the dimension4 after the decrement
        template<typename T>
        friend auto operator--(T& dimension4) noexcept -> enable_if_dimension4<T, T&> {
            --dimension4.x;
            --dimension4.y;
            --dimension4.z;
            --dimension4.w;
            return dimension4;
        }


        /// \brief Postfix decrement operator
        /// \tparam T Type of the dimension4, must be a derived class of dimension4
        /// \param dimension4 dimension4 to decrement
        /// \return A copy of the dimension4 before the decrement
        template<typename T>
        NODISCARD friend auto operator--(T& dimension4, int) noexcept -> enable_if_dimension4<T, T> {
            T result = dimension4;
            --dimension4;
            return result;
        }

        // Output operator

        /// \brief Output a dimension4 derived class to an output stream
        /// \param os Output stream
        /// \return A reference to the output stream
        virtual std::ostream& print(std::ostream& os) const = 0;

        /// \brief Output a dimension4 to an output stream
        /// \param os Output stream
        /// \param dimension4 dimension4 to output
        /// \return A reference to the output stream
        friend std::ostream& operator<<(std::ostream& os, const dimension4& dimension4){
            return dimension4.print(os);
        }

    }; // class dimension4

} // namespace bardrix
