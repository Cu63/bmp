#ifndef BMP_HPP
#define BMP_HPP

#include <cstdint>
#include <iostream>

class bmp {
    private:
        typedef struct s_bmp {
            uint16_t    bfType;         // 0x4d42 | 0x4349 | 0x5450
            uint32_t    bfSize;         // размер файла
            uint32_t    bfReserved;     // 0
            uint32_t    bfOffBits;      // смещение до поля данных,
                                         // обычно 54 = 16 + biSize
            uint32_t    biSize;         // размер струкуры в байтах:
                                 // 40(BITMAPINFOHEADER) или 108(BITMAPV4HEADER)
                                 // или 124(BITMAPV5HEADER)
            uint32_t    biWidth;        // ширина в точках
            uint32_t    biHeight;       // высота в точках
            uint16_t    biPlanes;       // всегда должно быть 1
            uint16_t    biBitCount;     // 0 | 1 | 4 | 8 | 16 | 24 | 32
            uint32_t    biCompression;  // BI_RGB | BI_RLE8 | BI_RLE4 |
                                 // BI_BITFIELDS | BI_JPEG | BI_PNG
                                 // реально используется лишь BI_RGB
            uint32_t    biSizeImage;    // Количество байт в поле данных
                                 // Обычно устанавливается в 0
            uint32_t    biXPelsPerMeter;// горизонтальное разрешение, точек на дюйм
            uint32_t    biYPelsPerMeter;// вертикальное разрешение, точек на дюйм
            uint32_t    biClrUsed;      // Количество используемых цветов
                                 // (если есть таблица цветов)
            uint32_t    biClrImportant; // Количество существенных цветов.
                                 // Можно считать, просто 0
        } sBmpHeader;

        typedef struct s_rgb {
            uint8_t B;
            uint8_t G;
            uint8_t R;
        } sRGB;

         sBmpHeader bmpHeader;
         sRGB **MatrixRGB;

    public:
        bmp();
        void readBmp(FILE *fp);
        void writeBmp(FILE *fp);
        void readBmpHeader(FILE *fp);
        void printBmpHeader();
        void writeBmpHeader(FILE *fp);
        void readMatrixRGB(FILE *fp);
        void writeMatrixRGB(FILE *fp);
        void writeRGBToDifferentFile();
        ~bmp();
};


#endif
