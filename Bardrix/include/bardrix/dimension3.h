//
// Created by Bard on 13/03/2024.
//

#pragma once

#include <bardrix/bardrix.h>

namespace bardrix {

    /// \brief Abstract class to represent 3 dimensions
    /// \note This class is not meant to be used directly, but to be inherited by other classes
    /// \details This class implements the basic operations for 3 dimensions (+, +=, -, -=, *, *=, /, /=, %, %=, ==, !=, <, >, <=, >=, -, ++, --, <<)
    class dimension3 {

    public:
        /// \brief A template to check if a type is a derived class of dimension3
        /// \tparam T Type to check
        /// \tparam Result Type to return if T is a derived class of dimension3
        /// \example template<typename T> \n
        ///          auto Add(const T& value) const noexcept -> enable_if_dimension3<T, T>; \n
        ///          Add<std::string>("hello") -> error \n
        ///          Add<point3>({}) -> ok
        template<typename T, typename Result>
        using enable_if_dimension3 = std::enable_if_t<std::is_base_of_v<dimension3, T>, Result>;

    public:
        double x{}, y{}, z{};

        /// \brief Takes the minimum of each dimension of two dimension3 (T result = min(dim3, dim3))
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3 Dimension3 to compare
        /// \return A copy of the dimension3 with the minimum of each dimension
        /// \example point3 min_point = point3(1, 2, 3).min(point3(2, 1, 4)); // min_point = (1, 1, 3)
        template<typename T>
        NODISCARD auto min(const T& dimension3) const noexcept -> enable_if_dimension3<T, T> {
            T result = dimension3;
            result.x = std::min(x, result.x);
            result.y = std::min(y, result.y);
            result.z = std::min(z, result.z);
            return result;
        }

        /// \brief Takes the maximum of each dimension of two dimension3 (T result = max(dim3, dim3))
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3 Dimension3 to compare
        /// \return A copy of the dimension3 with the maximum of each dimension
        /// \example point3 max_point = point3(1, 2, 3).max(point3(2, 1, 4)); // max_point = (2, 2, 4)
        template<typename T>
        NODISCARD auto max(const T& dimension3) const noexcept -> enable_if_dimension3<T, T> {
            T result = dimension3;
            result.x = std::max(x, result.x);
            result.y = std::max(y, result.y);
            result.z = std::max(z, result.z);
            return result;
        }

        // https://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B
        // https://en.cppreference.com/w/cpp/language/operators
        // Operator overloading

        // Arithmetic operators

        /// \brief Add a dimension3 to another dimension3 (T result = dim3 + dim3)
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3_lhs Dimension3 to add
        /// \param dimension3_rhs Dimension3 to add
        /// \return A copy of the dimension3 with the result of the addition
        template<typename T>
        NODISCARD friend auto operator+(const T& dimension3_lhs, const T& dimension3_rhs) noexcept -> enable_if_dimension3<T, T> {
            T result = dimension3_lhs;
            result += dimension3_rhs;
            return result;
        }

        /// \brief Add a double to a dimension3 (T result = n + dim3)
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param n Value to add
        /// \param dimension3 Dimension3 to add
        /// \return A copy of the dimension3 with the result of the addition
        template<typename T>
        NODISCARD friend auto operator+(double n, const T& dimension3) noexcept -> enable_if_dimension3<T, T> {
            return dimension3 + n;
        }

        /// \brief Add a dimension3 to a double (T result = dim3 + n)
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3 Dimension3 to add
        /// \param n Value to add
        /// \return A copy of the dimension3 with the result of the addition
        template<typename T>
        NODISCARD friend auto operator+(const T& dimension3, double n) noexcept -> enable_if_dimension3<T, T> {
            T result = dimension3;
            result += n;
            return result;
        }

