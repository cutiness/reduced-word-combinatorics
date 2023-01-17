# The GPLv3 License (GPLv3)

# Copyright (c) 2023 cutiness

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

all: notifier rword

notifier:
		@echo "You are compiling on: $(shell uname -s)"

rword: functions.o tower-diagram.o
		g++ functions.o tower-diagram.o reduced-word.cpp -o reduced-word

functions.o:
		g++ -c functions.cpp

tower-diagram.o:
		g++ -c tower-diagram.cpp

clean:
		rm -f *.o reduced-word	
