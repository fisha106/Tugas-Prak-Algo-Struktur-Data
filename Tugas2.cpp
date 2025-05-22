#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//Node untuk antrean 
struct QueueNode {
    string nama;
    string jenisRoti;
    int totalHarga;
    QueueNode *next;
    QueueNode *prev;
};

//Node untuk riwayat stack
struct StackNode {
    string nama;
    string jenisRoti;
    int totalHarga;
    StackNode *next;
};

// Daftar menu roti
const int JUMLAH_MENU = 4;
string daftarRoti[JUMLAH_MENU] = {"Coklat", "Keju", "Pisang", "Sosis"};
int hargaRoti[JUMLAH_MENU] = {10000, 12000, 11000, 13000};

// Pointer antrean
QueueNode *headAntrean = NULL;
QueueNode *tailAntrean = NULL;

// Pointer top stack riwayat
StackNode *topRiwayat = NULL;

// Fungsi menambahkan ke antrean
void ambilAntrean() {
    QueueNode *baru = new QueueNode;
    cout << "Masukkan nama pembeli: ";
    cin.ignore();
    getline(cin, baru->nama);
    cout << endl;

    // Tampilkan daftar menu roti
    cout << setfill('=') << setw(19) << "=";
    cout << "\n     Menu Roti\n";
    cout << setfill('-') << setw(19) << "-" << endl;
    for (int i = 0; i < JUMLAH_MENU; i++) {
        cout << i + 1 << ". " << daftarRoti[i] << " - Rp" << hargaRoti[i] << endl;
    }
    cout << setfill('-') << setw(19) << "-" << endl;
    int pilihanRoti;
    cout << "Pilih jenis roti [1-" << JUMLAH_MENU << "]: ";
    cin >> pilihanRoti;

    while (pilihanRoti < 1 || pilihanRoti > JUMLAH_MENU) {
        cout << "Pilihan tidak valid. Pilih lagi: ";
        cin >> pilihanRoti;
    }

    baru->jenisRoti = daftarRoti[pilihanRoti - 1];
    baru->totalHarga = hargaRoti[pilihanRoti - 1];
    baru->next = NULL;
    baru->prev = NULL;

    if (headAntrean == NULL) {
        headAntrean = tailAntrean = baru;
    } else {
        tailAntrean->next = baru;
        baru->prev = tailAntrean;
        tailAntrean = baru;
    }

    cout << setfill('=') << setw(25) << "=" << endl;
    cout << "Pesanan masuk ke antrean.\n";
    cout << setfill('=') << setw(25) << "=" << endl;
}

// Fungsi melayani pembeli
void layaniPesanan() {
    if (headAntrean == NULL) {
        cout << "Antrean kosong!\n";
        return;
    }

    QueueNode *dilayani = headAntrean;
    cout << "---[Melayani pesanan atas nama: " << dilayani->nama << "]---" << endl;

    // Tambahkan ke stack riwayat 
    StackNode *baru = new StackNode;
    baru->nama = dilayani->nama;
    baru->jenisRoti = dilayani->jenisRoti;
    baru->totalHarga = dilayani->totalHarga;
    baru->next = topRiwayat;
    topRiwayat = baru;

    // Hapus dari antrean
    headAntrean = headAntrean->next;
    if (headAntrean != NULL)
        headAntrean->prev = NULL;
    else
        tailAntrean = NULL;

    delete dilayani;
}

// Fungsi menampilkan antrean
void tampilkanAntrean() {
    if (headAntrean == NULL) {
        cout << "Antrean kosong.\n";
        return;
    }

    cout << "Daftar antrean:\n";
    QueueNode *current = headAntrean;
    int no = 1;
    while (current != NULL) {
        cout << no++ << ". " << current->nama << " - " << current->jenisRoti << " - Rp" << current->totalHarga << endl;
        current = current->next;
    }
}

// Fungsi membatalkan pesanan terakhir (hapus tail antrean)
void batalkanPesananTerakhir() {
    if (tailAntrean == NULL) {
        cout << "Antrean kosong, tidak ada yang dibatalkan.\n";
        return;
    }

    cout << "Pesanan terakhir dibatalkan: " << tailAntrean->nama << endl;
    QueueNode *hapus = tailAntrean;
    tailAntrean = tailAntrean->prev;
    if (tailAntrean != NULL)
        tailAntrean->next = NULL;
    else
        headAntrean = NULL;

    delete hapus;
}

// Fungsi menampilkan riwayat
void tampilkanRiwayat() {
    if (topRiwayat == NULL) {
        cout << "Belum ada pesanan yang dilayani.\n";
        return;
    }

    cout << "History Pesanan yang Sudah Dilayani:\n";
    StackNode *current = topRiwayat;
    int no = 1;
    while (current != NULL) {
        cout << no++ << ". " << current->nama << " - " << current->jenisRoti << " - Rp" << current->totalHarga << endl;
        current = current->next;
    }
}

int main() {
    int pilihan;

    cout << "Selamat Datang di Program Pelayanan Toko Roti Manis Lezat ^U^" << endl;
    do {
        cout << "\n=== Toko Roti Manis Lezat ===" << endl;
        cout << "1. Ambil Antrean" << endl;
        cout << "2. Layani Pembeli" << endl;
        cout << "3. Tampilkan Pesanan (Antrean)" << endl;
        cout << "4. Batalkan Pesanan Terakhir" << endl;
        cout << "5. Tampilkan History Pesanan" << endl;
        cout << "0. Keluar" << endl;
        cout << setfill('-') << setw(30) << "-" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;
        cout << setfill('=') << setw(30) << "=" << endl;
        cout << endl;

        switch (pilihan) {
            case 1: ambilAntrean(); break;
            case 2: layaniPesanan(); break;
            case 3: tampilkanAntrean(); break;
            case 4: batalkanPesananTerakhir(); break;
            case 5: tampilkanRiwayat(); break;
            case 0: cout << "Terima kasih! Sampai Jumpa Lagi ^^" << endl; break;
            default: cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);

    return 0;
}
