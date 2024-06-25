//
// Created by Bardio on 22/06/2024.
//

#pragma once

#include <bardrix/bardrix.h>

namespace bardrix {

    /// \brief Represents a binary tree, which is a tree data structure in which each node has at most two children.  \n
    /// \tparam T The type of the values in the binary tree, e.g int, double, point3, etc.
    /// \example       5        \n
    ///              /   \      \n
    ///             3     7     \n
    ///            / \   / \    \n
    ///           1   4 6   8
    /// \note The implementation of operator==, operator!= and operator= are required for the binary tree to work.
    template<typename T>
    class binary_tree {
    public:
        static_assert(std::is_convertible_v<decltype(std::declval<T>() == std::declval<T>()), bool>,
                      "Template argument T must have operator==");
        static_assert(std::is_convertible_v<decltype(std::declval<T>() != std::declval<T>()), bool>,
                      "Template argument T must have operator!=");
        static_assert(std::is_assignable_v<T&, const T&>, "Template argument T must have operator=");

        /// \brief Represents a node in the binary tree.
        /// \details The node has a value of type T and two children, left and right.
        class node {
        public:
            /// \brief The value of the node, which is of type T (of the binary tree).
            T data;

            /// \brief The left child of the node.
            std::unique_ptr<node> left;

            /// \brief The right child of the node.
            std::unique_ptr<node> right;

        public:
            /// \brief Constructs a node with the given value and no children.
            /// \param val The value of the node.
            explicit node(T val) noexcept: node(std::move(val), nullptr, nullptr) {}

            /// \brief Constructs a node with the given value and children.
            /// \param val The value of the node.
            /// \param left The left child of the node.
            /// \param right The right child of the node.
            node(T val, std::unique_ptr<node> left, std::unique_ptr<node> right) noexcept: data(std::move(val)),
                                                                                           left(std::move(left)),
                                                                                           right(std::move(right)) {}
        }; // class node

    protected:
        /// \brief The predicate used to compare two values of type T.
        /// \details The predicate is used to determine whether a value should be inserted to the left or right of a node.
        /// \param lhs The left-hand side value.
        /// \param rhs The right-hand side value.
        /// \return True if the left-hand side value should be inserted to the left of the right-hand side value, false otherwise.
        /// \example bool int_predicate(int a, int b) { return a < b; } // Returns true if a is less than b.
        std::function<bool(const T&, const T&)> predicate;

    public:
        /// \brief Root node of the binary tree, this is the entry point to the tree.
        std::unique_ptr<node> root;

        /// \brief Constructs a binary tree with the given predicate.
        /// \param predicate The predicate used to compare two values of type T.
        explicit binary_tree(std::function<bool(const T&, const T&)> predicate) noexcept;

        /// \brief Clears the binary tree, removing all nodes.
        /// \example tree.clear(); // Removes all nodes from the binary tree.
        void clear() noexcept;

        /// \brief Builds a balanced binary tree from the given values.                                             \n
        ///        For a balanced tree the values should be sorted in ascending order. (e.g 1, 2, 3, 4, 5, 6, 7, 8) \n
        ///        The sorting should adhere to the predicate given in the constructor.
        /// \param values The values to insert into the binary tree.
        /// \param size The number of values to insert into the binary tree.
        /// \example int values[] = {1, 2, 3, 4, 5, 6, 7, 8}; tree.build(values, sizeof values / sizeof values[0]); \n
        ///          5        \n
        ///         / \       \n
        ///        3   7      \n
        ///       / \ / \     \n
        ///      2  4 6  8    \n
        ///     /             \n
        ///    1
        /// \note Use this function for a balanced binary tree.
        /// \details O(n) time complexity assuming the values are sorted.
        void build(const T* values, std::size_t size) noexcept;

