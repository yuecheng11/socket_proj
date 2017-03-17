 
#ifndef _MY_NONCOPYABLE_H_
#define _MY_NONCOPYABLE_H_


namespace wd
{

class Noncopyable
{
protected:
	Noncopyable(){}
private:
	Noncopyable(const Noncopyable & rhs);
	Noncopyable & operator=(const Noncopyable & rhs);
};

}// end of namespace wd


#endif 
