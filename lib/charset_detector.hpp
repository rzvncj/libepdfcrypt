#ifndef __CHARSET_DETECTOR_HPP_INCLUDED__
#define __CHARSET_DETECTOR_HPP_INCLUDED__

#include <string>
#include <unicode/ucsdet.h>

namespace epdfcrypt {

class charset_detector {

public:
    charset_detector();
    ~charset_detector();

public:
    std::string charset(const std::string& text);

private:
    charset_detector(const charset_detector&);
    charset_detector& operator=(const charset_detector&);

private:
    UCharsetDetector* detector_;
};

}

#endif // __CHARSET_DETECTOR_HPP_INCLUDED__