        /// \brief Builds a balanced binary tree from the given values.                                                         \n
        ///        For a balanced tree the values should be sorted in ascending order. (e.g 1, 2, 3, 4, 5, 6, 7, 8)             \n
        ///        The sorting should adhere to the predicate given in the constructor.
        /// \tparam Iterator The type of the iterator to the values to insert into the binary tree.
        /// \param begin The beginning of the values to insert into the binary tree.
        /// \param end The end of the values to insert into the binary tree.
        /// \example std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8}; tree.build(values.begin(), values.end());              \n
        ///          int values[] = {1, 2, 3, 4, 5, 6, 7, 8}; tree.build(values, values + sizeof values / sizeof values[0]);    \n
        ///          5        \n
        ///         / \       \n
        ///        3   7      \n
        ///       / \ / \     \n
        ///      2  4 6  8    \n
        ///     /             \n
        ///    1
        /// \note Use this function for a balanced binary tree.
        /// \details O(n) time complexity assuming the values are sorted.
        template<typename Iterator, typename = std::enable_if_t<std::is_same_v<T, typename std::iterator_traits<Iterator>::value_type>>>
        void build(Iterator begin, Iterator end) noexcept;

        /// \brief Builds a balanced binary tree from the given values.                                             \n
        ///        For a balanced tree the values should be sorted in ascending order. (e.g 1, 2, 3, 4, 5, 6, 7, 8) \n
        ///        The sorting should adhere to the predicate given in the constructor.
        /// \tparam Args The types of the values to insert into the binary tree.
        /// \param val The first value to insert into the binary tree.
        /// \param args Other values to insert into the binary tree.
        /// \example tree.build(1, 2, 3, 4, 5, 6, 7, 8); // Builds a balanced binary tree \n
        ///          5        \n
        ///         / \       \n
        ///        3   7      \n
        ///       / \ / \     \n
        ///      2  4 6  8    \n
        ///     /             \n
        ///    1
        /// \note Use this function for a balanced binary tree.
        /// \details O(n) time complexity assuming the values are sorted.
        template<typename... Args>
        void build(T val, Args... args) noexcept;

        /// \brief Inserts the given values into the binary tree.           \n
        ///        The values are inserted in the order they are given.     \n
        ///        Use build function for a balanced binary tree.
        /// \tparam Args The types of the values to insert into the binary tree.
        /// \param val The first value to insert into the binary tree.
        /// \param args Other values to insert into the binary tree.
        /// \example tree.insert(2, 1, 3, 4, 5); \n
        ///          2          \n
        ///         / \         \n
        ///        1   3        \n
        ///             \       \n
        ///              4      \n
        ///               \     \n
        ///                5
        /// \note Do not use this function for a balanced binary tree, use the build function instead.
        /// \details O(log n) time complexity assuming the binary tree is balanced. \n
        ///          O(n) time complexity in the worst case (when the tree is unbalanced).
        template<typename... Args>
        void insert(T val, Args... args) noexcept;

        /// \brief Inserts the given values into the binary tree.           \n
        ///        The values are inserted in the order they are given.     \n
        ///        Use build function for a balanced binary tree.
        /// \param values The values to insert into the binary tree.
        /// \param size The number of values to insert into the binary tree.
        /// \example int values[] = {2, 1, 3, 4, 5}; tree.insert(values, 5);                                \n
        ///          std::vector<int> values = {2, 1, 3, 4, 5}; tree.insert(values.data(), values.size());  \n
        ///          2          \n
        ///         / \         \n
        ///        1   3        \n
        ///             \       \n
        ///              4      \n
        ///               \     \n
        ///                5
        /// \note Do not use this function for a balanced binary tree, use the build function instead.
        /// \details O(log n) time complexity assuming the binary tree is balanced. \n
        ///          O(n) time complexity in the worst case (when the tree is unbalanced).
        void insert(const T* values, std::size_t size) noexcept;

