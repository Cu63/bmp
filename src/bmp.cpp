#include "../headers/bmp.hpp"

bmp::bmp() {
}

void bmp::readBmp(FILE *fp) {
    readBmpHeader(fp);
    printBmpHeader();
    readMatrixRGB(fp);
}

void bmp::writeBmp(FILE *fp) {
    writeBmpHeader(fp);
    writeMatrixRGB(fp);
}

void bmp::readBmpHeader(FILE *fp) {
    fread(&(bmpHeader.bfType), 1, sizeof(bmpHeader.bfType), fp);
    fread(&(bmpHeader.bfSize), 1, sizeof(bmpHeader.bfSize), fp);
    fread(&(bmpHeader.bfReserved), 1, sizeof(bmpHeader.bfReserved), fp);
    fread(&(bmpHeader.bfOffBits), 1, sizeof(bmpHeader.bfOffBits), fp);
    fread(&(bmpHeader.biSize), 1, sizeof(bmpHeader.biSize), fp);
    fread(&(bmpHeader.biWidth), 1, sizeof(bmpHeader.biWidth), fp);
    fread(&(bmpHeader.biHeight), 1, sizeof(bmpHeader.biHeight), fp);
    fread(&(bmpHeader.biPlanes), 1, sizeof(bmpHeader.biPlanes), fp);
    fread(&(bmpHeader.biBitCount), 1, sizeof(bmpHeader.biBitCount), fp);
    fread(&(bmpHeader.biCompression), 1, sizeof(bmpHeader.biCompression), fp);
    fread(&(bmpHeader.biSizeImage), 1, sizeof(bmpHeader.biSizeImage), fp);
    fread(&(bmpHeader.biXPelsPerMeter), 1, sizeof(bmpHeader.biXPelsPerMeter), fp);
    fread(&(bmpHeader.biYPelsPerMeter), 1, sizeof(bmpHeader.biYPelsPerMeter), fp);
    fread(&(bmpHeader.biClrUsed), 1, sizeof(bmpHeader.biClrUsed), fp);
    fread(&(bmpHeader.biClrImportant), 1, sizeof(bmpHeader.biClrImportant), fp);
}

void bmp::printBmpHeader() {
    using std::cout;
    using std::endl;
    using std::hex;
    cout << hex << "bfType: " << bmpHeader.bfType << endl;
    cout << hex << "bfSize: " << bmpHeader.bfSize << endl;
    cout << hex << "bfReserved: " << bmpHeader.bfReserved << endl;
    cout << hex << "bfOffBits: " << bmpHeader.bfOffBits << endl;
    cout << hex << "biSize: " << bmpHeader.biSize << endl;
    cout << std::dec << "biWidth: " << bmpHeader.biWidth << endl;
    cout << std::dec << "biHeight: " << bmpHeader.biHeight << endl;
    cout << hex << "biPlanes: " << bmpHeader.biPlanes << endl;
    cout << hex << "biBitCount: " << bmpHeader.biBitCount << endl;
    cout << hex << "biCompression: " << bmpHeader.biCompression << endl;
    cout << hex << "biSizeImage: " << bmpHeader.biSizeImage << endl;
    cout << hex << "biXPelsPerMeter: " << bmpHeader.biXPelsPerMeter << endl;
    cout << hex << "biYPelsPerMeter: " << bmpHeader.biYPelsPerMeter << endl;
    cout << hex << "biClrUsed: " << bmpHeader.biClrUsed << endl;
    cout << hex << "biClrImportant: " << bmpHeader.biClrImportant << endl;
}

