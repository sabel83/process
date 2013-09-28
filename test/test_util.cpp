// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "util.hpp"

#include <boost/test/unit_test.hpp>

#include <sys/stat.h>
#include <fcntl.h>

BOOST_AUTO_TEST_CASE(test_existing_file_exists)
{
  write_file(temp_filename, "foo");
  BOOST_CHECK(file_exists(temp_filename));
}

BOOST_AUTO_TEST_CASE(test_non_existing_file_does_not_exist)
{
  BOOST_CHECK(!file_exists("/etc/no_such_file"));
}

BOOST_AUTO_TEST_CASE(test_open_file_descriptor_is_open)
{
  BOOST_CHECK(file_descriptor_is_open(0));
}

BOOST_AUTO_TEST_CASE(test_closed_file_descriptor_is_not_open)
{
  write_file(temp_filename, "foo");
  const int fd = open(temp_filename.c_str(), O_RDONLY);
  close(fd);

  BOOST_CHECK(!file_descriptor_is_open(fd));
}

BOOST_AUTO_TEST_CASE(test_read_and_write_file)
{
  write_file(temp_filename, "foo bar");
  BOOST_CHECK_EQUAL("foo bar", read_file(temp_filename));
}

