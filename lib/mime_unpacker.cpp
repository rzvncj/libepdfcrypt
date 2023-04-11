#include <cstdio>
#include <cstdlib>
#include <mime_message.hpp>
#include <mime_unpacker.hpp>
#include <sstream>
#include <stdexcept>

namespace epdfcrypt {

mime_unpacker::mime_unpacker(const mime_stream& stream, bool keep_parts)
    : keep_parts_(keep_parts), parser_(stream), part_index_(0)
{
    char temporary_dirname[] = "/tmp/epdfcryptXXXXXX";

    if (!mkdtemp(temporary_dirname))
        throw std::runtime_error(std::string("failed to open ") + temporary_dirname + ": " + g_strerror(errno));

    tmp_dir_ = temporary_dirname;
}

mime_unpacker::~mime_unpacker()
{
    if (!keep_parts_) {
        for (auto&& part : parts_)
            remove(part.c_str());

        if (!tmp_dir_.empty())
            remove(tmp_dir_.c_str());
    }
}

void mime_unpacker::unpack()
{
    if (!parts_.empty())
        return;

    mime_message message(parser_.parse());
    g_mime_message_foreach(message.message(), extract_foreach_callback, this);

    body_text_ = message.body_text();
}

const parts_t& mime_unpacker::parts() const
{
    return parts_;
}

const std::string& mime_unpacker::body_text() const
{
    return body_text_;
}

void mime_unpacker::extract_foreach_callback(GMimeObject*, GMimeObject* part, gpointer user_data)
{
    // 'part' points to the current part node that g_mime_message_foreach() is iterating over.

    // Find out what class 'part' is...
    if (GMIME_IS_MESSAGE_PART(part)) {
        // message/rfc822 or message/news.

        // g_mime_message_foreach() won't descend into child message parts, so if we want to count
        // any subparts of this child message, we'll have to call g_mime_message_foreach() again here.

        GMimeMessage* message = g_mime_message_part_get_message(reinterpret_cast<GMimeMessagePart*>(part));

        g_mime_message_foreach(message, extract_foreach_callback, user_data);

    } else if (GMIME_IS_MESSAGE_PARTIAL(part)) {
        // message/partial.

        // This is an incomplete message part, probably a large message that the sender has broken into
        // smaller parts sent to us bit by bit. We could save some info about it so that we could
        // piece this back together again once we get all the parts?

    } else if (GMIME_IS_MULTIPART(part)) {
        // multipart/mixed, multipart/alternative, multipart/related, multipart/signed, multipart/encrypted, etc.

    } else if (GMIME_IS_PART(part)) {
        // A standard leaf part, could be text/plain, image/jpeg, etc.

        GMimePart*     mime_part = reinterpret_cast<GMimePart*>(part);
        mime_unpacker* unpacker  = reinterpret_cast<mime_unpacker*>(user_data);

        const char* filename = g_mime_part_get_filename(mime_part);

        std::string path {unpacker->tmp_dir_ + "/"};

        if (!filename)
            path += "part" + std::to_string(unpacker->part_index_++) + ".bin";
        else
            path += filename;

        file_mime_stream output(path);

        GMimeDataWrapper* content = g_mime_part_get_content(mime_part);
        g_mime_data_wrapper_write_to_stream(content, output.stream());
        g_mime_stream_flush(output.stream());

        unpacker->parts_.push_back(path);

    } else {
        g_assert_not_reached();
    }
}

} // namespace epdfcrypt
