#include <iostream>
#include <ctime>
#include <string>
#include <iomanip> // Diperlukan untuk std::setfill dan std::setw (format jam:menit:detik)
//#include<bits/stdc++.h>
//using namespace std;

int main() {
    // 1. Mengambil waktu sistem saat ini
    std::time_t now = std::time(nullptr);
    std::tm *ltm = std::localtime(&now);

    // 2. Data nama hari dan bulan dalam Bahasa Indonesia
    const std::string namaHari[] = {
        "Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"
    };
    
    const std::string namaBulan[] = {
        "Januari", "Februari", "Maret", "April", "Mei", "Juni",
        "Juli", "Agustus", "September", "Oktober", "November", "Desember"
    };

    // 3. Ekstraksi komponen tanggal dan waktu
    std::string hari = namaHari[ltm->tm_wday];
    int tanggal     = ltm->tm_mday;
    std::string bulan= namaBulan[ltm->tm_mon];
    int tahun       = 1900 + ltm->tm_year;

    int jam   = ltm->tm_hour;
    int menit = ltm->tm_min;
    int detik = ltm->tm_sec;

    // 4. Penentuan salam berdasarkan jam
    std::string salam;
    if (jam >= 4 && jam < 11) {
        salam = "Selamat Pagi";
    } else if (jam >= 11 && jam < 15) {
        salam = "Selamat Siang";
    } else if (jam >= 15 && jam < 18) {
        salam = "Selamat Sore";
    } else {
        salam = "Selamat Malam";
    }

    // 5. Tampilan Output yang Rapi
    std::cout << "==========================================" << std::endl;
    std::cout << "        INFORMASI WAKTU SISTEM            " << std::endl;
    std::cout << "==========================================" << std::endl;
    
    std::cout << salam << "! Selamat datang.\n" << std::endl;

    std::cout << "Hari       : " << hari << std::endl;
    std::cout << "Tanggal    : " << tanggal << " " << bulan << " " << tahun << std::endl;
    
    // std::setw(2) dan std::setfill('0') memastikan format angka selalu 2 digit (misal 08:05:09)
    std::cout << "Pukul      : " 
              << std::setfill('0') << std::setw(2) << jam << ":"
              << std::setfill('0') << std::setw(2) << menit << ":"
              << std::setfill('0') << std::setw(2) << detik << " WIB/Lokal" << std::endl;

    // Tampilan versi ringkas bawaan ctime (dari Program 1)
    char* dt = std::ctime(&now);
    std::cout << "\n[Format Mentah System] : " << dt; 
    std::cout << "==========================================" << std::endl;

    return 0;
}
