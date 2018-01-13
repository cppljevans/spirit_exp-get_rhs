/*=============================================================================
    Copyright (c) 2018      Larry Evans

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_SPIRIT_TEST_X3_BOOST_SPIRIT_INSTANTIATE_LINK_ERROR_START
#define BOOST_SPIRIT_TEST_X3_BOOST_SPIRIT_INSTANTIATE_LINK_ERROR_START
#include "../trace_flags.hpp"
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/traits/attribute_of.hpp>

namespace client{
namespace x3 = boost::spirit::x3;
#define LINK_ERROR
#ifndef LINK_ERROR
#define START_RHS_V \
  +x3::alnum
#else
//Emulate the a_def grammar expression in
//../Halvorsen_link_error/field_def.h.
//The reason Halvorsen_link_error fails to
//link is because the attribute in field.cpp
//is wrong.  It should be char instead of unsued_type.
//

#define START_RHS_V x3::char_
#endif//LINK_ERROR  
using start_rhs_t = decltype(START_RHS_V);
using context_t=x3::unused_type;
using start_attr_t = x3::traits::attribute_of<start_rhs_t, context_t>::type;
struct start_id{};
using start_t = x3::rule<start_id, start_attr_t>;
BOOST_SPIRIT_DECLARE(start_t)
}//end namespace
#endif
