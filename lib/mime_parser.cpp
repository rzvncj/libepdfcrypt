#include <mime_parser.hpp>
#include <mime_streams.hpp>
#include <stdexcept>

namespace epdfcrypt {

mime_parser::mime_parser(const mime_stream& input) : parser_(NULL)
{
    input.seek(0, mime_stream::SET);
    parser_ = g_mime_parser_new_with_stream(input.stream());
}

mime_parser::~mime_parser()
{
    g_object_unref(parser_);
}

GMimeMessage* mime_parser::parse() const
{
    GMimeMessage* message = g_mime_parser_construct_message(parser_);

    if (!GMIME_IS_MESSAGE(message))
        throw std::runtime_error("parse error: invalid email stream");

    return message;
}

} // namespace epdfcrypt
