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
#include "source.ih"
void Source::build(Compiler & cc) {
    d_apiLock.set(); //Protect d_filename

    if(!FileSystem::isReadable(d_filename)) {
        cerrLock.set();
        cerr << "ccbuild: Warning: Trying to build a non-readable file: '" << d_filename << "'" << endl;
        cerrLock.unset();
    }
    d_apiLock.unset();

    if(isHeader()) {
        buildHeader(cc);
    } else if(isObjectTarget()) {
        buildObjectTarget(cc);
    } else {
        d_apiLock.set(); //Protect d_filename
        cerr << "ccbuild: Error: Unknown file type: " << d_filename << "\n";
        d_apiLock.unset();
    }
}
