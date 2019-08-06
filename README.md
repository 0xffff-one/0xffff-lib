# 0xffff-lib

[![Build Status](https://travis-ci.org/0xffff-one/0xffff-lib.svg?branch=master)](https://travis-ci.org/0xffff-one/0xffff-lib)

## Motivation

`0xffff-lib` is a low-level core library, with a goal of encouraging newbies to become familiar with modern C++ development, core courses of computer science, and how to contribute to open source projects by building a data structure and algorithm library from scratch with the help of testing framework [`googletest`](https://github.com/google/googletest) and building system [`bazel`](https://www.bazel.build/).

## Compilation

### Dependencies

1. Install `bazel`, which is a build system used to build our library: https://docs.bazel.build/versions/master/install.html
2. Install `g++`, which is the default c++ compiler in mainstream Linux distributions.

### Testing

1. `bazel test`: to run all tests.
2. `bazel test tests --test_output=all`: for verbose information.

## Project structure

Currently, our library is quite simple and crude. We need more contributors to enhance it, which is one of the project's motivations: encourage newbies to contribute to open source projects.

```
.
├── README.md
├── src
│   └── collections # Collection type
│       ├── BUILD # Bazel build file
│       └── ...
├── tests # Where testing codes live
│   ├── BUILD
│   └── test-vector.cc
└── WORKSPACE # import extenal dependencies
```

### Tutorial: adding modules

For instance, we are going to add a matrix calculation module to our library. Considering the module is currently non-existent in our library, we need to create a directory called `matrix`. Now our `src` directory looks like this:

```
.
├── collections
│   ├── BUILD
│   └── vector.h
└── matrix
    ├── BUILD
    ├── matrix.cc
    ├── matrix.h
    ├── svd.h
    └── ...
```

As the example above has demonstrated, we need a `BUILD` file to describe how to build the `matrix` module. `bazel` reads the `BUILD` file and determines how the module will be built and its visibility to other modules. Let's see how to write a basic `BUILD` file from scratch.

```bzl
cc_library(
    # Name of our module
    name = "matrix",
    # All file with type `cc` is our sources
    srcs = glob("[*.cc]"),
    # Includes all header file in `hdrs`
    hdrs = glob(["*.h"]),
    # Visible from other package
    visibility = ["//visibility:public"],
)
```

Now we have successfully added a module to our library, it's time to add some tests to examine if the module works as expected.
For now, all the tests reside in the `tests` directory. Since `tests` is a package managed by `bazel`, it contains a `BUILD` file. Let's check out its contents:

```bzl
cc_test(
    name = "tests",
    srcs = glob(["*.cc"]),
    deps = [
        # We need to import the module we want to test
        "//src/collections:vector",
        # New module; or "//src/matrix:matrix"
        "//src/matrix",

        // Import googletest to our tests.
        "@googletest//:gtest_main",
    ],
)
```

Then, we create a file named `test-matrix.cc`:

```c++
#include "src/matrix/matrix.h"
#include <gtest/gtest.h>

TEST(TestMatrix, TestAdd) {
    Matrix<int> lhs({{1, 2, 3});
    Matrix<int> rhs({{0, 0, 0}};
    Matrix<int> expected({1, 2, 3});

    EXPECT_EQ(expected, lhs + rhs);
}
```

Finally, we can run the test by executing `bazel test` and check if the function(s) of the module works as expected.

## Contribution

CI support is coming, and we will tag some issues, including:

* Feature requests; There will detailed documentation about the proposals made by community members.
    * Easy
    * Medium
    * Hard
* Help wanted

