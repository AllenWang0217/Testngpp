
#include <testngpp/testngpp.hpp>
#include <mockcpp/mokc.h>

#include <CBar.h>

USING_MOCKCPP_NS

FIXTURE(CBar)
{
	TEST(should be able to multiply 2 integers)
	{
		ASSERT_EQ(6, CBar::multiply(2, 3));
	}

	TEST(should be able to div 2 integers)
	{
		INFO("the result should be double type");
		ASSERT_EQ(3, CBar::divide(6, 2));
	}

	TEST(if devident is 0 => throw exception)
	{
		WARN("not implemented yet");
	}

	TEST(test devide by 0 with mock)
	{
		Except ex;
		MOCKER(CBar::divide).stubs().with(any(), eq(0)).will(throws(ex));
		
		__DO__

		ASSERT_THROWS(CBar::divide(1,0), Except);

		__CLEANUP__

		GlobalMockObject::reset();

		__DONE__
	}
};