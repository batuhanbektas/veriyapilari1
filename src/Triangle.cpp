/**
* @file Triangle.cpp
* @description Üçgen şeklini ekrana çizen sınıfın kaynak dosyası
* @course Veri Yapıları 2-A
* @assignment 1.Ödev
* @date 19.11.2025
* @author Batuhan Bektaş batuhan.bektas1@ogr.sakarya.edu.tr G231210379
*/

#include "Triangle.hpp"

Triangle::Triangle(int x, int y, int width, int height, int z, char drawChar)
    : Shape(x, y, width, height, z, drawChar) {}

void Triangle::draw(Screen& screen) {
    // Sol taraftan başlayan, aşağı doğru genişleyen dolu üçgen
    // y satırı arttıkça, o satırdaki karakter sayısı artıyor
    for (int dy = 0; dy < height; ++dy) {
        // Satırdaki genişlik: yükseklikle orantılı olacak şekilde ayarlandı
        int rowWidth = (width * (dy + 1)) / height;
        if (rowWidth < 1) rowWidth = 1;

        for (int dx = 0; dx < rowWidth; ++dx) {
            screen.setPixel(x + dx, y + dy, drawChar);
        }
    }
}
