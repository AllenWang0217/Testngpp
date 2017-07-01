
#include <testngpp/runner/DynamicLoader.h>
#include <testngpp/utils/StringList.h>

TESTNGPP_NS_START

TestLoader* createTestLoader(const StringList& suites)
{
   static DynamicLoader loader(suites);

   return &loader;
}

TESTNGPP_NS_END

