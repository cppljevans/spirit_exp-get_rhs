//Purpose:
//  Show that the rule_definition::parse_no_xform is needed.
//=================================  
//#define BOOST_SPIRIT_X3_DEBUG
#include "trace_flags.hpp"
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/traits/attribute_of.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#ifndef TRACE_PARSES
  #define TRACE_PARSES 1
#endif
#if TRACE_PARSES
  #include <boost/spirit/home/x3/support/traits/print_attribute.hpp>
#endif

#include <iostream>
#include "start.hpp"

int main() {
#ifdef USE_TRACE_SCOPE
      boost::iostreams::indent_scoped_ostreambuf<char>
  indent_outbuf(std::cout,2);
#endif

     std::string strs[]=
     { "label0!"
     //, "label1"
     };
     bool all_ok=true;
     for(std::string str : strs)
     {
         namespace x3=client::x3;

         client::start_t start;         
         client::start_attr_t start_attr_v;
         auto iter = str.begin();
         auto end = str.end();
         bool r = 
           parse
           ( iter
           , end
           , start
           , start_attr_v
           );
         all_ok=all_ok && r;
       #if TRACE_PARSES
         if (r)
         {
             std::cout << str << std::endl << std::endl << " Parses OK: " << std::endl;
             x3::traits::print_attribute(std::cout,start_attr_v);
             std::cout << "\n-------------------------\n";
         }
         else
         {
             std::cout << "Parsing failed\n";
             std::cout << "-------------------------\n";
         }

         if (iter != end) std::cout << "Partial match" << std::endl;
       #endif
     }
   #if TRACE_PARSES
     std::cout<<"all_ok="<<all_ok<<"\n";
   #endif
     return !all_ok;
}
