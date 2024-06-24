//
// Created by Bardio on 22/06/2024.
//

#pragma once

#include <bardrix/bardrix.h>
#include <bardrix/objects.h>

namespace bardrix {

    /// \brief Represents a binary tree, which is a tree data structure in which each node has at most two children.  \n
    ///        The use of duplicates is not allowed, it will be ignored when inserting.                               \n
    /// \tparam T The type of the values in the binary tree, e.g int, double, point3, etc.
    /// \example       5        \n
    ///              /  \       \n
    ///             3    7      \n
    ///            / \   / \    \n
    ///           1   4 6   8
    template<typename T>
    class binary_tree {
    public:
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
            explicit node(T val) : node(std::move(val), nullptr, nullptr) {}

            /// \brief Constructs a node with the given value and children.
            /// \param val The value of the node.
            /// \param left The left child of the node.
            /// \param right The right child of the node.
            node(T val, std::unique_ptr<node> left, std::unique_ptr<node> right) : data(std::move(val)),
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
        explicit binary_tree(std::function<bool(const T&, const T&)> predicate);

        /// \brief Clears the binary tree, removing all nodes.
        /// \example tree.clear(); // Removes all nodes from the binary tree.
        void clear();

        /// \brief Builds a balanced binary tree from the given values.                                             \n
        ///        For a balanced tree the values should be sorted in ascending order. (e.g 1, 2, 3, 4, 5, 6, 7, 8) \n
        ///        The sorting should adhere to the predicate given in the constructor.                             \n
        ///        The use of duplicates is not allowed.
        /// \param values The values to insert into the binary tree.
        /// \param size The number of values to insert into the binary tree.
        /// \example int values[] = {1, 2, 3, 4, 5, 6, 7, 8}; tree.build(values, 8); // Builds a balanced binary tree with the values 1, 2, 3, 4, 5, 6, 7, and 8. (Assuming the tree is of type int) \n
        ///          5        \n
        ///         / \       \n
        ///        3   7      \n
        ///       / \ / \     \n
        ///      2  4 6  8    \n
        ///     /             \n
        ///    1              \n
        /// \note Use this function for a balanced binary tree.
        void build(const T* values, std::size_t size);

        /// \brief Builds a balanced binary tree from the given values.                                             \n
        ///        For a balanced tree the values should be sorted in ascending order. (e.g 1, 2, 3, 4, 5, 6, 7, 8) \n
        ///        The sorting should adhere to the predicate given in the constructor.                             \n
        ///        The use of duplicates is not allowed.
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
        ///    1              \n
        /// \note Use this function for a balanced binary tree.
        template<typename... Args>
        void build(T val, Args... args);

        /// \brief Inserts the given values into the binary tree.           \n
        ///        The values are inserted in the order they are given.     \n
        ///        Use build function for a balanced binary tree.
        /// \tparam Args The types of the values to insert into the binary tree.
        /// \param val The first value to insert into the binary tree.
        /// \param args Other values to insert into the binary tree.
        /// \example tree.insert(1, 2, 3, 4, 5); \n
        ///          1          \n
        ///         / \         \n
        ///        2   3        \n
        ///             \       \n
        ///              4      \n
        ///               \     \n
        ///                5    \n
        /// \note Do not use this function for a balanced binary tree, use the build function instead.
        /// \note The use of duplicates is not allowed.
        template<typename... Args>
        void insert(T val, Args... args);

        /// \brief Inserts the given values into the binary tree.           \n
        ///        The values are inserted in the order they are given.     \n
        ///        Use build function for a balanced binary tree.
        /// \param val The value to insert into the binary tree.
        /// \example tree.insert(1); // Inserts the value 1 into the binary tree. (Assuming the tree is of type int)
        /// \note Do not use this function for a balanced binary tree, use the build function instead.
        /// \note The use of duplicates is not allowed.
        void insert(T val);

        /// \brief Inserts the given values into the binary tree.           \n
        ///        The values are inserted in the order they are given.     \n
        ///        Use build function for a balanced binary tree.
        /// \param values The values to insert into the binary tree.
        /// \param size The number of values to insert into the binary tree.
        /// \example int values[] = {1, 2, 3, 4, 5}; tree.insert(values, 5); // Inserts the values 1, 2, 3, 4, and 5 into the binary tree. (Assuming the tree is of type int)
        /// \example std::vector<int> values = {1, 2, 3, 4, 5}; tree.insert(values.data(), values.size()); \n
        ///          1          \n
        ///         / \         \n
        ///        2   3        \n
        ///             \       \n
        ///              4      \n
        ///               \     \n
        ///                5    \n
        /// \note Do not use this function for a balanced binary tree, use the build function instead.
        /// \note The use of duplicates is not allowed.
        void insert(const T* values, std::size_t size);

        /// \brief Deletes a node from the binary tree.
        /// \param val The value of the node to delete.
        /// \details This function deletes the node with the given value from the binary tree.
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
        ///    1                        \n
        void remove(T val);

