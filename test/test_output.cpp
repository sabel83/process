// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <process/output.hpp>

#include <boost/test/unit_test.hpp>

using namespace process;

BOOST_AUTO_TEST_CASE(test_output_empty_stdout)
{
  output o("", "");

  BOOST_CHECK_EQUAL("", o.standard_output());
}

BOOST_AUTO_TEST_CASE(test_output_stdout)
{
  output o("normal", "");

  BOOST_CHECK_EQUAL("normal", o.standard_output());
}

BOOST_AUTO_TEST_CASE(test_output_empty_stderr)
{
  output o("", "");

  BOOST_CHECK_EQUAL("", o.standard_error());
}

BOOST_AUTO_TEST_CASE(test_output_stderr)
{
  output o("", "error");

  BOOST_CHECK_EQUAL("error", o.standard_error());
}


