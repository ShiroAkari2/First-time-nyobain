#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream> // Diperlukan untuk std::stringstream

using namespace std;

namespace TimeUtils {

    // Mengecek apakah tahun kabisat (Leap Year)
    constexpr bool isLeapYear(int year) noexcept {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    // Mendapatkan jumlah hari dalam satu bulan tertentu
    int getDaysInMonth(int month, int year) {
        static const int daysPerMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (month == 2 && isLeapYear(year)) return 29;
        return daysPerMonth[month - 1];
    }

    // Menentukan ucapan salam berdasarkan jam
    string getGreeting(int hour) {
        if (hour >= 4 && hour < 11)  return "Selamat Pagi 🌅";
        if (hour >= 11 && hour < 15) return "Selamat Siang ☀️";
        if (hour >= 15 && hour < 18) return "Selamat Sore 🌇";
        return "Selamat Malam 🌙";
    }

    // Konversi jam 24-jam ke format 12-jam (AM/PM)
    string format12Hour(int hour, int min, int sec) {
        string period = (hour >= 12) ? "PM" : "AM";
        int hour12 = hour % 12;
        if (hour12 == 0) hour12 = 12;

        stringstream ss;
        ss << setfill('0') << setw(2) << hour12 << ":"
           << setfill('0') << setw(2) << min << ":"
           << setfill('0') << setw(2) << sec << " " << period;
        return ss.str();
    }

    // Menghitung estimasi sisa hari menuju akhir tahun
    int getRemainingDaysInYear(int dayOfYear, int year) {
        int totalDays = isLeapYear(year) ? 366 : 365;
        return totalDays - dayOfYear;
    }

    // Menghitung persentase progres tahun berjalan
    double getYearProgressPercentage(int dayOfYear, int year) {
        int totalDays = isLeapYear(year) ? 366 : 365;
        return (static_cast<double>(dayOfYear) / totalDays) * 100.0;
    }
}

int main() {
    // ---------------------------------------------------------
    // 1. Konfigurasi Zona Waktu (Default: WITA = UTC+8)
    // ---------------------------------------------------------
    const int TIMEZONE_OFFSET_HOURS = 8; 
    
    string namaZona;
    switch (TIMEZONE_OFFSET_HOURS) {
        case 7:  namaZona = "WIB";  break;
        case 8:  namaZona = "WITA"; break;
        case 9:  namaZona = "WIT";  break;
        default: namaZona = "UTC" + string(TIMEZONE_OFFSET_HOURS >= 0 ? "+" : "") + to_string(TIMEZONE_OFFSET_HOURS);
    }

    // ---------------------------------------------------------
    // 2. Kalkulasi Waktu Sistem dengan Offset
    // ---------------------------------------------------------
    time_t rawNow = time(nullptr);
    time_t targetTime = rawNow + (TIMEZONE_OFFSET_HOURS * 3600);

    // Menggunakan gmtime untuk mengonversi detik epoch ke struct tm berbasis UTC
    tm* ltm = gmtime(&targetTime);

    if (!ltm) {
        cerr << "Gagal mengambil waktu sistem!" << endl;
        return 1;
    }

    // Data Referensi Kalender
    static const string namaHari[] = {
        "Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"
    };

    static const string namaBulan[] = {
        "Januari", "Februari", "Maret", "April", "Mei", "Juni",
        "Juli", "Agustus", "September", "Oktober", "November", "Desember"
    };

    // Ekstraksi Variabel
    string hari          = namaHari[ltm->tm_wday];
    int tanggal          = ltm->tm_mday;
    int indexBulan       = ltm->tm_mon;
    string bulan         = namaBulan[indexBulan];
    int tahun            = 1900 + ltm->tm_year;

    int jam              = ltm->tm_hour;
    int menit            = ltm->tm_min;
    int detik            = ltm->tm_sec;

    int hariKeDalamTahun = ltm->tm_yday + 1;
    int mingguKe         = ((hariKeDalamTahun - 1) / 7) + 1;
    int sisaHari         = TimeUtils::getRemainingDaysInYear(hariKeDalamTahun, tahun);
    double progresTahun  = TimeUtils::getYearProgressPercentage(hariKeDalamTahun, tahun);

    // ---------------------------------------------------------
    // 3. Tampilan Dashboard Utama
    // ---------------------------------------------------------
    cout << "============================================================" << endl;
    cout << "                 DASHBOARD WAKTU & KALENDER                 " << endl;
    cout << "============================================================" << endl;
    cout << " " << TimeUtils::getGreeting(jam) << "! Sistem berjalan normal.\n" << endl;

    // Seksi Tanggal
    cout << " 📌 [ KALENDER & TANGGAL ]" << endl;
    cout << "    • Hari           : " << hari << endl;
    cout << "    • Tanggal        : " << setfill('0') << setw(2) << tanggal << " " << bulan << " " << tahun << endl;
    cout << "    • Hari ke-       : " << hariKeDalamTahun << " dari " << (TimeUtils::isLeapYear(tahun) ? 366 : 365) << " hari" << endl;
    cout << "    • Minggu ke-     : " << mingguKe << endl;
    cout << "    • Total Hari Bulan ini : " << TimeUtils::getDaysInMonth(indexBulan + 1, tahun) << " Hari" << endl;
    cout << "    • Status Tahun   : " << (TimeUtils::isLeapYear(tahun) ? "Tahun Kabisat (366 Hari)" : "Bukan Kabisat (365 Hari)") << endl;
    cout << endl;

    // Seksi Waktu
    cout << " ⏰ [ WAKTU & PRESISI ]" << endl;
    cout << "    • Format 24-Jam  : " 
         << setfill('0') << setw(2) << jam << ":"
         << setfill('0') << setw(2) << menit << ":"
         << setfill('0') << setw(2) << detik 
         << " (" << namaZona << " / UTC" << (TIMEZONE_OFFSET_HOURS >= 0 ? "+" : "") << TIMEZONE_OFFSET_HOURS << ")" << endl;
    cout << "    • Format 12-Jam  : " << TimeUtils::format12Hour(jam, menit, detik) << endl;
    cout << endl;

    // Seksi Progres Tahun (Fitur Tambahan)
    cout << " 📊 [ PROGRES TAHUN " << tahun << " ]" << endl;
    cout << "    • Sisa Hari      : " << sisaHari << " Hari lagi menuju tahun " << (tahun + 1) << endl;
    cout << "    • Progres Berlalu: " << fixed << setprecision(2) << progresTahun << "%" << endl;
    cout << "============================================================" << endl;

    return 0;
}
