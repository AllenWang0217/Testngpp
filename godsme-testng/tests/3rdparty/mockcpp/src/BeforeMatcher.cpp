/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2009>  <Darwin Yuan: darwin.yuan@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***/

#include <mockcpp/BeforeMatcher.h>
#include <mockcpp/InvocationMocker.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/Invocation.h>
#include <mockcpp/InvocationId.h>
#include <mockcpp/ChainableMockMethodCore.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////
BeforeMatcher::BeforeMatcher()
	: previousCall(0)
{}

//////////////////////////////////////////////////////
bool BeforeMatcher::matches(const Invocation& inv) const
{
    return true;
}

//////////////////////////////////////////////////////
void BeforeMatcher::increaseInvoked(const Invocation& inv)
{
    oss_t oss;

    oss << "Expected invoked before the invocation with id \"" 
        << previousCall->getId()->getId()
        << "\", but that invocation has been invoked.";

    MOCKCPP_ASSERT_TRUE_MESSAGE(
         oss.str(),
         !previousCall->hasBeenInvoked());
}

//////////////////////////////////////////////////////
std::string BeforeMatcher::toString() const
{
    return "before";
}

//////////////////////////////////////////////////////
void BeforeMatcher::verify() 
{
}

//////////////////////////////////////////////////////
bool BeforeMatcher::isCompleted(void) const
{
    return previousCall != 0;
}

//////////////////////////////////////////////////////
void BeforeMatcher::setOrderingInvocationMocker(InvocationMocker* mocker)
{
    previousCall = mocker;
}

MOCKCPP_NS_END

