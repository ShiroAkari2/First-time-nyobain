
//#include<bits/stdc++.h>
#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    // 1. Pengaturan Offset Zona Waktu
    // Ubah ke 8 untuk WITA, 7 untuk WIB, atau 9 untuk WIT
    const int TIMEZONE_OFFSET = 8; 

    // 2. Mengambil waktu sistem saat ini (epoch time)
    time_t now = time(nullptr);

    // 3. Menyesuaikan waktu dengan offset detik (1 jam = 3600 detik)
    now += TIMEZONE_OFFSET * 3600;

    // 4. Konversi ke struktur waktu UTC (gmtime)
    tm *ltm = gmtime(&now);

    // 5. Data nama hari dan bulan dalam Bahasa Indonesia
    const string namaHari[] = {
        "Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"
    };
    
    const string namaBulan[] = {
        "Januari", "Februari", "Maret", "April", "Mei", "Juni",
        "Juli", "Agustus", "September", "Oktober", "November", "Desember"
    };

    // 6. Ekstraksi komponen hari, tanggal, dan waktu
    string hari  = namaHari[ltm->tm_wday];
    int tanggal  = ltm->tm_mday;
    string bulan = namaBulan[ltm->tm_mon];
    int tahun    = 1900 + ltm->tm_year;

    int jam   = ltm->tm_hour;
    int menit = ltm->tm_min;
    int detik = ltm->tm_sec;

    // 7. Penentuan salam otomatis berdasarkan jam
    string salam;
    if (jam >= 4 && jam < 11) {
        salam = "Selamat Pagi";
    } else if (jam >= 11 && jam < 15) {
        salam = "Selamat Siang";
    } else if (jam >= 15 && jam < 18) {
        salam = "Selamat Sore";
    } else {
        salam = "Selamat Malam";
    }

    // 8. Menampilkan output ke layar
    cout << "==========================================" << endl;
    cout << "        INFORMASI WAKTU SISTEM            " << endl;
    cout << "==========================================" << endl;
    
    cout << salam << "! Selamat datang.\n" << endl;

    cout << "Hari       : " << hari << endl;
    cout << "Tanggal    : " << tanggal << " " << bulan << " " << tahun << endl;
    
    // Format agar jam, menit, dan detik selalu ditampilkan 2 digit (misal: 05:57:02)
    cout << "Pukul      : " 
         << setfill('0') << setw(2) << jam << ":"
         << setfill('0') << setw(2) << menit << ":"
         << setfill('0') << setw(2) << detik 
         << " (UTC+" << TIMEZONE_OFFSET << ")" << endl;
              
    cout << "==========================================" << endl;

    return 0;
}
