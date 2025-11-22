/**
* @file MainNode.cpp
* @description Ana çift yönlü listenin düğüm sınıfı (her düğüm bir ShapeList tutar)
* @course Veri Yapıları 2-A
* @assignment 1.Ödev
* @date 18.11.2025
* @author Batuhan Bektaş batuhan.bektas1@ogr.sakarya.edu.tr G231210379
*/

#include "MainNode.hpp"

using namespace std;

MainNode::MainNode()
    : prev(nullptr), next(nullptr), shapes()
{
}
