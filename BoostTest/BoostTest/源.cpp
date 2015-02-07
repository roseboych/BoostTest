/*
** This is a test for Boost,whether it is configured and the data_time lib is complied
*/

#include <vector>
#include <iostream>
#include <boost/foreach.hpp>
#include <boost/assign.hpp>
#include <boost/timer.hpp> //for test the data_time lib is complied right
int main()
{
	std::vector<int> v = (boost::assign::list_of(1), 2, 3, 4, 5);
	BOOST_FOREACH(int x, v)
	{
		std::cout << x << ",";
	}
	std::cout << std::endl;
	boost::timer  t;
	std::cout << t.elapsed() <<"s"<< std::endl;
	return 0;
}
