# Conventions

## 1. Introduction

This document describes the conventions used in the code and documentation of the project. All future code and
documentation should follow these conventions. The conventions are divided into the following sections:

1. [Naming Conventions](#2-naming-conventions)
2. [Code Conventions](#3-code-conventions)
3. [Documentation Conventions](#4-documentation-conventions)
4. [Commit Message Conventions](#5-commit-message-conventions)
5. [Branch Naming Conventions](#6-branch-naming-conventions)
6. [Pull Request Conventions](#7-pull-request-conventions)
7. [Issue Conventions](#8-issue-conventions)
8. [Project Management Conventions](#9-project-management-conventions)
9. [Testing Conventions](#10-testing-conventions)
10. [Continuous Integration Conventions](#11-continuous-integration-conventions)
11. [Deployment Conventions](#12-deployment-conventions)
12. [Security Conventions](#13-security-conventions)
13. [Legal Conventions](#14-legal-conventions)
14. [Conclusion](#15-conclusion)
15. [References](#16-references)

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
