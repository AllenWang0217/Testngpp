/**
    TestNG++ is a practical, easy-to-use C/C++ xUnit framework.
    Copyright (C) <2009>  <Arthur Yuan: arthur.ii.yuan@gmail.com>

    TestNG++ is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TestNG++ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with TestNG++.  If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef __CPPTEST_WIN32_PIPE_WRITTABLE_CHANNEL_H
#define __CPPTEST_WIN32_PIPE_WRITTABLE_CHANNEL_H

#include <windows.h>
#include <string>

#include <testngppst/testngppst.h>

#include <testngppst/comm/WrittableChannel.h>

TESTNGPPST_NS_START

struct Win32PipeWrittableChannel
   : public WrittableChannel
{
   Win32PipeWrittableChannel(HANDLE channelFd);
   ~Win32PipeWrittableChannel();

   void writeByte(const unsigned char byte) TESTNGPPST_THROW (Error);
   void writeInt(const unsigned int value) TESTNGPPST_THROW (Error);
   void writeString(const std::string& str) TESTNGPPST_THROW (Error);

   void close();

private:
   HANDLE handle;
};

TESTNGPPST_NS_END

#endif

