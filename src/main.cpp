#include "../headers/bmp.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << argv[0] << " <file to read>\n";
        return 1;
    }

    FILE *fBmpRead = fopen(argv[1], "r");
//    FILE *fBmpWrite = fopen(argv[2], "wb");
    bmp pic;

    pic.readBmp(fBmpRead);
 //   pic.writeBmp(fBmpWrite);
    fclose(fBmpRead);
    return 0;
}
