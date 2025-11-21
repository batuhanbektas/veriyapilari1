/**
 * @file App.cpp
 * @description Program akışı, kullanıcı etkileşimi, liste ve şekil kontrolü
 * @course Veri Yapıları 2-A
 * @assignment 1.Ödev
 * @date 20.11.2025
 * @author Batuhan Bektaş batuhan.bektas1@ogr.sakarya.edu.tr G231210379
 */

#include <iostream>
#include <conio.h>
#include <string>
#include "../include/App.hpp"
#include "../include/MainList.hpp"
#include "../include/Shape.hpp"
#include "../include/ShapeNode.hpp"
#include "../include/Screen.hpp"

App::App() {
    // Açılışta kullanıcıya sor: Dosyadan mı, rastgele mi?
    char secim;
    std::cout << "Sahne nasil yüklensin?\n";
    std::cout << "1) Dosyadan yukle (data.txt)\n";
    std::cout << "2) Rastgele olustur\n";
    std::cout << "Secim (1/2): ";
    std::cin >> secim;

    if (secim == '1') {
        // Dosyadan yükleme
        mainList.loadFromFile("data.txt");

        // Dosya bos veya hataliysa fallback: rastgele olustur
        if (mainList.getSize() == 0) {
            std::cout << "Dosya okunamadi ya da sahne bos. "
                         "Rastgele sahne olusturuluyor...\n";
            mainList.generateRandom(20);  // ~20 node
        }
    }
    else {
        // Rastgele sahne
        mainList.generateRandom(20);      // ~20 node
    }

    currentMain  = mainList.getCurrent();
    currentShape = nullptr;
    mode         = MODE_LIST;     // önce liste modundan başla
}

void App::drawNodeList(Screen& screen) {
    MainNode* node = mainList.getHead();
    int idx = 0;
    int y   = 0;

    while (node && y < ROWS) {
        int displayIndex = idx + 1; // 1'den başlasın
        int shapeCount   = node->shapes.getSize();

        std::string line = std::to_string(displayIndex) + " (" + std::to_string(shapeCount) + ")";
        if (node == currentMain)
            line += " <--";

        for (size_t i = 0; i < line.size() && (int)i < COLS; ++i) {
            screen.setPixel((int)i, y, line[i]);
        }

        node = node->next;
        y++;
        idx++;
    }
}

void App::renderAll(Screen& screen) {
    // Aktif node'un tüm şekillerini z-sıralı çizer
    mainList.drawAll(screen);

    // Solda node listesini çiz
    drawNodeList(screen);

    // Şekil modunda isek seçili shape'i işaretle
    if (mode == MODE_SHAPE && currentShape) {
        Shape* s = currentShape->data;
        screen.setPixel(s->getX(), s->getY(), '@');  // seçili shape işareti
    }
}