void bmp::writeBmpHeader(FILE *fp) {
    fwrite(&(bmpHeader.bfType), 1, sizeof(bmpHeader.bfType), fp);
    fwrite(&(bmpHeader.bfSize), 1, sizeof(bmpHeader.bfSize), fp);
    fwrite(&(bmpHeader.bfReserved), 1, sizeof(bmpHeader.bfReserved), fp);
    fwrite(&(bmpHeader.bfOffBits), 1, sizeof(bmpHeader.bfOffBits), fp);
    fwrite(&(bmpHeader.biSize), 1, sizeof(bmpHeader.biSize), fp);
    fwrite(&(bmpHeader.biWidth), 1, sizeof(bmpHeader.biWidth), fp);
    fwrite(&(bmpHeader.biHeight), 1, sizeof(bmpHeader.biHeight), fp);
    fwrite(&(bmpHeader.biPlanes), 1, sizeof(bmpHeader.biPlanes), fp);
    fwrite(&(bmpHeader.biBitCount), 1, sizeof(bmpHeader.biBitCount), fp);
    fwrite(&(bmpHeader.biCompression), 1, sizeof(bmpHeader.biCompression), fp);
    fwrite(&(bmpHeader.biSizeImage), 1, sizeof(bmpHeader.biSizeImage), fp);
    fwrite(&(bmpHeader.biXPelsPerMeter), 1, sizeof(bmpHeader.biXPelsPerMeter), fp);
    fwrite(&(bmpHeader.biYPelsPerMeter), 1, sizeof(bmpHeader.biYPelsPerMeter), fp);
    fwrite(&(bmpHeader.biClrUsed), 1, sizeof(bmpHeader.biClrUsed), fp);
    fwrite(&(bmpHeader.biClrImportant), 1, sizeof(bmpHeader.biClrImportant), fp);
}

void bmp::readMatrixRGB(FILE *fp) {
    MatrixRGB = new sRGB* [bmpHeader.biHeight];

    //Lines of bmp file has reversed posisions
    for (int i = bmpHeader.biHeight - 1; i >= 0; --i) {
        MatrixRGB[i] = new sRGB[bmpHeader.biWidth];
        fread(&(MatrixRGB[i]), bmpHeader.biWidth, sizeof(sRGB), fp);

        /*Size of every bmp file line shoud be multiply by 4 bytes.
         * So we skip garbage bits in the of line.
         */
        if (bmpHeader.biWidth % 4 != 0)
            fseek(fp, 4 - bmpHeader.biWidth % 4, SEEK_CUR);
    }
}

void bmp::writeMatrixRGB(FILE *fp) {
    for (int i = bmpHeader.biHeight - 1; i >= 0; --i) {
        fwrite(&(MatrixRGB[i]), bmpHeader.biWidth, sizeof(sRGB), fp);

        /*
         * Size of every bmp file line shoud be multiply by 4 bytes.
         * So we expand our line with zeros.
         */
        if (bmpHeader.biWidth % 4 != 0) {
            char tmp[4] {0};
            fwrite(&tmp, 4 - bmpHeader.biWidth % 4, sizeof(sRGB), fp);
        }
    }
}

void bmp::writeRGBToDifferentFile() {
    FILE *fR = fopen("r.bmp", "wb");
    FILE *fG = fopen("g.bmp", "wb");
    FILE *fB = fopen("b.bmp", "wb");

    writeBmpHeader(fR);
    writeBmpHeader(fG);
    writeBmpHeader(fB);
    for (int i = bmpHeader.biHeight - 1; i >= 0; --i) {
        for (int j = 0; j < bmpHeader.biWidth; ++j) {
            sRGB tmp {MatrixRGB[i][j].B, 0, 0};
            fwrite(&tmp, 1, sizeof(sRGB), fB);
            tmp.B = 0;
            tmp.G = MatrixRGB[i][j].G;
            fwrite(&tmp, 1, sizeof(sRGB), fG);
            tmp.G = 0;
            tmp.R = MatrixRGB[i][j].R;
            fwrite(&tmp, 1, sizeof(sRGB), fR);
        }
        if (bmpHeader.biWidth % 4 != 0) {
            char tmp[4] {0};
            fwrite(&tmp, 4 - bmpHeader.biWidth % 4, sizeof(sRGB), fR);
            fwrite(&tmp, 4 - bmpHeader.biWidth % 4, sizeof(sRGB), fG);
            fwrite(&tmp, 4 - bmpHeader.biWidth % 4, sizeof(sRGB), fB);
        }
    }
    fclose(fR);
    fclose(fG);
    fclose(fB);
}

bmp::~bmp() {
    for (int i = 0; i < bmpHeader.biHeight; ++i)
        delete [] MatrixRGB[i];
    delete [] MatrixRGB;
}
