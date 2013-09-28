// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <process/impl/output_file.hpp>

#include "util.hpp"

#include <boost/test/unit_test.hpp>

#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace process::impl;

namespace
{
  int open_temp_file()
  {
    return
      open(
        temp_filename.c_str(),
        O_CREAT | O_WRONLY | O_TRUNC,
        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
      );
  }
}

BOOST_AUTO_TEST_CASE(test_destructor_closing_output_file)
{
  const int fd = open_temp_file();
  {
    output_file f(fd);
  }

  BOOST_CHECK(!file_descriptor_is_open(fd));
}

BOOST_AUTO_TEST_CASE(test_write_to_output_file)
{
  output_file f(open_temp_file());
  f.write("hello", 5);

  BOOST_CHECK_EQUAL("hello", read_file(temp_filename));
}

BOOST_AUTO_TEST_CASE(test_close_output_file)
{
  const int fd = open_temp_file();
  output_file f(fd);
  f.close();

  BOOST_CHECK(!file_descriptor_is_open(fd));
}





