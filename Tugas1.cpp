#include <iostream>
#include <iomanip>
using namespace std;

struct Data {
    string nama;
    string nim;
    float ipk;
};
Data mhs[] = {
    {"Juan", "1250", 3.4},
    {"Kennan", "1251", 4.0},
    {"Launa", "1252", 3.9},
    {"Malik", "1253", 3.1},
    {"Nuha", "1254", 3.6},
    {"Orion", "1255", 3.7},
    {"Pram", "1256", 3.5},
    {"Qiana", "1257", 3.0},
    {"Ribhan", "1258", 3.3},
    {"Suha", "1259", 3.2}
};
Data *pmhs = mhs;
int pil, bnyk = sizeof(mhs)/ sizeof(*mhs);
int binarySearch(Data mhs[], int bnyk, string cari);
void  menu(), sequenSearch(Data mhs[], int bnyk), quickSort(Data dt[], int l, int r), bubbleSort(Data mhs[], int bnyk), cetakDt(Data mhs[], int n);


int main () {
    cout << endl;
    cout << "~~~ Selamat datang di Pogram Data Mahasiswa ^U^ ~~~" << endl;
    cout << endl;
    do {
        int hasil;
        string cari;
        bool ketemu = false;
    
        menu();
        system ("cls");

        switch(pil) {
            case 1:
            cout << "----[ MENAMPILKAN DATA ]----" << endl;
            cout << endl;
            cetakDt(mhs, bnyk);
            cout << endl;
            system("pause");
            system("cls");
            break;

            case 2:
                sequenSearch(mhs, bnyk);
                system("pause");
                system("cls");
                break;
    
            case 3:
                cout << "Data atas Nama siapa yang anda cari?" << endl;
                cout << "!!Pastikan gunakan huruf kapital untuk menulis huruf pertama nama!!" << endl;
                while (true) {
                    cout << "Silahkan masukkan Nama : ";
                    cin >> cari;
                    cout << endl;
            
                    hasil = binarySearch(mhs, bnyk, cari);
            
                    if (hasil != -1) {
                        cout << "----[ DATA DITEMUKAN ]----" << endl;
                        cout << "NIM    : " << mhs[hasil].nim << endl;
                        cout << "Nama   : " << mhs[hasil].nama << endl;
                        cout << "IPK    : " << fixed << setprecision(2) << mhs[hasil].ipk << endl;
                        cout << endl;
                        cout << "fyi    : pencarian dilakukan dengan metode binary search ^v^ " << endl;
                        break;
                    } else {
                        cout << "Tidak ditemukan data atas nama : " << cari << endl;
                        cout << "Silahkan coba lagi.\n" << endl;
                    }
                }
                system("pause");
                system("cls");
                break;
    
            case 4:
                cout << "Berikut data sebelum diurutkan" << endl;
                cetakDt(mhs, bnyk);
                cout << endl;
                system("pause");
                quickSort(mhs, 0, bnyk - 1);
                cout << "----[ PENGURUTAN BERHASIL ]----" << endl;
                cout << endl;
                cout << "Berikut data setelah diurutkan" << endl;
                cout << endl;
                cetakDt(mhs, bnyk);
                cout << endl;
                cout << "fyi    : pengurutan IPK dilakukan secara ascending dengan metode quick sort ^v^ " << endl;
                system("pause");
                system("cls");
                break;

            case 5:
                cout << "Berikut data sebelum diurutkan" << endl;
                cetakDt(mhs, bnyk);
                cout << endl;
                system("pause");
                bubbleSort(mhs, bnyk);
                cout << "----[ PENGURUTAN BERHASIL ]----" << endl;
                cout << endl;
                cout << "Berikut data setelah diurutkan" << endl;
                cout << endl;
                cetakDt(mhs, bnyk);
                cout << endl;
                cout << "fyi    : pengurutan IPK dilakukan secara descending dengan metode bubble sort ^v^ " << endl;
                system("pause");
                system("cls");
                break;
    
            case 6:
                cout << "Selamat Tinggal, Terima kasih telah menggunakan program kami ^U^" << endl;
                break;

            default :
                cout << "Pilihan tidak tersedia!" << endl;
                break;
        }
    } while (pil != 6);

}

