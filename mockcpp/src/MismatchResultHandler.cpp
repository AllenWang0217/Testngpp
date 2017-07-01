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

#include <mockcpp/types/Any.h>

#include <mockcpp/MismatchResultHandler.h>
#include <mockcpp/SelfDescribe.h>
#include <mockcpp/Asserter.h>

MOCKCPP_NS_START

////////////////////////////////////////////////////////////////
MismatchResultHandler::MismatchResultHandler(
                           bool castable
                         , const std::type_info& info
                         , const std::string& typeString
                         , const SelfDescribe* selfDescriber)
           : isCastable(castable)
			  , expectedTypeInfo(info)
			  , expectedTypeString(typeString)
			  , resultProvider(selfDescriber)
{
}

////////////////////////////////////////////////////////////////
bool MismatchResultHandler::matches(const Any& result) const
{
      return !isCastable;
}

////////////////////////////////////////////////////////////////
const Any& MismatchResultHandler::getResult(const Any& result) const
{
    oss_t oss;

    oss << "Returned type does NOT match the method declaration \n"
        << "Required : " << expectedTypeString << "\n"
        << "Returned : " << result.toTypeString() << ", which is from\n"
        << resultProvider->toString();

    MOCKCPP_ASSERT_FALSE_MESSAGE(oss.str(), matches(result));

    return getEmptyAny();
}

MOCKCPP_NS_END

