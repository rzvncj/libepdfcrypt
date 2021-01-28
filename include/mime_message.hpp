#ifndef __MIME_MESSAGE_HPP_INCLUDED__
#define __MIME_MESSAGE_HPP_INCLUDED__

#include <gmime/gmime.h>
#include <safe_epdf_object.hpp>
#include <string>

namespace epdfcrypt {

class mime_message : private safe_epdf_object {

public:
    mime_message();
    mime_message(GMimeMessage* message);
    ~mime_message();

    mime_message(const mime_message&) = delete;
    mime_message& operator=(const mime_message&) = delete;

public:
    GMimeMessage* message() const;
    std::string   body_text() const;

private:
    static bool        part_is_textual(GMimeObject* mime_part);
    static std::string charset(GMimeObject* mime_part);

protected:
    GMimeMessage* message_ {nullptr};
};

}

#endif // __MIME_STREAMS_HPP_INCLUDED__
