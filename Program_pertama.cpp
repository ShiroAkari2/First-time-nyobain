//#include <bits/stdc++.h>
#include <iostream>
#include <ctime>
#include <string>

int main() {
    // Mengambil waktu sistem saat ini
    time_t now = time(0);
    
    // Mengubah waktu sistem menjadi format waktu lokal yang bisa dibaca
    char* dt = ctime(&now);

    std::cout << "Halo! Waktu dan tanggal saat ini adalah: " << dt << std::endl;

    return 0;
}