void App::handleInput(char key) {
    //---------------------------------------
    // 1) LİSTE MODU – sadece node'lar arasında gezinme
    //---------------------------------------
    if (mode == MODE_LIST) {
        if (key == 'w' || key == 'W') {
            mainList.prevNode();
            currentMain  = mainList.getCurrent();
            currentShape = nullptr;
            return;
        }
        if (key == 's' || key == 'S') {
            mainList.nextNode();
            currentMain  = mainList.getCurrent();
            currentShape = nullptr;
            return;
        }
        // Şu anki node'u seç ve şekil moduna gir
        if ((key == 'f' || key == 'F') && currentMain) {
            mode         = MODE_SHAPE;
            currentShape = currentMain->shapes.getHead();
            return;
        }
        // Node sil
        if (key == 'c' || key == 'C') {
            mainList.removeCurrent();
            currentMain  = mainList.getCurrent();
            currentShape = nullptr;
            return;
        }

        // Liste modunda başka tuşlar bir şey yapmasın
        return;
    }

    //---------------------------------------
    // 2) ŞEKİL MODU – seçili node'un şekilleri
    //---------------------------------------
    if (mode == MODE_SHAPE) {

        // Seçili node boş kaldıysa node'u da sil ve liste moduna dön
        if (currentMain && currentMain->shapes.isEmpty()) {
            mainList.removeCurrent();
            currentMain  = mainList.getCurrent();
            currentShape = nullptr;
            mode         = MODE_LIST;
            return;
        }

        if (!currentMain) {
            // Node kalmamışsa tekrar liste moduna dön
            mode         = MODE_LIST;
            currentShape = nullptr;
            return;
        }

        // g: liste moduna geri dön
        if (key == 'g' || key == 'G') {
            mode         = MODE_LIST;
            currentShape = nullptr;
            return;
        }

        // q: önceki shape
        if (key == 'q' || key == 'Q') {
            if (currentShape && currentShape != currentMain->shapes.getHead()) {
                ShapeNode* iter = currentMain->shapes.getHead();
                while (iter && iter->next != currentShape)
                    iter = iter->next;
                if (iter) currentShape = iter;
            }
            return;
        }

        // e: sonraki shape
        if (key == 'e' || key == 'E') {
            if (currentShape && currentShape->next)
                currentShape = currentShape->next;
            return;
        }

        // c: seçili shape'i sil
        if (key == 'c' || key == 'C') {
            if (currentMain && currentShape) {

                // 1) currentShape'in listedeki indeksini bul
                int index = 0;
                ShapeNode* iter = currentMain->shapes.getHead();
                while (iter && iter != currentShape) {
                    iter = iter->next;
                    index++;
                }

                // Her ihtimale karşı: currentShape listede değilse hiçbir şey yapma
                if (!iter) return;

                // 2) Seçili shape'i sil
                currentMain->shapes.removeIndex(index);

                // 3) Bu node'un içinde hiç shape kalmadıysa node'u da sil
                if (currentMain->shapes.isEmpty()) {
                    mainList.removeCurrent();              // current node'u listeden sil
                    currentMain  = mainList.getCurrent();  // yeni current node (veya nullptr)
                    currentShape = nullptr;
                    mode         = MODE_LIST;              // şekil kalmadı, liste moduna dön
                    return;                                // önemli: buradan çık
                }

                // 4) Hâlâ şekil varsa, basitçe baştaki shape'i seç
                currentShape = currentMain->shapes.getHead();
            }
            return;
        }

        // Hareket: w/a/s/d
        if (currentShape) {
            Shape* s = currentShape->data;
            int dx = 0, dy = 0;

            if (key == 'w' || key == 'W') dy = -1; // yukarı
            if (key == 's' || key == 'S') dy =  1; // aşağı
            if (key == 'a' || key == 'A') dx = -1; // sol
            if (key == 'd' || key == 'D') dx =  1; // sağ

            if (dx != 0 || dy != 0) {
                s->move(dx, dy);

                // sınır kontrolü
                int x = s->getX();
                int y = s->getY();
                int w = s->getWidth();
                int h = s->getHeight();

                if (x < 0) x = 0;
                if (y < 0) y = 0;
                if (x + w > COLS) x = COLS - w;
                if (y + h > ROWS) y = ROWS - h;

                if (x < 0) x = 0;
                if (y < 0) y = 0;

                s->setPosition(x, y);
            }
        }

        return;
    }
}

void App::run() {
    Screen screen;
    char key = ' ';

    while (true) {
        screen.clear();
        renderAll(screen);
        screen.render();

        std::cout << "\n-------------------------\n";
        std::cout << "Node sayisi : " << mainList.getSize() << "\n";

        if (currentMain) {
            int shapeCount = currentMain->shapes.getSize();
            std::cout << "Aktif Node Shape sayisi : " << shapeCount << "\n";
        } else {
            std::cout << "Listede hic Node kalmadi.\n";
        }

        if (mode == MODE_LIST) {
            std::cout << "\n[LİSTE MODU]\n";
            std::cout << "(w/s) listede yukari/asagi\n";
            std::cout << "(f)   secili node'un sekillerine git\n";
            std::cout << "(c)   node sil\n";
        } else {
            std::cout << "\n[SEKİL MODU]\n";
            std::cout << "(w/a/s/d) sekli hareket ettir\n";
            std::cout << "(q) onceki sekil   (e) sonraki sekil\n";
            std::cout << "(c) sekil sil      (g) liste moduna don\n";
        }

        std::cout << "\n(0) Cikis (ve kaydet)\n";

        key = _getch();

        // 0'a basınca dosyaya kaydet ve programdan çık
        if (key == '0') {
            mainList.saveToFile("data.txt");
            break;
        }

        handleInput(key);
    }
}
