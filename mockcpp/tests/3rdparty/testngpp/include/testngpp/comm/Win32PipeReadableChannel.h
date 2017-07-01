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

#ifndef __CPPTEST_WIN32_PIPE_READABLE_CHANNEL_H
#define __CPPTEST_WIN32_PIPE_READABLE_CHANNEL_H

#include <string>
#include <windows.h>

#include <testngpp/testngpp.h>

#include <testngpp/comm/ReadableChannel.h>

TESTNGPP_NS_START

struct Win32PipeReadableChannel: public ReadableChannel
{
   Win32PipeReadableChannel(HANDLE readableHandle, bool autoClose=true);
   ~Win32PipeReadableChannel();

   unsigned char readByte() TESTNGPP_THROW (Error, EOFError); 
   int readInt() TESTNGPP_THROW (Error, EOFError); 
   std::string readString() TESTNGPP_THROW (Error, EOFError); 

   void close();

   HANDLE getHandle() const;

private:

   HANDLE handle;
   bool hasBeenClosed;
   bool shouldClose;
};

TESTNGPP_NS_END

#endif

