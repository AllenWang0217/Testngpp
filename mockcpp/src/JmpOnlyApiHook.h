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

#ifndef __MOCKCPP_JMP_ONLY_API_HOOK_H__
#define __MOCKCPP_JMP_ONLY_API_HOOK_H__

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

struct JmpOnlyApiHookImpl;

struct JmpOnlyApiHook
{
    JmpOnlyApiHook
       ( const void* api
       , const void* stub );

    ~JmpOnlyApiHook();

private:
    JmpOnlyApiHookImpl* This;;
};

MOCKCPP_NS_END

#endif
