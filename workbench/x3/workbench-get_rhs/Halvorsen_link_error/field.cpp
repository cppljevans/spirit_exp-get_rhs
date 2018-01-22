#include "field_def.h"

namespace field
{
	namespace x3 = boost::spirit::x3;

	typedef std::string::const_iterator iterator_type;

	BOOST_SPIRIT_INSTANTIATE(a_type, iterator_type, x3::unused_type);
	BOOST_SPIRIT_INSTANTIATE(b_type, iterator_type, x3::unused_type);
}

