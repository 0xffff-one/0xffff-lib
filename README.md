# 0xffff-lib

[![Build Status](https://travis-ci.com/tikv/client-go.svg?branch=master)](https://travis-ci.com/tikv/client-go)

## Motivation

`0xffff-lib` is a low level core library whose goal is enabling newbie to be familiar with modern C++ development, computer science's core courses and how to contribute to open source project by building a data-structure and algorithm library from scratch with the help of testing framework [`googletest`](https://github.com/google/googletest) and building system [`bazel`](https://www.bazel.build/).

## Compilation

### Dependency

1. Install `bazel` which is a build system used to build our library: https://docs.bazel.build/versions/master/install.html
2. Install `g++`, which is the default c++ compiler in many Linux distribution.

### Testing

1. `bazel test`: if you just want to check if any test failed.
2. `bazel test tests --test_output=all`: if you want more verbose information.

## Project structure

Currently, our library is quite simple and crude, we need more contributors to enhance it which is one of the project's motivations: encourage newbie to contribute to open source project.

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

### Add modules

For instance, if we are going to a matrix calculation module to our library. Considering the module doesn't belong to any existing module, we need to add a directory called `matrix` for logical need. Now our `src` directory looks like:

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

In the example above, we need a `BUILD` file to describe how to build `matrix` module. The `BUILD` file is read by `bazel` and determine how the module build and visibility to other modules. Now let's see how to write such a `BUILD` file from scratch.

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

Now we have successfully added a module to our library, now it's time to add some tests to examine if the module works as we expected.
For now, all the tests live in `tests` which is also a package managed by `bazel`. So it contains a `BUILD` file. Let's check out its content:

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

Then, we can run the test by: `bazel test` and check if the function of the module works as expected.

## Contribution

CI support is coming. And we will make some tags in the issues including:

* Feature request; There will detailed document to describe the proposal.
    * Easy
    * Medium
    * Hard
* Help wanted

