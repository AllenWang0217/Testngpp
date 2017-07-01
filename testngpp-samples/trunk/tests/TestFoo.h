
#include <testngpp/testngpp.hpp>
#include <mockcpp/mockcpp.hpp>

#include <CFoo.h>
#include <Interface.h>

USING_MOCKCPP_NS

FIXTURE(CFoo)
{
	CFoo* foo;
	MockObject<Interface> iface;

	SETUP()
	{
		foo = new CFoo(iface);
	}

	TEARDOWN()
	{
		delete foo;
	}

	TEST(should be able to add up 2 integers)
	{
		MOCK_METHOD(iface, add)
			.stubs()
			.with(eq(1), eq(3))
			.will(returnValue(4));

		ASSERT_EQ(4, foo->add(1, 3));
	}

	TEST(should be able to substract 2 integers)
	{
		MOCK_METHOD(iface, sub)
			.stubs()
			.with(eq(2), eq(3))
			.will(returnValue(-1));

		ASSERT_EQ(-1, foo->sub(2, 3));
	}
};