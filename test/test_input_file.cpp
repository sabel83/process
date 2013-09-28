// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <process/impl/input_file.hpp>

#include "util.hpp"

#include <boost/test/unit_test.hpp>

#include <sys/stat.h>
#include <fcntl.h>

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace process::impl;

BOOST_AUTO_TEST_CASE(test_destructor_closing_input_file)
{
  write_file(temp_filename, "foo");
  const int fd = open(temp_filename.c_str(), O_RDONLY);
  {
    input_file f(fd);
  }

  BOOST_CHECK(!file_descriptor_is_open(fd));
}

BOOST_AUTO_TEST_CASE(test_read_from_input_file)
{
  write_file(temp_filename, "foo");
  input_file f(open(temp_filename.c_str(), O_RDONLY));
  char buffer;

  BOOST_CHECK_EQUAL(1, f.read(&buffer, 1));
}

BOOST_AUTO_TEST_CASE(test_read_content_input_file)
{
  write_file(temp_filename, "foo");
  input_file f(open(temp_filename.c_str(), O_RDONLY));
  char buffer;

  BOOST_CHECK_EQUAL(1, f.read(&buffer, 1));
}

BOOST_AUTO_TEST_CASE(test_read_first_byte_of_input_file)
{
  write_file(temp_filename, "foo");

  input_file f(open(temp_filename.c_str(), O_RDONLY));
  char buffer;
  f.read(&buffer, 1);

  BOOST_CHECK_EQUAL('f', buffer);
}

BOOST_AUTO_TEST_CASE(test_read_entire_input_file)
{
  write_file(temp_filename, "foo");
  std::vector<char> buff(3);

  input_file f(open(temp_filename.c_str(), O_RDONLY));
  f.read(&buff[0], buff.size());

  BOOST_CHECK_EQUAL("foo", std::string(buff.begin(), buff.end()));
}

BOOST_AUTO_TEST_CASE(test_not_eof)
{
  write_file(temp_filename, "foo");
  input_file f(open(temp_filename.c_str(), O_RDONLY));

  BOOST_CHECK(!f.eof());
}

BOOST_AUTO_TEST_CASE(test_eof_at_end_of_file)
{
  write_file(temp_filename, "foo");
  std::vector<char> buff(3);

  input_file f(open(temp_filename.c_str(), O_RDONLY));
  f.read(&buff[0], buff.size());
  f.read(&buff[0], 1);

  BOOST_CHECK(f.eof());
}

BOOST_AUTO_TEST_CASE(test_read_entire_file)
{
  write_file(temp_filename, "foo bar");
  input_file f(open(temp_filename.c_str(), O_RDONLY));

  BOOST_CHECK_EQUAL("foo bar", f.read());
}

BOOST_AUTO_TEST_CASE(test_close_input_file)
{
  write_file(temp_filename, "foo");
  const int fd = open(temp_filename.c_str(), O_RDONLY);
  input_file f(fd);
  f.close();

  BOOST_CHECK(!file_descriptor_is_open(fd));
}



