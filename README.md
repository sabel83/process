# Process

[![Build Status](https://secure.travis-ci.org/sabel83/process.png?branch=master "Build Status")](http://travis-ci.org/sabel83/process)

Process is a library for running an external process and capturing its standard
output and error.

## Installing the library (Linux)

* Get the source code: `git clone https://github.com/sabel83/process && cd process`
* Create the build directory: `mkdir bin && bin`
* Generate the Makefiles: `cmake ..`
* Build the tests: `make`
* Run the tests: `make test`
* Copy the headers: `make install` (You may need to run this as `root`)

## Usage

You need to include the `<process/process.hpp>` header file which provides the
following template function:

```cpp
template <class Seq>
process::output process::run(const Seq& cmd_, const std::string& input_)
```

The first argument, `cmd_` is a sequence of `std::string` objects. It defines
the command to execute. The second argument, `input_` is what should be passed
to the executed process as its standard input. The function launches the
command and captures its standard output and error. It blocks until the process
terminates and its entire standard output and error is available.

The resulting `output` object contains the captured standard output and error
which can be queried by calling its `standard_output` and `standard_error`
methods.

## License

Process is published under the
[Boost Software License](http://www.boost.org/LICENSE_1_0.txt).


