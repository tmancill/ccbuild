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
#include "compiler.ih"

void Compiler::splitInto(std::string argument, std::vector<std::string> &arguments) const {
    vector<string> tArguments;  //Uncollapsed version
    istringstream argumentStream(argument);

    copy(istream_iterator<string>(argumentStream),
         istream_iterator<string>(),
         back_inserter(tArguments)
        );

#if DEBUGLEVEL > 3
    {
        _debugLevel4("--- Before collapse");
        unsigned i = 0;
        _foreach(arg, tArguments)
        _debugLevel4( (i++) << " " << *arg);
        _debugLevel4("---");
    }
#endif

    //vector<string> arguments; //Collapsed (quoted strings collapsed)
    //Collapse the arguments with \" or \'
    for(unsigned i = 0; i < tArguments.size(); ++i) {
        unsigned start = i;
        if(tArguments[i][0] == '"' || tArguments[i][0] == '\'' || tArguments[i][0] == '`') {
            char stopChar = tArguments[i][0];
            while(i < tArguments.size()) {
                //TODO Be more efficient
                //Ending in stop argument
                string const st = "  " + tArguments[i];
                if(st[st.size() - 1] == stopChar
                        && st[st.size() - 2] != '\'') {
                    break;
                }
                ++i;
            }
        }



        //Collapse start -> i into an argument.
        string arg = tArguments[start];
        for(unsigned p = start + 1; p <= i; ++p) {
            arg += " " + tArguments[p];
        }

        //Strip "" and '' if they both exist
        if(arg.find_first_of("\"'") == 0
                && arg.find_last_of("\"'") == arg.size() -1) {
            //They must exist
            arg = arg.substr(1, arg.size() -2);
        }

        arguments.push_back(arg);
    }

#if DEBUGLEVEL > 3
    {
        _debugLevel4("--- After collapse");
        unsigned i = 0;
        _foreach(arg, arguments)
        _debugLevel4( (i++) << " " << *arg);
        _debugLevel4("---");
    }
#endif

}
