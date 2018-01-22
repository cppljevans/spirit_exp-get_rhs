#pragma once

#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED

#include <boost/spirit/home/x3.hpp>

namespace field
{
	namespace x3 = boost::spirit::x3;

	struct a_class{};
	struct b_class{};

	typedef x3::rule<a_class, char> a_type;
	typedef x3::rule<b_class, std::vector<char>> b_type;

	BOOST_SPIRIT_DECLARE(a_type, b_type);
}

field::a_type const& a();
field::b_type const& b();

#endif // FIELD_H_INCLUDED

