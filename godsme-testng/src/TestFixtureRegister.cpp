
#include <testngpp/internal/TestFixtureRegister.h>
#include <testngpp/internal/TestSuiteDesc.h>

TESTNGPP_NS_START

extern "C" TestSuiteDesc* ___testngpp_test_suite_desc_getter();

TestFixtureRegister::TestFixtureRegister(TestFixtureDesc** fixtures, unsigned int num)
{
    ___testngpp_test_suite_desc_getter()->registerFixtures(fixtures, num);
}

TESTNGPP_NS_END