        /// \brief Add a dimension3 to another dimension3 (dim3 += dim3)
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3_lhs Dimension3 containing the result
        /// \param dimension3_rhs Dimension3 to add
        /// \return A reference to the dimension3 with the result of the addition
        template<typename T>
        friend auto operator+=(T& dimension3_lhs, const T& dimension3_rhs) noexcept -> enable_if_dimension3<T, const T&> {
            dimension3_lhs.x += dimension3_rhs.x;
            dimension3_lhs.y += dimension3_rhs.y;
            dimension3_lhs.z += dimension3_rhs.z;
            return dimension3_lhs;
        }

        /// \brief Add a double to a dimension3 (dim3 += n)
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3 Dimension3 containing the result
        /// \param n Value to add
        /// \return A reference to the dimension3 with the result of the addition
        template<typename T>
        friend auto operator+=(T& dimension3, double n) noexcept -> enable_if_dimension3<T, const T&> {
            dimension3.x += n;
            dimension3.y += n;
            dimension3.z += n;
            return dimension3;
        }

        /// \brief Subtract a dimension3 to another dimension3 (T result = dim3 - y)
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3_lhs Dimension3 to subtract
        /// \param dimension3_rhs Dimension3 to subtract
        /// \return A copy of the dimension3 with the result of the subtraction
        template<typename T>
        NODISCARD friend auto operator-(const T& dimension3_lhs, const T& dimension3_rhs) noexcept -> enable_if_dimension3<T, T> {
            T result = dimension3_lhs;
            result -= dimension3_rhs;
            return result;
        }

        /// \brief Subtract a dimension3 to a double (T result = n - dim3)
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param n Value to subtract
        /// \param dimension3 Dimension3 to subtract
        /// \return A copy of the dimension3 with the result of the subtraction
        template<typename T>
        NODISCARD friend auto operator-(double n, const T& dimension3) noexcept -> enable_if_dimension3<T, T> {
            T result = dimension3;
            result.x = n - dimension3.x;
            result.y = n - dimension3.y;
            result.z = n - dimension3.z;
            return result;
        }

        /// \brief Subtract a double to a dimension3 (T result = dim3 - n)
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3 Dimension3 to subtract
        /// \param n Value to subtract
        /// \return A copy of the dimension3 with the result of the subtraction
        template<typename T>
        NODISCARD friend auto operator-(const T& dimension3, double n) noexcept -> enable_if_dimension3<T, T> {
            T result = dimension3;
            result -= n;
            return result;
        }

        /// \brief Subtract a dimension3 to another dimension3 (dim3 -= dim3)
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3_lhs Dimension3 containing the result
        /// \param dimension3_rhs Dimension3 to subtract
        /// \return A reference to the dimension3 with the result of the subtraction
        template<typename T>
        friend auto operator-=(T& dimension3_lhs, const T& dimension3_rhs) noexcept -> enable_if_dimension3<T, const T&> {
            dimension3_lhs.x -= dimension3_rhs.x;
            dimension3_lhs.y -= dimension3_rhs.y;
            dimension3_lhs.z -= dimension3_rhs.z;
            return dimension3_lhs;
        }

        /// \brief Subtract a double to a dimension3 (dim3 -= n)
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3 Dimension3 containing the result
        /// \param n Value to subtract
        /// \return A reference to the dimension3 with the result of the subtraction
        template<typename T>
        friend auto operator-=(T& dimension3, double n) noexcept -> enable_if_dimension3<T, const T&> {
            dimension3.x -= n;
            dimension3.y -= n;
            dimension3.z -= n;
            return dimension3;
        }

        /// \brief Multiply a dimension3 by a scalar (T result = dim3 * n)
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3 Dimension3 to multiply
        /// \param n Value to multiply (scalar)
        /// \return A copy of the dimension3 with the result of the multiplication
        template<typename T>
        NODISCARD friend auto operator*(const T& dimension3, double n) noexcept -> enable_if_dimension3<T, T> {
            T result = dimension3;
            result *= n;
            return result;
        }

