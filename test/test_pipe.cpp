// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <process/impl/pipe.hpp>

#include "util.hpp"

#include <boost/test/unit_test.hpp>

using namespace process::impl;

BOOST_AUTO_TEST_CASE(test_pipe_creation)
{
  process::impl::pipe();
}

BOOST_AUTO_TEST_CASE(test_pipe_write_and_read)
{
  process::impl::pipe p;
  p.output.write("Hello");
  p.output.close();

  BOOST_CHECK_EQUAL("Hello", p.input.read());
}