        /// \brief Checks if the binary tree contains the given value, meant to be a helper function for the public contains function.
        /// \param current The current node to check if it contains the value.
        /// \param val The value to check if it is in the binary tree.
        /// \return True if the binary tree contains the value, false otherwise.
        /// \details This function is called recursively to check if the binary tree contains the value.
        NODISCARD bool contains(const node* current, T val) const;

        /// \brief Checks if the binary tree contains the given value.
        /// \param val The value to check if it is in the binary tree.
        /// \return True if the binary tree contains the value, false otherwise.
        /// \example if (tree.contains(3)) std::cout << "The tree contains the value 3!";
        NODISCARD bool contains(T val) const;

        /// \brief Finds the node with the given value, it's called recursively.
        /// \param current The current node to find the value from.
        /// \param val The value to find in the binary tree.
        /// \return The node with the given value in the binary tree.
        /// \details This function is called recursively to find the node with the given value in the binary tree.
        NODISCARD const node* find(const node* current, T val) const;

        /// \brief Finds the node with the given value.
        /// \param val The value to find in the binary tree.
        /// \return The node with the given value in the binary tree.
        /// \example const node* node = tree.find(3); // (1,2,3,4,5) -> node with value 3
        NODISCARD const node* find(T val) const;

        /// \brief Traverses the binary tree in pre-order, it's called recursively.
        /// \param current The current node to traverse the binary tree from.
        /// \param func The function to call for each node in the binary tree.
        /// \details This function is called recursively to traverse the binary tree in pre-order.  \n
        ///          This means that the current node is visited first, then the left child recursively, when it reaches the end it goes to the right child then recursively to the left child and so on.
        void traverse_in_order(const node* current, std::function<void(const T&)> func) const;

        /// \brief Traverses the binary tree in pre-order, it's called recursively.
        /// \param current The current node to traverse the binary tree from.
        /// \param func The function to call for each node in the binary tree.
        /// \details This function is called recursively to traverse the binary tree in pre-order.  \n
        ///          This means that the current node is visited first, then the left child recursively, when it reaches the end it goes to the right child then recursively to the left child and so on.
        void traverse_in_order(std::function<void(const T&)> func) const;

        /// \brief Finds the minimum value in the binary tree, it's called recursively.
        /// \param current The current node to find the minimum value from.
        /// \return The node with the minimum value in the binary tree.
        /// \details This function is called recursively to find the minimum value in the binary tree.
        NODISCARD const node* find_min(const node* current) const;

        /// \brief Finds the minimum value in the binary tree, using the predicate given.
        /// \return The minimum value in the binary tree.
        /// \example int min = tree.find_min();  // (1,2,3,4,5) -> 1    \n
        ///           3         \n
        ///          / \        \n
        ///         2   5       \n
        ///        /   /        \n
        /// (min) 1   4         \n
        NODISCARD const node* find_min() const;

        /// \brief Finds the maximum value in the binary tree, it's called recursively.
        /// \param current The current node to find the maximum value from.
        /// \return The node with the maximum value in the binary tree.
        /// \details This function is called recursively to find the maximum value in the binary tree.
        NODISCARD const node* find_max(const node* current) const;

        /// \brief Finds the maximum value in the binary tree, using the predicate given.
        /// \return The maximum value in the binary tree.
        /// \example int max = tree.find_max();  // (1,2,3,4,5) -> 5    \n
        ///           3         \n
        ///          / \        \n
        ///         2   5 (max) \n
        ///        /   /        \n
        ///       1   4         \n
        NODISCARD const node* find_max() const;

        /// \brief Checks if the binary tree is empty.
        /// \return True if the binary tree is empty, false otherwise.
        /// \example if (tree.is_empty()) std::cout << "The tree is empty!";
        NODISCARD bool is_empty() const;

        /// \brief Calculates the height of the binary tree, it's called recursively.
        /// \param current The current node to calculate the height from.
        /// \return The height of the binary tree.
        /// \details This function is called recursively to calculate the height of the binary tree.
        NODISCARD int height(const node* current) const;

        /// \brief Calculates the height of the binary tree.
        /// \return The height of the binary tree.
        /// \example int h = tree.height(); // (1,2,3,4,5) -> 3    \n
        NODISCARD int height() const;

    protected:
        /// \brief Inserts the given value into the binary tree, meant to be a helper function for the public insert function.
        /// \param current The current node to insert the value into.
        /// \param val The value to insert into the binary tree.
        /// \details This function is called recursively to insert the value into the binary tree.
        void insert(std::unique_ptr<node>& current, T val);

        /// \brief Builds a balanced binary tree from the given values, meant to be a helper function for the public build function.
        /// \param current The current node to insert the values into.
        /// \param values The values to insert into the binary tree.
        /// \param size The number of values to insert into the binary tree.
        /// \details This function is called recursively to build a balanced binary tree from the given values.
        void build(std::unique_ptr<node>& current, const T* values, std::size_t size);

