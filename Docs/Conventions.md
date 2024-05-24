# Conventions

## 1. Introduction

This document describes the conventions used in the code and documentation of the project. All future code and
documentation should follow these conventions. The conventions are divided into the following sections:

1. [Naming Conventions](#2-naming-conventions)
2. [Code Conventions](#3-code-conventions)
3. [Testing Conventions](#4-testing-conventions)
4. [Documentation Conventions](#5-documentation-conventions)
5. [Commit Message Conventions](#6-commit-message-conventions)
6. [Branch Naming Conventions](#7-branch-naming-conventions)
7. [Pull Request Conventions](#8-pull-request-conventions)
8. [Issue Conventions](#9-issue-conventions)
9. [Continuous Integration Conventions](#10-continuous-integration-conventions)
10. [Deployment Conventions](#11-deployment-conventions)
11. [Legal Conventions](#12-legal-conventions)
12. [Conclusion](#13-conclusion)
13. [References](#14-references)

## 2. Naming Conventions

### 2.1. General Naming Conventions

Names should be descriptive and unambiguous. They should clearly convey the purpose. Avoid using single letter names or
abbreviations unless they are widely accepted (e.g. `i` for an index in a loop). For example, use `number_of_students`
instead of `n`.

1. **Use snake_case** for variables, functions, classes, namespaces, typedefs, enums. E.g. `foo_bar` instead of `fooBar` or `FooBar`.
2. **Use PascalCase** for generic template variables, e.g. `T`, `FooBar`, etc.
3. **Use UPPER_CASE** for defines, e.g. `MAX_NUMBER_OF_STUDENTS`.
4. **Use a suffix** underscore for private or protected members, e.g. `foo_bar_`.

### 2.2. File Naming Conventions

1. **Use snake_case** for file and directory names, e.g. `foo_bar.h` and `foo_bar/bar_foo.cpp`.
2. **Src and include directories** should be named `src/bardrix` and `include/bardrix` respectively.
3. **Use a suffix** `_test` for test files, e.g. `foo_bar_test.cpp`.
4. **Use directories** to group by namespace, e.g. `src/bardrix/math` and `include/bardrix/math`.

## 3. Code Conventions

### 3.1. General Code Conventions

1. **Use C++17** as the programming language.
2. **Use 4 spaces** for indentation.
3. **Use newline** after namespace, class, function.
4. **Use `#pragma once`** for include guards.
5. **Use `#include`** in the following order:
    1. Related header file.
    2. C++ standard library.
    3. Other libraries.
6. **Use `#include <bardrix/...>`** for internal libraries.
7. **Put** all external header files in `bardrix.h` as this is the main file.

### 3.2. Class Conventions

## 4. Testing Conventions
### 4.1. General Testing Conventions
1. Use Google Test v1.14.0 for unit testing.
2. When writing new tests name the file `foo_bar_test.cpp` where `foo_bar` is the name of the file being tested.
3. Any standard library headers should be included in the pch.h file.
4. Any internal headers should be included in the test file where they are needed.

- Example:
  ```cpp
  #include <bardrix/class_name.h>
  
  /// \brief Test case for the function_name method.
  TEST(class_name, function_name_description) {
      // Test code here
  }
  ```
  - Here the description could be something like `degenerate_case` or `boundary_condition`.
  - Documentation comments are required for each test case.

## 5. Documentation Conventions
### 5.1. General Documentation Conventions
1. Use Markdown for README files and other documentation files.
2. Whenever adding or updating any code update the [Bardrix Reference](Bardrix_Reference.md) file.
3. Whenever adding or updating any code update the [Release Notes](Release_Notes.md) file.

## 5. Code Documentation Conventions
1. Use Doxygen style comments for documenting functions, classes, members, etc.
   - Use `/// \` style for the documentation, no other style is allowed.
   - Example:
     ```cpp
     /// \brief This is a function that does something.
     /// \param x Explanation of the first parameter.
     /// \param y Explanation of the second parameter.
     /// \return Explanation of the return value.
     /// \example Example usage of the function.
     /// \details Detailed explanation of the function.
     /// \note Additional notes.
     /// \exception Exception that can be thrown.
     int foo(int x, int y);
     ```
2. Include examples where appropriate to illustrate usage.
3. Include notes and exceptions where appropriate to provide additional information.

## 6. Commit Message Conventions
1. Reference issues or pull requests when appropriate.
2. Use title and comment for commit messages.

## 7. Branch Naming Conventions
### 7.1. General Branch Naming Conventions