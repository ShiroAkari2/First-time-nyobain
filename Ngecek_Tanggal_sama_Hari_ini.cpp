//#include <iostream>
//#include <ctime>
#include <bits/stdc++.h>

int main() {
    // 1. Mengambil waktu sistem saat ini
    time_t now = time(0);
    tm *ltm = localtime(&now);

    // 2. Array untuk nama hari dan bulan dalam bahasa Indonesia
    std::string namaHari[] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
    std::string namaBulan[] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", 
                               "Juli", "Agustus", "September", "Oktober", "November", "Desember"};

    // 3. Mengambil komponen hari, tanggal, bulan, dan tahun
    std::string hari = namaHari[ltm->tm_wday];
    int tanggal = ltm->tm_mday;
    std::string bulan = namaBulan[ltm->tm_mon];
    int tahun = 1900 + ltm->tm_year; // tm_year dihitung dari tahun 1900

    // 4. Menampilkan hasil
    std::cout << "Hari ini adalah : " << hari << std::endl;
    std::cout << "Tanggal         : " << tanggal << " " << bulan << " " << tahun << std::endl;

    return 0;
}
