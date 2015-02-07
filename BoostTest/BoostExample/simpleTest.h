#ifndef SIMPLE_TEST_H
#define SIMPLE_TEST_H
#include <string>
#include <vector>
#include <iostream>
#include <boost/foreach.hpp>
#include <boost/assign.hpp>
#include <boost/timer.hpp>
#include <boost/shared_ptr.hpp>


void boost_foreach_test()
{
	
	std::vector<int> v = (boost::assign::list_of(1),2,3,4,5);
	BOOST_FOREACH(int x,v)
	{
		std::cout << x << ",";
	}
	std::cout << std::endl;

	std::string str("boost foreach test");
	BOOST_FOREACH(char& c,str)
	{
		std::cout << c << "-" ;
	}

	std::cout << std::endl;
	
}

void boost_date_time_test()
{

	boost::timer t;
	std::cout << t.elapsed() << "s" << std::endl;

}


void Test_Boost_Lib_Ready()
{
	boost_foreach_test();
	boost_date_time_test();

}

#endif
