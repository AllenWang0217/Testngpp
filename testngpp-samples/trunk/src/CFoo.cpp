#include "CFoo.h"
#include <Interface.h>

int CFoo::add(int lhs, int rhs)
{
	return iface->add(lhs, rhs);
}

int CFoo::sub(int lhs, int rhs)
{
	return iface->sub(lhs, rhs);
}
