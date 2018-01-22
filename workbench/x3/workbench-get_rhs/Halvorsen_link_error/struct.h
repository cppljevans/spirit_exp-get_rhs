#pragma once

#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

#include <boost/fusion/include/adapt_struct.hpp>
#include <vector>

namespace s
{
	
struct foo
{
	char a; 
	std::vector<char> b;
};

}

BOOST_FUSION_ADAPT_STRUCT(
	s::foo,
	(char, a)
	(std::vector<char>, b)
)


#endif // STRUCT_H_INCLUDED
