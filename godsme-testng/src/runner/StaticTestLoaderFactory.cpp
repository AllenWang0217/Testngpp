
#include <testngpp/runner/StaticLoader.h>

TESTNGPP_NS_START

struct StringList;

TestLoader* createTestLoader(const StringList&)
{
   static StaticLoader loader;
   return &loader;
}

TESTNGPP_NS_END