        /// \brief Multiply a dimension3 by a scalar (T result = n * dim3)
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param n Value to multiply (scalar)
        /// \param dimension3 Dimension3 to multiply
        /// \return A copy of the dimension3 with the result of the multiplication
        template<typename T>
        NODISCARD friend auto operator*(double n, const T& dimension3) noexcept -> enable_if_dimension3<T, T> {
            return dimension3 * n;
        }

        /// \brief Multiply a dimension3 by a scalar (dim3 *= n)
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3 Dimension3 containing the result
        /// \param n Value to multiply (scalar)
        /// \return A reference to the dimension3 with the result of the multiplication
        template<typename T>
        friend auto operator*=(T& dimension3, double n) noexcept -> enable_if_dimension3<T, const T&> {
            dimension3.x *= n;
            dimension3.y *= n;
            dimension3.z *= n;
            return dimension3;
        }

        /// \brief Divide a dimension3 by a scalar (T result = dim3 / n)
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3 Dimension3 to divide
        /// \param n Value to divide (scalar)
        /// \throws std::invalid_argument If n is 0
        /// \return A copy of the dimension3 with the result of the division
        template<typename T>
        NODISCARD friend auto operator/(const T& dimension3, double n) -> enable_if_dimension3<T, T> {
            if (nearly_equal(n, 0))
                throw std::invalid_argument("Division by zero");

            T result = dimension3;
            result /= n;
            return result;
        }

        /// \brief Divide a dimension3 by a scalar (T result = n / dim3)
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param n Value to divide (scalar)
        /// \param dimension3 Dimension3 to divide
        /// \throws std::invalid_argument If any of the dimension3 values is 0
        /// \return A copy of the dimension3 with the result of the division
        template<typename T>
        NODISCARD friend auto operator/(double n, const T& dimension3) -> enable_if_dimension3<T, T> {
            if (nearly_equal(dimension3.x, 0) || nearly_equal(dimension3.y, 0) || nearly_equal(dimension3.z, 0))
                throw std::invalid_argument("Division by zero");

            T result = dimension3;
            result.x = n / dimension3.x;
            result.y = n / dimension3.y;
            result.z = n / dimension3.z;
            return result;
        }

        /// \brief Divide a dimension3 by a scalar (dim3 /= n)
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3 Dimension3 containing the result
        /// \param n Value to divide (scalar)
        /// \throws std::invalid_argument If n is 0
        /// \return A reference to the dimension3 with the result of the division
        template<typename T>
        friend auto operator/=(T& dimension3, double n) -> enable_if_dimension3<T, const T&> {
            if (nearly_equal(n, 0))
                throw std::invalid_argument("Division by zero");

            dimension3.x /= n;
            dimension3.y /= n;
            dimension3.z /= n;
            return dimension3;
        }

        /// \brief Modulus operator (T result = dim3 % n)
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3 Dimension3 to calculate the modulus
        /// \param n Value to calculate the modulus
        /// \throws std::invalid_argument If n is 0
        /// \note It used the std::fmod function to calculate the modulus
        /// \return A copy of the dimension3 with the result of the modulus
        template<typename T>
        NODISCARD friend auto operator%(const T& dimension3, double n) -> enable_if_dimension3<T, T> {
            if (nearly_equal(n, 0))
                throw std::invalid_argument("Division by zero");

            T result = dimension3;
            result %= n;
            return result;
        }

        /// \brief Modulus operator (T result = n % dim3)
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param n Value to calculate the modulus
        /// \note It used the std::fmod function to calculate the modulus
        /// \param dimension3 Dimension3 to calculate the modulus
        /// \throws std::invalid_argument If any of the dimension3 values is 0
        /// \return A copy of the dimension3 with the result of the modulus
        template<typename T>
        NODISCARD friend auto operator%(double n, const T& dimension3) -> enable_if_dimension3<T, T> {
            if (nearly_equal(dimension3.x, 0) || nearly_equal(dimension3.y, 0) || nearly_equal(dimension3.z, 0))
                throw std::invalid_argument("Division by zero");

            T result = dimension3;
            result.x = std::fmod(n, result.x);
            result.y = std::fmod(n, result.y);
            result.z = std::fmod(n, result.z);
            return result;
        }

