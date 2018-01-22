#include "group_def.h"

namespace group
{
	namespace x3 = boost::spirit::x3;
	typedef std::string::const_iterator iterator_type;

	BOOST_SPIRIT_INSTANTIATE(foo_type, iterator_type, x3::unused_type);
}


