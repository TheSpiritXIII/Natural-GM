###
 #  @file CleanQt.py
 #	@section About
 #
 #		This is a convenience script. Often times, Qt Creator will fail or return
 #		strange results because it does not rewrite its Makefiles. Calling this
 #		effectively removes all Qt generated Makefiles.
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

dir = ""
if len(sys.argv) == 2:
	dir = sys.argv[2]
else:
	dir = os.getcwd()+'/'
os.remove(dir+'Makefile')
os.remove(dir+'Makefile.Debug')
os.remove(dir+'Makefile.Release')