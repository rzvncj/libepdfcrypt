#ifndef __MIME_MESSAGE_HPP_INCLUDED__
#define __MIME_MESSAGE_HPP_INCLUDED__


#include <gmime/gmime.h>
#include <safe_epdf_object.hpp>
#include <string>


namespace epdfcrypt {


class mime_message : private safe_epdf_object {

public:
    mime_message();
    mime_message(GMimeMessage *message);
    ~mime_message();

public:
    GMimeMessage* message() const;
    std::string body_text() const;

private:
    mime_message(const mime_message&);
    mime_message& operator=(const mime_message&);

private:
    static bool part_is_textual(GMimeObject *mime_part);
    static std::string charset(GMimeObject *mime_part);

protected:
    GMimeMessage *message_;
};


}


#endif // __MIME_STREAMS_HPP_INCLUDED__


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