        /// \brief Inserts the given values into the binary tree.           \n
        ///        The values are inserted in the order they are given.     \n
        ///        Use build function for a balanced binary tree.
        /// \tparam Iterator The type of the iterator to the values to insert into the binary tree.
        /// \param begin The beginning of the values to insert into the binary tree.
        /// \param end The end of the values to insert into the binary tree.
        /// \example int values[] = {2, 1, 3, 4, 5}; tree.insert(values, values + sizeof values / sizeof values[0]);  \n
        ///          std::vector<int> values = {2, 1, 3, 4, 5}; tree.insert(values.begin(), values.end());            \n
        ///          2          \n
        ///         / \         \n
        ///        1   3        \n
        ///             \       \n
        ///              4      \n
        ///               \     \n
        ///                5
        /// \note Do not use this function for a balanced binary tree, use the build function instead.
        /// \details O(log n) time complexity assuming the binary tree is balanced. \n
        ///          O(n) time complexity in the worst case (when the tree is unbalanced).
        template<typename Iterator, typename = std::enable_if_t<std::is_same_v<T, typename std::iterator_traits<Iterator>::value_type>>>
        void insert(Iterator begin, Iterator end) noexcept;

        /// \brief Deletes a node from the binary tree.                                                                  \n
        ///        The node is replaced with a bigger value from the right child or a smaller value from the left child. \n
        ///        When the node is removed it doesn't rebalance the tree.
        /// \param val The value of the node to delete.
        /// \param prefer_left Whether to prefer the left child to replace the node when deleting a node. \n
        ///                    Default is false.
        /// \example tree.delete_node(3); // (1,2,3,4,5,6,7,8) -> (1,2,4,5,6,7,8)   \n
        ///          5                  \n
        ///         / \                 \n
        ///        3   7                \n
        ///       / \ / \               \n
        ///      2  4 6  8              \n
        ///     /                       \n
        ///    1                        \n
        /// This will be turned into:   \n
        ///          5                  \n
        ///         / \                 \n
        ///        4   7                \n
        ///       /   / \               \n
        ///      2   6   8              \n
        ///     /                       \n
        ///    1
        /// \details This function deletes the node with the given value from the binary tree.
        /// \details O(log n) time complexity assuming the binary tree is balanced. \n
        ///          O(n) time complexity in the worst case (when the tree is unbalanced).
        bool remove(T val, bool prefer_left = false) noexcept;

        /// \brief Checks if the binary tree contains the given value, meant to be a helper function for the public contains function.
        /// \param current The current node to check if it contains the value.
        /// \param val The value to check if it is in the binary tree.
        /// \return True if the binary tree contains the value, false otherwise.
        /// \example if (tree.contains(3)) std::cout << "The tree contains the value 3!";
        /// \details O(log n) time complexity assuming the binary tree is balanced. \n
        ///          O(n) time complexity in the worst case (when the tree is unbalanced).
        NODISCARD bool contains(const node* current, T val) const noexcept;

        /// \brief Checks if the binary tree contains the given value.
        /// \param val The value to check if it is in the binary tree.
        /// \return True if the binary tree contains the value, false otherwise.
        /// \example if (tree.contains(3)) std::cout << "The tree contains the value 3!";
        NODISCARD bool contains(T val) const noexcept;

        /// \brief Finds the node with the given value, it's called recursively.
        /// \param current The current node to find the value from.
        /// \param val The value to find in the binary tree.
        /// \return The node with the given value in the binary tree.
        NODISCARD const node* find(const node* current, T val) const noexcept;

        /// \brief Finds the node with the given value.
        /// \param val The value to find in the binary tree.
        /// \return The node with the given value in the binary tree.
        /// \example const node* node = tree.find(3); // (1,2,3,4,5) -> node with value 3
        NODISCARD const node* find(T val) const noexcept;