// fungsi menu
void menu () {
    cout << "=======[ MENU PROGRAM ]=======" << endl;
    cout << "1. Tampilkan Data Mahasiswa" << endl;
    cout << "2. Cari Berdasarkan NIM" << endl;
    cout << "3. Cari Berdasarkan Nama" << endl;
    cout << "4. Sort IPK Mahasiswa (asc)" << endl;
    cout << "5. Sort IPK Mahasiswa (desc)" << endl;
    cout << "6. Keluar" << endl;
    cout << "Pilih menu: ";
    cin >> pil;
}

// fungsi cari nim dengan sequential search
void sequenSearch(Data mhs[], int bnyk) {
    string cari;
    bool ketemu = false;

    cout << "Data dengan NIM berapa yang anda cari?" << endl;
    
    while (!ketemu) {
        cout << "Silahkan masukkan NIM : ";
        cin >> cari;
        cout << endl;

        for (int i = 0; i < bnyk; i++) {
            if (mhs[i].nim == cari) {
                ketemu = true;
                cout << "----[ DATA DITEMUKAN ]----" << endl;
                cout << "NIM    : " << mhs[i].nim << endl;
                cout << "Nama   : " << mhs[i].nama << endl;
                cout << "IPK    : " << fixed << setprecision(2) << mhs[i].ipk << endl;
                cout << endl;
                cout << "fyi    : pencarian dilakukan dengan metode sequential search ^v^ " << endl;
                return; 
            }
        }

        cout << "Tidak ditemukan data dengan NIM : " << cari << endl;
        cout << "Silahkan coba lagi.\n" << endl;
    }
}

// fungsi cari nama dengan binary search
int binarySearch(Data mhs[], int bnyk, string cari) {
    int awal = 0, akhir = bnyk - 1, tengah;
    
    while (awal <= akhir) {
        tengah = (awal + akhir) / 2;

        if (mhs[tengah].nama == cari) {
            return tengah; 
        } else if (mhs[tengah].nama > cari) {
            akhir = tengah - 1;
        } else {
            awal = tengah + 1;
        }
    }

    return -1; // Jika tidak ditemukan
}

// fungsi pengurutan ascending dengan quick sort
void quickSort(Data mhs[], int l, int r) {
    if (l >= r) return; 

    int i = l, j = r;
    float pivot = mhs[(l + r) / 2].ipk; // Menggunakan elemen tengah sebagai pivot

    do {
        while (mhs[i].ipk < pivot) i++; // Cari elemen yang lebih besar dari pivot
        while (mhs[j].ipk > pivot) j--; // Cari elemen yang lebih kecil dari pivot

        if (i <= j) {
            swap(mhs[i], mhs[j]);
            i++;
            j--;
        }
    } while (i <= j);

    // Rekursi untuk bagian kiri dan kanan
    if (l < j) quickSort(mhs, l, j);
    if (i < r) quickSort(mhs, i, r);
}

// fungsi pengurutan descending dengan bubble sort
void bubbleSort(Data mhs[], int bnyk) {
    for (int i = 0; i < bnyk - 1; i++) {
        for (int j = 0; j < bnyk - 1 - i; j++) {
            if (mhs[j].ipk < mhs[j + 1].ipk) {
                swap(mhs[j], mhs[j + 1]); // Menukar struct data
            }
        }
    }
}

void cetakDt(Data mhs[], int bnyk) {
    cout << setfill ('=') << setw (30) << "=";
    cout << setfill (' ') << endl;
    cout << "| No.  |" << " NIM  |" << " Nama  |" << " IPK  |" << endl;
    cout << setfill ('=') << setw (30) << "=";
    cout << setfill (' ') << endl;

    for (int n = 0; n < bnyk; n++ ) {
        cout << setiosflags (ios::left) 
        << "|" << setw(8) << n+1  
        << setw(7) << (pmhs + n)->nim 
        << setw(8) << (pmhs + n)->nama 
        << setw(5) << fixed << setprecision(2) << (pmhs + n)->ipk 
        << "|"; 
        cout << endl;
    }

    cout << setfill (' ') << endl;
    cout << setfill ('-') << setw (30) << "-";
}
