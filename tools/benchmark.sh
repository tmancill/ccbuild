#!/bin/sh
#  This file is part of ccbuild.

#  ccbuild is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.

#  ccbuild is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.

#  You should have received a copy of the GNU General Public License
#  along with ccbuild.  If not, see <http://www.gnu.org/licenses/>.
#
#
# Write a file with the mean of 200 `time COMMAND` results.
#  Uses AWK to collect and mean the results

COMMAND=$@

echo "#BENCHMARK RESULTS FOR: " "$COMMAND" > benchmark.result.txt

for i in {1..200}; do
	(time -p $COMMAND ) 2>&1 |tail -n3 >> benchmark.result.txt
done

awk -- "/^real.*/{ rlt += \$2; rltn++;}/^user.*/{ ust += \$2; ustn++;}/^sys.*/{ syt += \$2; sytn++;} END{ print \"real\", rlt/rltn, \"[\" rltn \"]\";print \"user\", ust/ustn, \"[\" ustn \"]\"; print \"sys\", syt/sytn, \"[\" sytn \"]\";}" < benchmark.result.txt


