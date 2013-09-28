// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <process/process.hpp>

#include "util.hpp"

#include <boost/test/unit_test.hpp>

#include <boost/assign/list_of.hpp>

#include <vector>
#include <string>

using namespace process;

BOOST_AUTO_TEST_CASE(test_command_is_executed)
{
  using std::vector;
  using std::string;
  using boost::assign::list_of;

  const vector<string> cmd = list_of<string>
    ("/bin/bash")("-c")("echo hello > " + temp_filename);

  write_file(temp_filename, "something but hello");
  run(cmd, "");

  BOOST_CHECK_EQUAL("hello\n", read_file(temp_filename));
}

BOOST_AUTO_TEST_CASE(test_output_of_command)
{
  using std::vector;
  using std::string;
  using boost::assign::list_of;

  const vector<string> cmd = list_of<string>
    ("/bin/bash")("-c")("echo hello");

  const output o = run(cmd, "");

  BOOST_CHECK_EQUAL("hello\n", o.standard_output());
}

BOOST_AUTO_TEST_CASE(test_error_of_command)
{
  using std::vector;
  using std::string;
  using boost::assign::list_of;

  const vector<string> cmd = list_of<string>
    ("/bin/bash")("-c")("echo hello 1>&2");

  const output o = run(cmd, "");

  BOOST_CHECK_EQUAL("hello\n", o.standard_error());
}

BOOST_AUTO_TEST_CASE(test_input_of_command)
{
  using std::vector;
  using std::string;
  using boost::assign::list_of;

  const vector<string> cmd(1, "/bin/cat");

  const output o = run(cmd, "hello world");

  BOOST_CHECK_EQUAL("hello world", o.standard_output());
}

BOOST_AUTO_TEST_CASE(test_invalid_command)
{
  using std::vector;
  using std::string;

  const vector<string> cmd(1, "/some_invalid_command");

  const output o = run(cmd, "");

  BOOST_CHECK_EQUAL("", o.standard_output());
  BOOST_CHECK_EQUAL("", o.standard_error());
}