        /// \brief Modulus operator (dim3 %= n)
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3 Dimension3 to calculate the modulus
        /// \param n Value to calculate the modulus
        /// \throws std::invalid_argument If n is 0
        /// \note It used the std::fmod function to calculate the modulus
        /// \return A reference to the dimension3 with the result of the modulus
        template<typename T>
        friend auto operator%=(T& dimension3, double n) -> enable_if_dimension3<T, const T&> {
            if (nearly_equal(n, 0))
                throw std::invalid_argument("Division by zero");

            dimension3.x = std::fmod(dimension3.x, n);
            dimension3.y = std::fmod(dimension3.y, n);
            dimension3.z = std::fmod(dimension3.z, n);
            return dimension3;
        }

        // Equality operators

        /// \brief Check if two dimension3 are equal
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3_lhs Dimension3 to compare
        /// \param dimension3_rhs Dimension3 to compare
        /// \return True if the two dimension3 are equal, false otherwise
        template<typename T>
        NODISCARD friend auto operator==(const T& dimension3_lhs, const T& dimension3_rhs) noexcept -> enable_if_dimension3<T, bool> {
            return nearly_equal(dimension3_lhs.x, dimension3_rhs.x) &&
                   nearly_equal(dimension3_lhs.y, dimension3_rhs.y) &&
                   nearly_equal(dimension3_lhs.z, dimension3_rhs.z);
        }

        /// \brief Check if dimension3 is equal to a value
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3 Dimension3 to compare
        /// \param n Value to compare
        /// \return True if the dimension3 is equal to the value, false otherwise
        template<typename T>
        NODISCARD friend auto operator==(const T& dimension3, double n) noexcept -> enable_if_dimension3<T, bool> {
            return nearly_equal(dimension3.x, n) && nearly_equal(dimension3.y, n) && nearly_equal(dimension3.z, n);
        }

        /// \brief Check if two dimension3 are different
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3_lhs Dimension3 to compare
        /// \param dimension3_rhs Dimension3 to compare
        /// \return True if the two dimension3 are different, false otherwise
        template<typename T>
        NODISCARD friend auto operator!=(const T& dimension3_lhs, const T& dimension3_rhs) noexcept -> enable_if_dimension3<T, bool> {
            return !(dimension3_lhs == dimension3_rhs);
        }

        /// \brief Check if a dimension3 is less than another dimension3
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3_lhs Dimension3 to compare
        /// \param dimension3_rhs Dimension3 to compare
        /// \return True if the first dimension3 is less than the second dimension3, false otherwise
        template<typename T>
        NODISCARD friend auto operator<(const T& dimension3_lhs, const T& dimension3_rhs) noexcept -> enable_if_dimension3<T, bool> {
            return dimension3_lhs.x < dimension3_rhs.x && dimension3_lhs.y < dimension3_rhs.y &&
                   dimension3_lhs.z < dimension3_rhs.z;
        }

        /// \brief Check if a dimension3 is greater than another dimension3
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3_lhs Dimension3 to compare
        /// \param dimension3_rhs Dimension3 to compare
        /// \return True if the first dimension3 is greater than the second dimension3, false otherwise
        template<typename T>
        NODISCARD friend auto operator>(const T& dimension3_lhs, const T& dimension3_rhs) noexcept -> enable_if_dimension3<T, bool> {
            return dimension3_lhs.x > dimension3_rhs.x && dimension3_lhs.y > dimension3_rhs.y &&
                   dimension3_lhs.z > dimension3_rhs.z;
        }

