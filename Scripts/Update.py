###
 #  @file Update.py
 #	@section About
 #
 #		This is a convenience script. It updates the build version in the indicated
 #		file. To use in Qt Creator, open your project and select "Projects" in the
 #		side pane. There, click "Add Build Step" and add "Update.py File.hpp" where
 #		"File.hpp" is the file you want to update. If there is a "BUILD" macro, it
 #		will be updated each time you compile your application.
 #
 #	@section License
 #
 #      Copyright (C) 2013 Daniel Hrabovcak
 #
 #      This file is a part of the Natural GM IDE. MIT License.
 #
 #      Permission is hereby granted, free of charge, to any person obtaining a copy
 #		of this software and associated documentation files (the "Software"), to deal
 #		in the Software without restriction, including without limitation the rights
 #		to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 #		copies of the Software, and to permit persons to whom the Software is
 #		furnished to do so, subject to the following conditions:
 #
 #		The above copyright notice and this permission notice shall be included in
 #		all copies or substantial portions of the Software.
 #
 #		THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 #		IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 #		FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 #		AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 #		LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 #		OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 #		THE SOFTWARE.
###
import os
import sys

if len(sys.argv) != 2:
	print 'Error: Wrong number of arguments.'
	print '  Usage:', os.path.basename(__file__), 'file.hpp'
	print '  > file.hpp Should point to the file you want to update.'
else:
	try:
		done = False
		file = open(sys.argv[1], 'r+')
		whole = ""
		for line in file:
			if done == False:
				position = line.find('BUILD')
				if position != -1:
					start = 0
					length = 0
					for i in range(position, len(line)):
						if line[i].isdigit():
							if start == 0:
								start = i
								whole += line[:i]
							++length
						elif length != 0:
							break;
					whole += str(int(line[start:i-1])+1) + line[i-1:]
					done = True
				else:
					whole += line
			else:
				whole += line
		file.seek(0)
		file.write(whole)
		file.close()
	except IOError:
		print 'Error: Could not open file.'
		print '  Check for mispellings and confirm existence.'
		print '  > File:', sys.argv[1]
