/*
  This file is part of ccbuild.

  ccbuild is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  ccbuild is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with ccbuild.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Compiler.ih"

string Compiler::libCommand(std::string pwd,
			std::string target) const
{

  ostringstream command(d_baseCommand, ios::ate);
  command << " -shared -Wl,-soname,\"" << target << "\" " << Options::extraArgs << " ";


  __foreach(obj, d_objects)
    command << " \"" << (*obj) << "\" ";

  copy(d_link.begin(), d_link.end(), ostream_iterator<string>(command, " "));

  command << "-o \"" << target << "\" ";
  

  command << Options::commandAppend;

	return command.str();
}

