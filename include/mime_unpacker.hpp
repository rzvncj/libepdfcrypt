#ifndef __MIME_UNPACKER_HPP_INCLUDED__
#define __MIME_UNPACKER_HPP_INCLUDED__

#include <mime_parser.hpp>
#include <mime_streams.hpp>
#include <safe_epdf_object.hpp>
#include <string>
#include <vector>

namespace epdfcrypt {

typedef std::vector<std::string> parts_t;

class mime_unpacker : private safe_epdf_object {

public:
    mime_unpacker(const mime_stream& stream, bool keep_parts = false);
    ~mime_unpacker();

    mime_unpacker(const mime_unpacker&) = delete;
    mime_unpacker& operator=(const mime_unpacker&) = delete;

public:
    void               unpack();
    const parts_t&     parts() const;
    const std::string& body_text() const;

private:
    static void extract_foreach_callback(GMimeObject* parent, GMimeObject* part, gpointer user_data);

private:
    bool        keep_parts_;
    mime_parser parser_;
    parts_t     parts_;
    unsigned    part_index_;
    std::string tmp_dir_;
    std::string body_text_;
};

}

#endif // __MIME_UNPACKER_HPP_INCLUDED__
