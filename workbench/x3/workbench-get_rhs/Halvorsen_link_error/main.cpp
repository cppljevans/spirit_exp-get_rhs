#include "../trace_scope.hpp"
#include "group.h"

int main(int argc, char* argv[])
{
#ifdef USE_TYPE_NAME
    boost::iostreams::indent_scoped_ostreambuf<char>
  indent_outbuf(std::cout,2);
#endif
  std::string s("1:ABC");
  s::foo f;
  auto ok = parse(s.cbegin(), s.cend(), foo(), f);
#ifdef USE_TYPE_NAME
  std::cout<<"ok="<<ok<<"\n";
#endif
  return EXIT_SUCCESS;
}
