#include <mime_unpacker.hpp>
#include <iostream>
#include <stdexcept>


using namespace epdfcrypt;
using namespace std;

int main()
{
    try {

        file_mime_stream stream("in.eml");
        mime_unpacker unpacker(stream);

        unpacker.unpack();

    } catch(const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;

    } catch(...) {
        cerr << "Error\n";
        return 1;
    }

    return 0;
}


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
