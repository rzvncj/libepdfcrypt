#ifndef __INIT_HPP_INCLUDED__
#define __INIT_HPP_INCLUDED__

namespace epdfcrypt {

// RAII GMIME and haru system initializer
class sys_initializer {

public:
    // Init
    sys_initializer();

    // Cleanup
    ~sys_initializer();
};

}

#endif // __INIT_HPP_INCLUDED__
