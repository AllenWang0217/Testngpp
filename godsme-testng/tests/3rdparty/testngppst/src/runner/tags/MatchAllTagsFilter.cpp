
#include <testngppst/runner/MatchAllTagsFilter.h>

TESTNGPPST_NS_START

/////////////////////////////////////////////
bool
MatchAllTagsFilter::
matches(const Taggable* obj) const
{
   return true;
}

/////////////////////////////////////////////
std::string
MatchAllTagsFilter::
toString() const
{
   return "*";
}

TESTNGPPST_NS_END


