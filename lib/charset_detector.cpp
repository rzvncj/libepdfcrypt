#include "charset_detector.hpp"
#include <stdexcept>

namespace epdfcrypt {

charset_detector::charset_detector() : detector_(0)
{
    UErrorCode status = U_ZERO_ERROR;
    detector_         = ucsdet_open(&status);

    if (!detector_ || U_FAILURE(status))
        throw std::runtime_error("could not create charset detector");
}

charset_detector::~charset_detector()
{
    ucsdet_close(detector_);
}

std::string charset_detector::charset(const std::string& text)
{
    UErrorCode status = U_ZERO_ERROR;

    ucsdet_setText(detector_, text.c_str(), static_cast<int32_t>(text.length()), &status);

    if (U_FAILURE(status))
        return std::string();

    const UCharsetMatch* match = ucsdet_detect(detector_, &status);

    if (U_FAILURE(status) || !match)
        return std::string();

    const char* detected_charset = ucsdet_getName(match, &status);

    if (!detected_charset)
        return std::string();

    return detected_charset;
}

} // namespace epdfcrypt
