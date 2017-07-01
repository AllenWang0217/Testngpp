/***
   mockcpp is a C/C++ mock framework.
   Copyright [2008] [Darwin Yuan <darwin.yuan@gmail.com>]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
***/

#include <mockcpp/IgnoreReturnStub.h>
#include <mockcpp/Ignore.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////////
IgnoreReturnStub::IgnoreReturnStub()
   : hasBeenInvoked(false)
{
}
/////////////////////////////////////////////////////
bool
IgnoreReturnStub::isCompleted() const
{
    return hasBeenInvoked;
}
/////////////////////////////////////////////////////
Any&
IgnoreReturnStub::invoke()
{
    hasBeenInvoked = true;
    return getIgnore();
}

/////////////////////////////////////////////////////
std::string IgnoreReturnStub::toString(void) const
{
    return "ignoreReturnValue()";
}

/////////////////////////////////////////////////////
const std::type_info& IgnoreReturnStub::type() const
{
    return typeid(Ignore);
}

/////////////////////////////////////////////////////

MOCKCPP_NS_END