        /// \brief Traverses the binary tree in-order, it's called recursively.
        /// \param current The current node to traverse the binary tree from.
        /// \param callback The function to call for each node in the binary tree.
        /// \details In-order means that the smallest value is visited first, then the next smallest value and so on.
        /// \details O(n) time complexity, where n is the number of nodes in the binary tree.
        /// \example tree.traverse_in_order(root.get(), [](const int& val) { std::cout << val << ' '; }); // (1,2,3,4,5) -> 1 2 3 4 5 \n
        ///           3 (3)     \n
        ///          / \        \n
        ///     (2) 2   5 (5)   \n
        ///        /   /        \n
        ///   (1) 1   4 (4)
        void traverse_in_order(const node* current, std::function<void(const T&)> callback) const noexcept;

        /// \brief Traverses the binary tree in-order, it's called recursively.
        /// \param callback The function to call for each node in the binary tree.
        /// \details In-order means that the smallest value is visited first, then the next smallest value and so on.
        /// \details O(n) time complexity, where n is the number of nodes in the binary tree.
        /// \example tree.traverse_in_order([](const int& val) { std::cout << val << ' '; }); // (1,2,3,4,5) -> 1 2 3 4 5 \n
        ///           3 (3)     \n
        ///          / \        \n
        ///     (2) 2   5 (5)   \n
        ///        /   /        \n
        ///   (1) 1   4 (4)
        void traverse_in_order(std::function<void(const T&)> callback) const noexcept;

        /// \brief Traverses the binary tree in pre-order, it's called recursively.
        /// \param current The current node to traverse the binary tree from.
        /// \param callback The function to call for each node in the binary tree.
        /// \details O(n) time complexity, where n is the number of nodes in the binary tree.
        /// \example tree.traverse_pre_order(root.get(), [](const int& val) { std::cout << val << ' '; }); // (1,2,3,4,5) -> 3 2 1 5 4 \n
        ///           3 (1)     \n
        ///          / \        \n
        ///     (2) 2   5 (4)   \n
        ///        /   /        \n
        ///   (3) 1   4 (5)
        void traverse_pre_order(const node* current, std::function<void(const T&)> callback) const noexcept;

        /// \brief Traverses the binary tree in pre-order, it's called recursively.
        /// \param callback The function to call for each node in the binary tree.
        /// \details O(n) time complexity, where n is the number of nodes in the binary tree.
        /// \example tree.traverse_pre_order([](const int& val) { std::cout << val << ' '; }); // (1,2,3,4,5) -> 3 2 1 5 4 \n
        ///           3 (1)     \n
        ///          / \        \n
        ///     (2) 2   5 (4)   \n
        ///        /   /        \n
        ///   (3) 1   4 (5)
        void traverse_pre_order(std::function<void(const T&)> callback) const noexcept;

        /// \brief Traverses the binary tree in post-order, it's called recursively.
        /// \param current The current node to traverse the binary tree from.
        /// \param callback The function to call for each node in the binary tree.
        /// \details O(n) time complexity, where n is the number of nodes in the binary tree.
        /// \example tree.traverse_post_order(root.get(), [](const int& val) { std::cout << val << ' '; }); // (1,2,3,4,5) -> 1 2 4 5 3 \n
        ///           3 (5)     \n
        ///          / \        \n
        ///     (2) 2   5 (4)   \n
        ///        /   /        \n
        ///   (1) 1   4 (3)
        void traverse_post_order(const node* current, std::function<void(const T&)> callback) const noexcept;

        /// \brief Traverses the binary tree in post-order, it's called recursively.
        /// \param callback The function to call for each node in the binary tree.
        /// \details O(n) time complexity, where n is the number of nodes in the binary tree.
        /// \example tree.traverse_post_order([](const int& val) { std::cout << val << ' '; }); // (1,2,3,4,5) -> 1 2 4 5 3 \n
        ///           3 (5)     \n
        ///          / \        \n
        ///     (2) 2   5 (4)   \n
        ///        /   /        \n
        ///   (1) 1   4 (3)
        void traverse_post_order(std::function<void(const T&)> callback) const noexcept;


