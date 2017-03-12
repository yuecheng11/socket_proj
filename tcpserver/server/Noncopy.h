#ifndef _MY_NONCOPY_H_
#define _MY_NONCOPY_H_
class Noncopy
{
public:
	Noncopy(){}
private:
	Noncopy(const Noncopy& rhs);
	Noncopy& operator=(const Noncopy& rhs);
};


#endif