        /// \brief Check if a dimension3 is less than or equal to another dimension3
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3_lhs Dimension3 to compare
        /// \param dimension3_rhs Dimension3 to compare
        /// \return True if the first dimension3 is less than or equal to the second dimension3, false otherwise
        template<typename T>
        NODISCARD friend auto operator<=(const T& dimension3_lhs, const T& dimension3_rhs) noexcept -> enable_if_dimension3<T, bool> {
            return less_than_or_nearly_equal(dimension3_lhs.x, dimension3_rhs.x) &&
                   less_than_or_nearly_equal(dimension3_lhs.y, dimension3_rhs.y) &&
                   less_than_or_nearly_equal(dimension3_lhs.z, dimension3_rhs.z);
        }

        /// \brief Check if a dimension3 is greater than or equal to another dimension3
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3_lhs Dimension3 to compare
        /// \param dimension3_rhs Dimension3 to compare
        /// \return True if the first dimension3 is greater than or equal to the second dimension3, false otherwise
        template<typename T>
        NODISCARD friend auto operator>=(const T& dimension3_lhs, const T& dimension3_rhs) noexcept -> enable_if_dimension3<T, bool> {
            return greater_than_or_nearly_equal(dimension3_lhs.x, dimension3_rhs.x) &&
                   greater_than_or_nearly_equal(dimension3_lhs.y, dimension3_rhs.y) &&
                   greater_than_or_nearly_equal(dimension3_lhs.z, dimension3_rhs.z);
        }

        // Increment, decrement and unary operators

        /// \brief Inverts the sign of the dimension3
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3 Dimension3 to invert
        /// \return A copy of the dimension3 with the inverted sign
        template<typename T>
        NODISCARD friend auto operator-(const T& dimension3) noexcept -> enable_if_dimension3<T, T> {
            T result = dimension3;
            result.x = -result.x;
            result.y = -result.y;
            result.z = -result.z;
            return result;
        }

        /// \brief Prefix increment operator
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3 Dimension3 to increment
        /// \return A reference to the dimension3 after the increment
        template<typename T>
        friend auto operator++(T& dimension3) noexcept -> enable_if_dimension3<T, T&> {
            ++dimension3.x;
            ++dimension3.y;
            ++dimension3.z;
            return dimension3;
        }

        /// \brief Postfix increment operator
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3 Dimension3 to increment
        /// \return A copy of the dimension3 before the increment
        template<typename T>
        NODISCARD friend auto operator++(T& dimension3, int) noexcept -> enable_if_dimension3<T, T> {
            T result = dimension3;
            ++dimension3;
            return result;
        }

        /// \brief Prefix decrement operator
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3 Dimension3 to decrement
        /// \return A reference to the dimension3 after the decrement
        template<typename T>
        friend auto operator--(T& dimension3) noexcept -> enable_if_dimension3<T, T&> {
            --dimension3.x;
            --dimension3.y;
            --dimension3.z;
            return dimension3;
        }


        /// \brief Postfix decrement operator
        /// \tparam T Type of the dimension3, must be a derived class of dimension3
        /// \param dimension3 Dimension3 to decrement
        /// \return A copy of the dimension3 before the decrement
        template<typename T>
        NODISCARD friend auto operator--(T& dimension3, int) noexcept -> enable_if_dimension3<T, T> {
            T result = dimension3;
            --dimension3;
            return result;
        }

        // Output operator

        /// \brief Output a dimension3 derived class to an output stream
        /// \param os Output stream
        /// \return A reference to the output stream
        virtual std::ostream& print(std::ostream& os) const = 0;

        /// \brief Output a dimension3 to an output stream (dim3, y, z)
        /// \param os Output stream
        /// \param dimension3 Dimension3 to output
        /// \return A reference to the output stream
        friend std::ostream& operator<<(std::ostream& os, const dimension3& dimension3);

        /// \brief Get the value of a dimension
        /// \param axis The axis to get the value
        /// \return The value of the axis
        /// \throws std::invalid_argument If the axis is invalid
        /// \note axis::x = 0, axis::y = 1, axis::z = 2
        /// \example point3(1, 2, 3)[axis::x] -> 1
        NODISCARD double& operator[](axis axis);

    }; // class dimension3

} // namespace bardrix