        /// \brief Finds the minimum value in the binary tree, it's called recursively.
        /// \param current The current node to find the minimum value from.
        /// \return The node with the minimum value in the binary tree.
        /// \details O(log n) time complexity assuming the binary tree is balanced. \n
        ///          O(n) time complexity in the worst case (when the tree is unbalanced).
        NODISCARD const node* find_min(const node* current) const noexcept;

        /// \brief Finds the minimum value in the binary tree, using the predicate given.
        /// \return The minimum value in the binary tree.
        /// \example int min = tree.find_min();  // (1,2,3,4,5) -> 1    \n
        ///           3         \n
        ///          / \        \n
        ///         2   5       \n
        ///        /   /        \n
        /// (min) 1   4
        /// \details O(log n) time complexity assuming the binary tree is balanced. \n
        ///          O(n) time complexity in the worst case (when the tree is unbalanced).
        NODISCARD const node* find_min() const noexcept;

        /// \brief Finds the maximum value in the binary tree, it's called recursively.
        /// \param current The current node to find the maximum value from.
        /// \return The node with the maximum value in the binary tree.
        /// \details O(log n) time complexity assuming the binary tree is balanced. \n
        ///          O(n) time complexity in the worst case (when the tree is unbalanced).
        NODISCARD const node* find_max(const node* current) const noexcept;

        /// \brief Finds the maximum value in the binary tree, using the predicate given.
        /// \return The maximum value in the binary tree.
        /// \example int max = tree.find_max();  // (1,2,3,4,5) -> 5    \n
        ///           3         \n
        ///          / \        \n
        ///         2   5 (max) \n
        ///        /   /        \n
        ///       1   4
        /// \details O(log n) time complexity assuming the binary tree is balanced. \n
        ///          O(n) time complexity in the worst case (when the tree is unbalanced).
        NODISCARD const node* find_max() const noexcept;

        /// \brief Checks if the binary tree is empty.
        /// \return True if the binary tree is empty, false otherwise.
        /// \example if (tree.is_empty()) std::cout << "The tree is empty!";
        /// \details O(1) time complexity.
        NODISCARD bool is_empty() const noexcept;

        /// \brief Calculates the height of the binary tree, it's called recursively.
        /// \param current The current node to calculate the height from.
        /// \return The height of the binary tree.
        /// \example int h = tree.height(); // (1,2,3,4,5) -> 3    \n
        /// 1         3         \n
        ///          / \        \n
        /// 2       2   5       \n
        ///        /   /        \n
        /// 3     1   4
        /// \details O(n) time complexity, where n is the number of nodes in the binary tree.
        NODISCARD std::size_t height(const node* current) const noexcept;

        /// \brief Calculates the height of the binary tree.
        /// \return The height of the binary tree.
        /// \example int h = tree.height(); // (1,2,3,4,5) -> 3    \n
        /// 1         3         \n
        ///          / \        \n
        /// 2       2   5       \n
        ///        /   /        \n
        /// 3     1   4
        /// \details O(n) time complexity, where n is the number of nodes in the binary tree.
        NODISCARD std::size_t height() const noexcept;

    protected:
        /// \brief Inserts the given value into the binary tree, meant to be a helper function for the public insert function.
        /// \param current The current node to insert the value into.
        /// \param val The value to insert into the binary tree.
        /// \details This function is called recursively to insert the value into the binary tree.
        /// \details O(log n) time complexity assuming the binary tree is balanced. \n
        ///          O(n) time complexity in the worst case (when the tree is unbalanced).
        void insert(std::unique_ptr<node>& current, T val);

        /// \brief Builds a balanced binary tree from the given values, meant to be a helper function for the public build function.
        /// \param current The current node to insert the values into.
        /// \param values The values to insert into the binary tree.
        /// \param size The number of values to insert into the binary tree.
        /// \details This function is called recursively to build a balanced binary tree from the given values.
        /// \details O(n) time complexity.
        void build(std::unique_ptr<node>& current, const T* values, std::size_t size);

