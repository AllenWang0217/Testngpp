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

#include <mockcpp/IsStringContains.h>
#include <mockcpp/OutputStringStream.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
bool
IsStringContains::predict(const std::string& input
               , const std::string& target) const
{
   const char* s = input.c_str();
   int len = input.size() - target.size() + 1;
   for(int i=0; i < len; i++)
   {
      if(!::strncmp(&s[i], target.c_str(), target.size()))
      {
         return true;
      }
   }

   return false;
}

///////////////////////////////////////////////////////////
std::string
IsStringContains::toString(const std::string& target) const
{
    oss_t oss;
    oss << "contains(\"" << target << "\")";
    return oss.str();
}

///////////////////////////////////////////////////////////

MOCKCPP_NS_END

