#ifndef __CFOO_H__
#define __CFOO_H__

struct Interface;

struct CFoo
{
	CFoo(Interface* iiface) : iface(iiface) {}

	int add(int lhs, int rhs);
	int sub(int lhs, int rhs);
private:
	Interface* iface;
};

#endif