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

#ifndef __TESTNGPP_TEST_DEF_MACROS_H
#define __TESTNGPP_TEST_DEF_MACROS_H

#include <testngpp/testngpp.h>

#define __TESTNGPP_LINENAME_CAT( name, line ) name##line
#define __LINENAME( name, line ) __TESTNGPP_LINENAME_CAT( name, line )
#define __TESTNGPP_LINENAME( name ) __LINENAME( name, __LINE__ )

#define __TESTNGPP_FIXTURE_NAME(name) Test##name

#define TEST(name, ...)            void __TESTNGPP_LINENAME(test_) (void)
#define FIXTURE(cut, ...) struct __TESTNGPP_FIXTURE_NAME(cut) : public TESTNGPP_NS::TestFixture

#define CONS(name) __TESTNGPP_FIXTURE_NAME(name)()

#define SETUP() void setUp()
#define TEARDOWN() void tearDown()

#endif

