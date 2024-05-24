# Contributing

This project is open source and welcomes contributions. Information on how to contribute can be found here. \
All contributions need to follow the [Code of Conduct](CODE_OF_CONDUCT.md), and the [Conventions](Docs/Conventions.md)
these rules are in place to ensure that the project is consistent and easy to maintain.

Any contributions are welcome, whether it be a bug fix, a new feature, or a documentation update. \
If you find any issues or have any suggestions, please open an issue.

## Setup

### Prerequisites

To get started with contributing, you will need to set up the project on your local machine. \
[Cmake](https://cmake.org/) version [3.27](https://cmake.org/cmake/help/latest/release/3.27.html) is used to build the
project, and [Doxygen](https://www.doxygen.nl/index.html) is used to
generate the documentation. \
C++17 is used in this project, you're able to use compilers like **clang**, **gcc** and **cl** that support C++17.

To help with the development process, you can use an IDE
like [CLion](https://www.jetbrains.com/clion/), [Visual Studio](https://visualstudio.microsoft.com/)
or [Visual Studio Code](https://code.visualstudio.com/). You're also able to run `cmake` manually and use the compiler
of your choice.

## Building the Project

Clone the repository to your local machine.

```bash
git clone https://github.com/BardoBard/Bardrix.git "Bardrix" && cd Bardrix
```

Now we need to build the project. You're also able to specify the compiler, architecture, debug/release, etc. but for a
simple build, you can run the following command.

```bash
cmake -B build -S .
```

This will create a build directory with the necessary files to build the project. \
Now we can compile the project.

```bash
cmake --build build
```

Depending on what operating system you're using, you'll be able to run the tests in **Bardrix_Tests**.

## How to Contribute

If you would like to contribute, please follow the steps below.

1. Fork the repository.
2. Clone the forked repository.
3. Create a new branch.
4. Make your changes.
5. Update the documentation & add tests.
6. Push the changes to your fork.
7. Create a pull request.
8. Make sure all the checks pass.
9. Wait for the pull request to be reviewed.

Make sure to write good commit messages, and follow the conventions in the [Conventions](Docs/Conventions.md) file. \
If you're adding a new feature, make sure to add tests for it. \
If you're fixing a bug, make sure to add a test that reproduces the bug.
Add documentation to the code you've written, and update the [Bardrix_Reference](Docs/Bardrix_Reference.md) and the
[Release Notes](Docs/Release_Notes.md) if necessary.
