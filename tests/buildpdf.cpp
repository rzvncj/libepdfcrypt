#include <epdf.hpp>
#include <fstream>
#include <getopt.h>
#include <iostream>
#include <mime_unpacker.hpp>
#include <stdexcept>

using namespace epdfcrypt;
using namespace std;

void print_help(const string& program_name)
{
    cout << "Usage: " << program_name << " options\n"
         << "  -h  --help            Display this usage information.\n"
         << "  -i  --input filename  Read input from file.\n"
         << "  -o  --output filename Write output to file.\n"
         << "  -p  --password        Encrypt output using given password.\n"
         << "  -b  --base64          Base64-encode the output.\n"
         << flush;
}

int main(int argc, char** argv)
{
    try {
        const char* const   short_options = "hi:o:p:ib";
        const struct option long_options[]
            = {{"help", 0, nullptr, 'h'},     {"output", 1, nullptr, 'o'}, {"input", 1, nullptr, 'i'},
               {"password", 1, nullptr, 'p'}, {"base64", 0, nullptr, 'p'}, {nullptr, 0, nullptr, 0}};

        string password, input_filename, output_filename;
        bool   base64 = false;
        int    next_option;

        do {
            next_option = getopt_long(argc, argv, short_options, long_options, nullptr);
            switch (next_option) {

            case 'o':
                output_filename = optarg;
                break;

            case 'i':
                input_filename = optarg;
                break;

            case 'p':
                password = optarg;
                break;

            case 'b':
                base64 = true;
                break;

            case -1: // no more arguments
                break;

            case 'h':
            case '?':
            default:
                print_help(argv[0]);
                return 0;
            }

        } while (next_option != -1);

        if (output_filename.empty() || input_filename.empty()) {
            print_help(argv[0]);
            return 0;
        }

        // Begin actual example

        file_mime_stream stream(input_filename);
        mime_unpacker    unpacker(stream, true);

        unpacker.unpack();
        string body_text = unpacker.body_text();

        epdf pdf("/usr/share/fonts/TTF/DroidSans.ttf");

        if (!password.empty())
            pdf.set_password(password);

        pdf.add_text(body_text);

        const parts_t& parts = unpacker.parts();

        for (size_t i = 0; i < parts.size(); ++i) {
            cout << "Using temporary part file: " << parts[i] << endl;
            pdf.attach(parts[i]);
        }

        cout << "PDF file size: " << pdf.size() << " bytes." << endl;

        pdf.write(output_filename, base64);

    } catch (const exception& e) {
        cerr << "ERROR: " << e.what() << "\n";
        return 1;

    } catch (...) {
        cerr << "ERROR\n";
        return 1;
    }

    return 0;
}
