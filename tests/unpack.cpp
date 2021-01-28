#include <iostream>
#include <mime_unpacker.hpp>
#include <stdexcept>

using namespace epdfcrypt;
using namespace std;

int main()
{
    try {
        file_mime_stream stream("in.eml");
        mime_unpacker    unpacker(stream);

        unpacker.unpack();

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;

    } catch (...) {
        cerr << "Error\n";
        return 1;
    }

    return 0;
}