        /// \brief Deletes a node from the binary tree, meant to be a helper function for the public delete_node function.
        /// \param current The current node to delete the value from.
        /// \param val The value of the node to delete.
        /// \details This function is called recursively to delete the node with the given value from the binary tree.
        void remove(std::unique_ptr<node>& current, T val);

    }; // class binary_tree

    // binary_tree implementation start

    template<typename T>
    binary_tree<T>::binary_tree(std::function<bool(const T&, const T&)> predicate) : predicate(std::move(predicate)),
                                                                                     root(nullptr) {}


    template<typename T>
    void binary_tree<T>::clear() {
        if (root)
            root.reset();
    }

    template<typename T>
    void binary_tree<T>::build(const T* values, std::size_t size) {
        clear();
        if (size == 0) return;

        std::size_t mid = size / 2;
        root = std::make_unique<node>(values[mid]);
        build(root->left, values, mid);
        build(root->right, values + mid + 1, size - mid - 1);
    }

    template<typename T>
    template<typename... Args>
    void binary_tree<T>::build(T val, Args... args) {
        std::initializer_list<T> values = { val, args... };
        build(values.begin(), values.size());
    }

    template<typename T>
    void binary_tree<T>::insert(const T* values, std::size_t size) {
        for (std::size_t i = 0; i < size; ++i)
            insert(values[i]);
    }

    template<typename T>
    void binary_tree<T>::insert(T val) {
        if (!root) root = std::make_unique<node>(val);
        else insert(root, val);
    }

    template<typename T>
    template<typename... Args>
    void binary_tree<T>::insert(T val, Args... args) {
        insert(val);
        insert(args...);
    }

    template<typename T>
    bool binary_tree<T>::contains(T val) const {
        return contains(root.get(), val);
    }

    template<typename T>
    const typename binary_tree<T>::node* binary_tree<T>::find(const binary_tree::node* current, T val) const {
        if (!current) return nullptr;
        if (val == current->data) return current;

        return predicate(val, current->data) ? find(current->left.get(), val) : find(current->right.get(), val);
    }

    template<typename T>
    const typename binary_tree<T>::node* binary_tree<T>::find(T val) const {
        return find(root.get(), val);
    }

    template<typename T>
    void binary_tree<T>::traverse_in_order(const binary_tree::node* current, std::function<void(const T&)> func) const {
        if (!current) return;
        traverse_in_order(current->left.get(), func);
        func(current->data);
        traverse_in_order(current->right.get(), func);
    }

    template<typename T>
    void binary_tree<T>::traverse_in_order(std::function<void(const T&)> func) const {
        traverse_in_order(root.get(), func);
    }

    template<typename T>
    const typename binary_tree<T>::node* binary_tree<T>::find_min(const binary_tree::node* current) const {
        if (!current->left) return current;
        return find_min(current->left.get());
    }

    template<typename T>
    const typename binary_tree<T>::node* binary_tree<T>::find_min() const {
        return find_min(root.get());
    }

    template<typename T>
    const typename binary_tree<T>::node* binary_tree<T>::find_max(const binary_tree::node* current) const {
        if (!current->right) return current;
        return find_max(current->right.get());
    }

    template<typename T>
    const typename binary_tree<T>::node* binary_tree<T>::find_max() const {
        return find_max(root.get());
    }

    template<typename T>
    bool binary_tree<T>::is_empty() const {
        return !root;
    }

    template<typename T>
    int binary_tree<T>::height(const binary_tree::node* current) const {
        if (!current) return 0;
        return 1 + std::max(height(current->left.get()), height(current->right.get()));
    }

    template<typename T>
    int binary_tree<T>::height() const {
        return height(root.get());
    }

    // helper function for insert
    template<typename T>
    void binary_tree<T>::insert(std::unique_ptr<node>& current, T val) {
        if (val == current->data) return; // Avoid duplicates

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
    void binary_tree<T>::remove(T val) {
        remove(root, val);
    }

    template<typename T>
    bool binary_tree<T>::contains(const binary_tree::node* current, T val) const {
        if (!current) return false;
        if (val == current->data) return true;

        return predicate(val, current->data) ? contains(current->left.get(), val) : contains(current->right.get(),
                                                                                             val);
    }

    // helper function for remove
    template<typename T>
    void binary_tree<T>::remove(std::unique_ptr<node>& current, T val) {
        if (!current) return;

        if (val == current->data) {
            if (!current->left) current = std::move(current->right);
            else if (!current->right) current = std::move(current->left);
            else {
                const node* min = find_min(current->right.get());
                current->data = min->data;
                remove(current->right, min->data);
            }
        } else if (predicate(val, current->data)) remove(current->left, val);
        else remove(current->right, val);
    }

    // binary_tree implementation end

} // namespace bardrix
