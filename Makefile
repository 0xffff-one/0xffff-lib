all: format test

format:
	@buildifier -r .
	@find . -iname "*.cc" -or -iname "*.h" | xargs clang-format -i

simple-test:
	@bazel test tests

test:
	@bazel test tests --keep_going --test_output=all

clean:
	@bazel clean
