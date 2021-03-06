    namespace detail_rule
    {
        template <typename ID>
        struct always_false
        {
            static constexpr bool value=false;
        };
    }//detail_rule namespace
    
    /*! \brief Default get_rhs implementation.
     *  get_rhs' specialized for a particular
     *  ID are generated by using the 
     *  BOOST_SPIRIT_DEFINE macro, which is
     *  defined below.
     */
      template 
      < typename ID
      >
      auto const&
    get_rhs
      ( ID
      )
      {
        static_assert
          ( detail_rule::always_false<ID>::value
            //Using just false in the above causes assert to
            //always fire.  Using the above template
            //metafunction call avoids that.
          , "Undefined rule.  Use BOOST_SPIRIT_DEFINE to define rule."
          );
        using rhs_t=detail_rule::rule_undefined;
        static rhs_t rhs_v;
        return rhs_v;
      }
/*!
  \def BOOST_SPIRIT_DEFINE_(r, data, rule_def)
    \a r is ignored.
    \a data is ignored.
    \a rule_def is the variable name of a variable
       with type, rule_definition<ID>.
    This macro generates an instance of get_rhs(ID)
    specialized on decltype(rule_def)::rule_id(==ID) as 1st arg.  
    The body just returns this variable.  Of course this
    means rule_def must be defined before this macro is executed.
    For example, if x is the rule variable named x, then a
    declaration statement something like:
      auto const& x_def = x = rhs;
    must occur in the scope in which this macro is invoked.
    Then, this macro is called as:
      BOOST_SPIRIT_DEFINE_(_,_,x_def)
*/
#define BOOST_SPIRIT_DEFINE_(r, data, rule_def) \
      auto const&                                \
    get_rhs                                      \
      ( typename decltype(rule_def)::rule_id     \
      )                                          \
    {                                            \
        return rule_def;                         \
    }                                            \
  
#define BOOST_SPIRIT_DEFINE(...) BOOST_PP_SEQ_FOR_EACH(                        \
    BOOST_SPIRIT_DEFINE_, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))            \
    /***/
    
    struct empty_context{};
    
