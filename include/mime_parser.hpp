#ifndef __MIME_PARSER_HPP_INCLUDED__
#define __MIME_PARSER_HPP_INCLUDED__


#include <gmime/gmime.h>
#include <safe_epdf_object.hpp>


namespace epdfcrypt {


// Forward declaration
class mime_stream;


class mime_parser : private safe_epdf_object {

public:
    mime_parser(const mime_stream& stream);
    ~mime_parser();

public:
    GMimeMessage* parse() const;

private:
    mime_parser(const mime_parser&);
    mime_parser& operator=(const mime_parser&);

protected:
    GMimeParser *parser_;
};


}


#endif // __MIME_PARSER_HPP_INCLUDED__


/*
  Local Variables:
  mode: c++
  c-basic-offset: 4
  tab-width: 4
  c-indent-comments-syntactically-p: t
  c-tab-always-indent: t
  indent-tabs-mode: nil
  End:
*/

// vim:shiftwidth=4:autoindent:tabstop=4:expandtab:softtabstop=4