        /// \brief Deletes a node from the binary tree, meant to be a helper function for the public delete_node function.
        /// \param current The current node to delete the value from.
        /// \param val The value of the node to delete.
        /// \param prefer_left Whether to prefer the left child to replace the node when deleting a node.
        /// \return True if the node was deleted, false otherwise.
        /// \details This function is called recursively to delete the node with the given value from the binary tree.
        /// \details O(log n) time complexity assuming the binary tree is balanced. \n
        ///          O(n) time complexity in the worst case (when the tree is unbalanced).
        bool remove(std::unique_ptr<node>& current, T val, bool prefer_left);

    }; // class binary_tree

    // binary_tree implementation start

    template<typename T>
    binary_tree<T>::binary_tree(std::function<bool(const T&, const T&)> predicate) noexcept : predicate(
            std::move(predicate)), root(nullptr) {}


    template<typename T>
    void binary_tree<T>::clear() noexcept {
        if (root)
            root.reset();
    }

    template<typename T>
    template<typename Iterator, typename>
    void binary_tree<T>::build(const Iterator begin, const Iterator end) noexcept {
        build(&(*begin), std::distance(begin, end));
    }

    template<typename T>
    void binary_tree<T>::build(const T* values, std::size_t size) noexcept {
        clear();
        if (size == 0) return;

        std::size_t mid = size / 2;
        root = std::make_unique<node>(values[mid]);
        build(root->left, values, mid);
        build(root->right, values + mid + 1, size - mid - 1);
    }

    template<typename T>
    template<typename... Args>
    void binary_tree<T>::build(T val, Args... args) noexcept {
        std::initializer_list<T> values = { val, args... };
        build(values.begin(), values.size());
    }

    template<typename T>
    void binary_tree<T>::insert(const T* values, std::size_t size) noexcept {
        if (!root) { // If the tree is empty
            root = std::make_unique<node>(values[0]);
            ++values;
            --size;
        }

        for (std::size_t i = 0; i < size; ++i) {
            insert(root, values[i]);
        }
    }

    template<typename T>
    template<typename... Args>
    void binary_tree<T>::insert(T val, Args... args) noexcept {
        std::initializer_list<T> values = { val, args... };
        insert(values.begin(), values.end());
    }

    template<typename T>
    template<typename Iterator, typename>
    void binary_tree<T>::insert(Iterator begin, Iterator end) noexcept {
        insert(&(*begin), std::distance(begin, end));
    }

    template<typename T>
    bool binary_tree<T>::contains(T val) const noexcept {
        return contains(root.get(), val);
    }

    template<typename T>
    const typename binary_tree<T>::node* binary_tree<T>::find(const binary_tree::node* current, T val) const noexcept {
        if (!current) return nullptr;
        if (val == current->data) return current;

        return predicate(val, current->data) ? find(current->left.get(), val) : find(current->right.get(), val);
    }

    template<typename T>
    const typename binary_tree<T>::node* binary_tree<T>::find(T val) const noexcept {
        return find(root.get(), val);
    }

    template<typename T>
    void binary_tree<T>::traverse_in_order(const binary_tree::node* current,
                                           std::function<void(const T&)> callback) const noexcept {
        if (!current) return;
        traverse_in_order(current->left.get(), callback);
        callback(current->data);
        traverse_in_order(current->right.get(), callback);
    }

    template<typename T>
    void binary_tree<T>::traverse_in_order(std::function<void(const T&)> callback) const noexcept {
        traverse_in_order(root.get(), callback);
    }

    template<typename T>
    void binary_tree<T>::traverse_pre_order(const binary_tree::node* current,
                                            std::function<void(const T&)> callback) const noexcept {
        if (!current) return;

        callback(current->data);
        traverse_pre_order(current->left.get(), callback);
        traverse_pre_order(current->right.get(), callback);
    }

    template<typename T>
    void binary_tree<T>::traverse_pre_order(std::function<void(const T&)> callback) const noexcept {
        traverse_pre_order(root.get(), callback);
    }

