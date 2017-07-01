#ifndef __TEST_FIXTURE_REGISTER_H__
#define __TEST_FIXTURE_REGISTER_H__

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TestFixtureDesc;

struct TestFixtureRegister
{
   TestFixtureRegister(TestFixtureDesc**, unsigned int num);
};

TESTNGPP_NS_END

#endif

