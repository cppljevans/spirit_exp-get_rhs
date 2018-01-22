#pragma once

#ifndef GROUP_H_INCLUDED
#define GROUP_H_INCLUDED

#include <boost/spirit/home/x3.hpp>
#include "struct.h"

namespace group
{
	namespace x3 = boost::spirit::x3;

	struct foo_class{};

	typedef x3::rule<foo_class, s::foo> foo_type;

	BOOST_SPIRIT_DECLARE(foo_type);
}

group::foo_type const& foo();

#endif // GROUP_H_INCLUDED