    template<typename T>
    void binary_tree<T>::traverse_post_order(std::function<void(const T&)> callback) const noexcept {
        traverse_post_order(root.get(), callback);
    }

    template<typename T>
    void binary_tree<T>::traverse_post_order(const binary_tree::node* current,
                                             std::function<void(const T&)> callback) const noexcept {
        if (!current) return;

        traverse_post_order(current->left.get(), callback);
        traverse_post_order(current->right.get(), callback);
        callback(current->data);
    }

    template<typename T>
    const typename binary_tree<T>::node* binary_tree<T>::find_min(const binary_tree::node* current) const noexcept {
        if (!current->left) return current;
        return find_min(current->left.get());
    }

    template<typename T>
    const typename binary_tree<T>::node* binary_tree<T>::find_min() const noexcept {
        return find_min(root.get());
    }

    template<typename T>
    const typename binary_tree<T>::node* binary_tree<T>::find_max(const binary_tree::node* current) const noexcept {
        if (!current->right) return current;
        return find_max(current->right.get());
    }

    template<typename T>
    const typename binary_tree<T>::node* binary_tree<T>::find_max() const noexcept {
        return find_max(root.get());
    }

    template<typename T>
    bool binary_tree<T>::is_empty() const noexcept {
        return !root;
    }

    template<typename T>
    std::size_t binary_tree<T>::height(const binary_tree::node* current) const noexcept {
        if (!current) return 0;
        return 1 + std::max(height(current->left.get()), height(current->right.get()));
    }

    template<typename T>
    std::size_t binary_tree<T>::height() const noexcept {
        return height(root.get());
    }

    // helper function for insert
    template<typename T>
    void binary_tree<T>::insert(std::unique_ptr<node>& current, T val) {
        if (predicate(val, current->data)) {
            if (current->left) insert(current->left, val);
            else current->left = std::make_unique<node>(val);
        } else {
            if (current->right) insert(current->right, val);
            else current->right = std::make_unique<node>(val);
        }
    }

    // helper function for build
    template<typename T>
    void binary_tree<T>::build(std::unique_ptr<node>& current, const T* values, std::size_t size) {
        if (size == 0) return;
        if (size == 1) {
            current = std::make_unique<node>(values[0]);
            return;
        }
        std::size_t mid = size / 2;
        current = std::make_unique<node>(values[mid]);
        build(current->left, values, mid);
        build(current->right, values + mid + 1, size - mid - 1);
    }

    template<typename T>
    bool binary_tree<T>::remove(T val, bool prefer_left) noexcept {
        return remove(root, val, prefer_left);
    }

    template<typename T>
    bool binary_tree<T>::contains(const binary_tree::node* current, T val) const noexcept {
        if (!current) return false;
        if (val == current->data) return true;

        return predicate(val, current->data) ? contains(current->left.get(), val) : contains(current->right.get(),
                                                                                             val);
    }

    // helper function for remove
    template<typename T>
    bool binary_tree<T>::remove(std::unique_ptr<node>& current, T val, bool prefer_left) {
        if (!current) return false;

        if (val == current->data) {
            if (!current->left && !current->right) { // No children
                current.reset();
                return true;
            }

            if (!current->left) { // Only right child
                current = std::move(current->right);
                return true;
            }

            if (!current->right) { // Only left child
                current = std::move(current->left);
                return true;
            }

            // Both children
            // In this case we find the max of the left child
            if (prefer_left) {
                const node* max = find_max(current->left.get());
                current->data = max->data;
                return remove(current->left, max->data, prefer_left);
            } // In this case we find the min of the right child
            else {
                const node* min = find_min(current->right.get());
                current->data = min->data;
                return remove(current->right, min->data, prefer_left);
            }
        }

        return predicate(val, current->data) ? remove(current->left, val, prefer_left) : remove(current->right, val,
                                                                                                prefer_left);
    }

    // binary_tree implementation end

} // namespace bardrix
