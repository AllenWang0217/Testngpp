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

#include <testngppst/internal/Exception.h>

TESTNGPPST_NS_START

//////////////////////////////////////////////////////////
Exception::Exception(const std::string& file
   , unsigned int line, const std::string& msg)
   : fileName(file), lineNumber(line), errMsg(msg)
{}


//////////////////////////////////////////////////////////
const std::string& Exception::getFileName() const
{
   return fileName;
}

//////////////////////////////////////////////////////////
unsigned int Exception::getLineOfFile() const
{
   return lineNumber;
}

//////////////////////////////////////////////////////////
const char* Exception::what() const TESTNGPPST_THROW()
{
   return errMsg.c_str();
}

//////////////////////////////////////////////////////////

TESTNGPPST_NS_END


