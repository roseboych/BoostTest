#include "simpleTest.h"
#include <stdio.h>

int main()
{
	boost_foreach_test();
	boost_date_time_test();

	boost::shared_ptr<int> ptr(new int(12));
	std::cout << ptr.use_count() << std::endl;
	boost::shared_ptr<int> ptr2(ptr);
	std::cout << ptr2.use_count() << std::endl;

	if (ptr.use_count()!=ptr2.use_count())
	{
		std::cout << "copy construct error" << std::endl;
	}

	return 0;
}
