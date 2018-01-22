#pragma once

#ifndef FIELD_DEF_H_INCLUDED
#define FIELD_DEF_H_INCLUDED
#include "../trace_scope.hpp"
#include <boost/spirit/home/x3.hpp>

namespace field
{
	namespace x3 = boost::spirit::x3;

	struct a_class{};
	struct b_class{};

	typedef x3::rule<a_class, char> a_type;
	typedef x3::rule<b_class, std::vector<char>> b_type;

	a_type const a = "a";
	b_type const b = "b";

	auto const a_def = x3::char_;
	auto const b_def = +x3::char_;

	BOOST_SPIRIT_DEFINE(a, b);
}

field::a_type const& a()
{
	return field::a;
}

field::b_type const& b()
{
	return field::b;
}

#endif // FIELD_DEF_H_INCLUDED

