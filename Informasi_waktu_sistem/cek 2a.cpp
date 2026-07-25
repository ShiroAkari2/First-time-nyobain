#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>

using namespace std;

// Fungsi untuk mengecek apakah tahun kabisat
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Fungsi untuk menentukan salam berdasarkan jam (24 Jam)
string getGreeting(int hour) {
    if (hour >= 4 && hour < 11) return "Selamat Pagi 🌅";
    if (hour >= 11 && hour < 15) return "Selamat Siang ☀️";
    if (hour >= 15 && hour < 18) return "Selamat Sore 🌇";
    return "Selamat Malam 🌙";
}

// Fungsi untuk konversi jam 24-jam ke format 12-jam (AM/PM)
string getFormat12Hour(int hour, int min, int sec) {
    string period = (hour >= 12) ? "PM" : "AM";
    int hour12 = hour % 12;
    if (hour12 == 0) hour12 = 12;

    stringstream ss;
    ss << setfill('0') << setw(2) << hour12 << ":"
       << setfill('0') << setw(2) << min << ":"
       << setfill('0') << setw(2) << sec << " " << period;
    return ss.str();
}

int main() {
    // 1. Pengaturan Offset Zona Waktu (WITA = 8, WIB = 7, WIT = 9)
    const int TIMEZONE_OFFSET = 8; 
    const string NAMA_ZONA = (TIMEZONE_OFFSET == 8) ? "WITA" : (TIMEZONE_OFFSET == 7 ? "WIB" : "WIT");

    // 2. Ambil waktu epoch sistem & sesuaikan offset
    time_t now = time(nullptr);
    now += TIMEZONE_OFFSET * 3600;

    // 3. Konversi ke struktur UTC
    tm *ltm = gmtime(&now);

    // 4. Array Nama Hari & Bulan
    const string namaHari[] = {
        "Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"
    };
    
    const string namaBulan[] = {
        "Januari", "Februari", "Maret", "April", "Mei", "Juni",
        "Juli", "Agustus", "September", "Oktober", "November", "Desember"
    };

    // 5. Ekstraksi Komponen Waktu
    string hari   = namaHari[ltm->tm_wday];
    int tanggal   = ltm->tm_mday;
    string bulan  = namaBulan[ltm->tm_mon];
    int tahun     = 1900 + ltm->tm_year;

    int jam       = ltm->tm_hour;
    int menit     = ltm->tm_min;
    int detik     = ltm->tm_sec;
    
    int hariKeDalamTahun = ltm->tm_yday + 1; // tm_yday dimulai dari 0
    int mingguKe         = (hariKeDalamTahun / 7) + 1;

    // 6. Tampilan Output Dashboard
    cout << "======================================================" << endl;
    cout << "             DASHBOARD WAKTU SISTEM                   " << endl;
    cout << "======================================================" << endl;
    cout << " " << getGreeting(jam) << "! Selamat datang kembali.\n" << endl;

    cout << " [ Tanggal & Kalender ]" << endl;
    cout << "   • Hari         : " << hari << endl;
    cout << "   • Tanggal      : " << tanggal << " " << bulan << " " << tahun << endl;
    cout << "   • Hari Ke-     : " << hariKeDalamTahun << " dari " << (isLeapYear(tahun) ? 366 : 365) << " hari" << endl;
    cout << "   • Minggu Ke-   : " << mingguKe << endl;
    cout << "   • Status Tahun : " << (isLeapYear(tahun) ? "Tahun Kabisat (Leap Year)" : "Bukan Tahun Kabisat") << endl;
    cout << endl;

    cout << " [ Waktu & Jam ]" << endl;
    cout << "   • Format 24-Jam: " 
         << setfill('0') << setw(2) << jam << ":"
         << setfill('0') << setw(2) << menit << ":"
         << setfill('0') << setw(2) << detik 
         << " (" << NAMA_ZONA << " / UTC+" << TIMEZONE_OFFSET << ")" << endl;
         
    cout << "   • Format 12-Jam: " << getFormat12Hour(jam, menit, detik) << endl;
    cout << "======================================================" << endl;

    return 0;
}
