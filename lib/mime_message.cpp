#include <mime_message.hpp>
#include <mime_streams.hpp>

namespace epdfcrypt {

mime_message::mime_message() : message_(NULL)
{
    message_ = g_mime_message_new(TRUE);
}

mime_message::mime_message(GMimeMessage* message) : message_(message)
{
}

mime_message::~mime_message()
{
    g_object_unref(message_);
}

GMimeMessage* mime_message::message() const
{
    return message_;
}

std::string mime_message::body_text() const
{
    std::string ret;

    GMimeObject* part = g_mime_message_get_body(message_);

    if (GMIME_IS_MULTIPART(part)) {
        GMimeMultipart* multipart = reinterpret_cast<GMimeMultipart*>(part);

        part      = NULL;
        int count = g_mime_multipart_get_count(multipart);

        for (int i = 0; i < count; ++i) {
            part = g_mime_multipart_get_part(multipart, i);

            if (part_is_textual(part))
                break;
        }
    }

    if (part_is_textual(part)) {
        memory_mime_stream output;
        GMimePart*         mime_part = reinterpret_cast<GMimePart*>(part);

        GMimeDataWrapper* content = g_mime_part_get_content_object(mime_part);
        g_mime_data_wrapper_write_to_stream(content, output.stream());
        g_mime_stream_flush(output.stream());

        ret = output.content();
    }

    return ret;
}

bool mime_message::part_is_textual(GMimeObject* mime_part)
{
    GMimeContentType* type = g_mime_object_get_content_type(mime_part);

    return g_mime_content_type_is_type(type, "text", "plain");
}

std::string mime_message::charset(GMimeObject* mime_part)
{
    const char* charset = g_mime_object_get_content_type_parameter(mime_part, "charset");

    if (charset)
        return charset;

    return "";
}

} // namespace epdfcrypt
