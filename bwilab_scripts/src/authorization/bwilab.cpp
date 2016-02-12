/*********************************************************************
* Software License Agreement (BSD License)
*
*  Copyright (C) 2016, Jack O'Quin
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the author nor other contributors may be
*     used to endorse or promote products derived from this software
*     without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/


/** @file

@brief Run scripts under a different user ID.

This is a POSIX program for authorizing a constrained set of scripts
to run under the @c bwilab user account.

*/

#include <ostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <boost/filesystem.hpp>

// Path to directory containing allowed scripts.
const std::string CMD_DIR("/usr/local/lib/bwilab_scripts");

int main(int argc, char *argv[])
{
  std::string exec_path = argv[0];

  if (argc < 2)
    {
      std::cerr << "usage: " << exec_path
                << " command [ args ]" << std::endl;
      return 9;
    }

  using boost::filesystem::is_directory;
  using boost::filesystem::path;

  path cmd_path(CMD_DIR);
  if (!is_directory(cmd_path))
    {
      std::cerr << "error: " << CMD_DIR
                << " directory does not exist" << std::endl;
      return 2;
    }

  std::string cmd = argv[1];
  std::cout << "Command to run: " << cmd << std::endl;
  std::string resolved_cmd_path = CMD_DIR + '/' + cmd;
  std::cout << "Command path: " << cmd << std::endl;

  // execute the desired program with the current environment
  int rc = execv(resolved_cmd_path.c_str(), argv+1);
  // execv should NOT return

  std::string error_str = "error: " + resolved_cmd_path + " exec failed";
  perror(error_str.c_str());
  return 1;
}
