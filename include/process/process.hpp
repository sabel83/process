#ifndef PROCESS_PROCESS_HPP
#define PROCESS_PROCESS_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <process/output.hpp>
#include <process/impl/pipe.hpp>

#include <boost/bind.hpp>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <cstdlib>

namespace process
{
  template <class Seq>
  output run(const Seq& cmd_, const std::string& input_)
  {
    using std::vector;
    using std::transform;
    using boost::bind;
    using std::string;

    assert(!cmd_.empty());

    vector<const char*> cmd(cmd_.size() + 1, 0);
    transform(cmd_.begin(), cmd_.end(), cmd.begin(), bind(&string::c_str, _1));

    impl::pipe standard_input;
    impl::pipe standard_output;
    impl::pipe standard_error;

    const pid_t pid = fork();
    switch (pid)
    {
    case -1:
      return output("", "");
    case 0: // in child
      standard_input.output.close();
      standard_output.input.close();
      standard_error.input.close();

      standard_input.input.use_as(STDIN_FILENO);
      standard_output.output.use_as(STDOUT_FILENO);
      standard_error.output.use_as(STDERR_FILENO);

      execv(cmd[0], const_cast<char*const*>(&cmd[0]));
      quick_exit(0);
    default: // in parent
      standard_input.input.close();
      standard_input.output.write(input_);
      standard_input.output.close();

      standard_output.output.close();
      standard_error.output.close();

      int status;
      waitpid(pid, &status, 0);

      return
        output(standard_output.input.read(), standard_error.input.read());
    }
  }
}

#endif

