#pragma once

#ifndef GROUP_DEF_H_INCLUDED
#define GROUP_DEF_H_INCLUDED

#include "../trace_scope.hpp"
#include <boost/spirit/home/x3.hpp>
#include "struct.h"
#include "field.h"

namespace group
{
	namespace x3 = boost::spirit::x3;

	struct foo_class{};

	typedef x3::rule<foo_class, s::foo> foo_type;

	foo_type const foo = "foo";

	auto const foo_def = a() >> x3::lit(":") >> b();

	BOOST_SPIRIT_DEFINE(foo);
}

group::foo_type const& foo()
{
	return group::foo;
}

#endif // GROUP_DEF_H_INCLUDED

