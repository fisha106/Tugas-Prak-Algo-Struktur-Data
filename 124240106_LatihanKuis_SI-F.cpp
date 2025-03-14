#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring> 
using namespace std;

struct Data {
    char nama[50];
    char nim[10];
    char jurusan[50];
    char tahun[5];
    float ipk;
};

void quickSort(Data mhs[], int l, int r);
void tambahmhs();
void tampilkanmhs();
void carimhsnim();
void carimhsjur();
void perbaruiIPK();
void hapusMahasiswa();

int main() {
    int pil;
    cout << "Selamat Datang di Sistem Pengelolaan Data Mahasiswa SmartCampus++" << endl;

    do {
        cout << "MENU:\n"
             << "1. Input Data Mahasiswa\n"
             << "2. Menampilkan Data Mahasiswa\n"
             << "3. Mencari Data Mahasiswa\n"
             << "4. Memperbarui Data IPK Mahasiswa\n"
             << "5. Menghapus Data Mahasiswa\n"
             << "6. Keluar\n"
             << "Pilih menu: ";
        cin >> pil;
        cin.ignore();  // Menangani karakter newline setelah cin >>

        switch (pil) {
            case 1: tambahmhs(); break;
            case 2: tampilkanmhs(); break;
            case 3: {
                int pilc;
                cout << "1. Cari dengan NIM\n"
                     << "2. Cari berdasarkan Jurusan\n"
                     << "Pilih: ";
                cin >> pilc;
                cin.ignore();
                (pilc == 1) ? carimhsnim() : carimhsjur();
                break;
            }
            case 4: perbaruiIPK(); break;
            case 5: hapusMahasiswa(); break;
            case 6: cout << "Terima kasih!\n"; return 0;
            default: cout << "Pilihan tidak tersedia!\n";
        }
    } while (pil != 6);
}

// Fungsi quickSort
void quickSort(Data mhs[], int left, int right) {
    int i = left, j = right;
    Data pivot = mhs[(left + right) / 2];

    while (i <= j) {
        while (strcmp(mhs[i].nim, pivot.nim) < 0) i++;
        while (strcmp(mhs[j].nim, pivot.nim) > 0) j--;
        if (i <= j) {
            swap(mhs[i], mhs[j]);
            i++; j--;
        }
    }

    if (left < j) quickSort(mhs, left, j);
    if (i < right) quickSort(mhs, i, right);
}

void tambahmhs() {
    FILE *pfile = fopen("MahasiswaData.dat", "ab");
    if (!pfile) {
        cout << "Gagal membuka file!\n";
        return;
    }

    Data mhs;
    cin.ignore();
    cout << "Masukkan Nama          : "; cin.getline(mhs.nama, 50);
    cout << "Masukkan NIM           : "; cin.getline(mhs.nim, 10);
    cout << "Masukkan Jurusan       : "; cin.getline(mhs.jurusan, 50);
    cout << "Masukkan Tahun Masuk   : "; cin.getline(mhs.tahun, 5);
    mhs.ipk = 0.0;

    fwrite(&mhs, sizeof(Data), 1, pfile);
    fclose(pfile);
    cout << "Data berhasil ditambahkan!\n";
}

void tampilkanmhs() {
    FILE *pfile = fopen("MahasiswaData.dat", "rb");
    if (!pfile) {
        cout << "Belum ada data mahasiswa!" << endl;
        return;
    }

    fseek(pfile, 0, SEEK_END);
    int jumlah = ftell(pfile) / sizeof(Data);
    rewind(pfile);

    if (jumlah == 0) {
        cout << "Data mahasiswa masih kosong!" << endl;
        fclose(pfile);
        return;
    }

    Data *mhs = new Data[jumlah];
    fread(mhs, sizeof(Data), jumlah, pfile);
    fclose(pfile);

    cout << "\nData sebelum sorting:\n";
    for (int i = 0; i < jumlah; i++) {
        cout << mhs[i].nim << " - " << mhs[i].nama << endl;
    }

    quickSort(mhs, 0, jumlah - 1);

    cout << "\nData setelah sorting:\n";
    for (int i = 0; i < jumlah; i++) {
        cout << "----------------------\n";
        cout << "Nama     : " << (strlen(mhs[i].nama) > 0 ? mhs[i].nama : "Tidak ada") << endl;
        cout << "NIM      : " << (strlen(mhs[i].nim) > 0 ? mhs[i].nim : "Tidak ada") << endl;
        cout << "Jurusan  : " << (strlen(mhs[i].jurusan) > 0 ? mhs[i].jurusan : "Tidak ada") << endl;
        cout << "Tahun    : " << (strlen(mhs[i].tahun) > 0 ? mhs[i].tahun : "Tidak ada") << endl;
        cout << "IPK      : " << mhs[i].ipk << endl;
    }

    delete[] mhs;
    system("pause");
}



void carimhsnim() {
    FILE *pfile = fopen("MahasiswaData.dat", "rb");
    if (!pfile) {
        cout << "Belum ada data mahasiswa!\n";
        return;
    }

    fseek(pfile, 0, SEEK_END);
    int jumlah = ftell(pfile) / sizeof(Data);
    rewind(pfile);

    Data* mhs = new Data[jumlah];
    fread(mhs, sizeof(Data), jumlah, pfile);
    fclose(pfile);

    quickSort(mhs, 0, jumlah - 1);

    char nim[10];
    cout << "Masukkan NIM: "; cin.getline(nim, 10);
    bool found = false;

    for (int i = 0; i < jumlah; i++) {
        if (strcmp(mhs[i].nim, nim) == 0) {
            cout << "Nama     : " << mhs[i].nama << "\n"
                 << "NIM      : " << mhs[i].nim << "\n"
                 << "Jurusan  : " << mhs[i].jurusan << "\n"
                 << "Tahun    : " << mhs[i].tahun << "\n"
                 << "IPK      : " << mhs[i].ipk << "\n"
                 << "----------------------\n";
            found = true;
            break;
        }
    }

    if (!found) cout << "Mahasiswa tidak ditemukan!\n";
    delete[] mhs;
}

void carimhsjur() {
    FILE *pfile = fopen("MahasiswaData.dat", "rb");
    if (!pfile) {
        cout << "Belum ada data mahasiswa!" << endl;
        return;
    }

    Data mhs;
    char jurusan[50];
    cin.ignore();
    cout << "Masukkan jurusan mahasiswa yang dicari: ";
    cin.getline(jurusan, 50);

    bool ketemu = false;
    while (fread(&mhs, sizeof(Data), 1, pfile)) {
        if (strcmp(mhs.jurusan, jurusan) == 0) {
            cout << "----------------------\n";
            cout << "Nama           : " << mhs.nama << endl;
            cout << "NIM            : " << mhs.nim << endl;
            cout << "Jurusan        : " << mhs.jurusan << endl;
            cout << "Tahun Masuk    : " << mhs.tahun << endl;
            cout << "IPK            : " << mhs.ipk << endl;
            ketemu = true;
        }
    }

    fclose(pfile);
    if (!ketemu) {
        cout << "Mahasiswa dengan jurusan " << jurusan << " tidak ditemukan!" << endl;
    }
    system("pause");
}

void perbaruiIPK() {
    FILE *pfile = fopen("MahasiswaData.dat", "rb+"); 
    if (!pfile) {
        cout << "Belum ada data mahasiswa!" << endl;
        return;
    }

    char nim[10];
    cout << "Masukkan NIM mahasiswa yang ingin diperbarui IPK-nya: ";
    cin >> nim;

    Data mhs;
    bool ketemu = false;

    while (fread(&mhs, sizeof(Data), 1, pfile)) {
        if (strcmp(mhs.nim, nim) == 0) {
            ketemu = true;
            cout << "Nama     : " << mhs.nama << endl;
            cout << "NIM      : " << mhs.nim << endl;
            cout << "Jurusan  : " << mhs.jurusan << endl;
            cout << "Tahun    : " << mhs.tahun << endl;
            cout << "IPK Lama : " << mhs.ipk << endl;

            float ipkBaru;
            do {
                cout << "Masukkan IPK baru (0.0 - 4.0): ";
                cin >> ipkBaru;
                if (ipkBaru < 0.0 || ipkBaru > 4.0) {
                    cout << "Error! IPK harus dalam rentang 0.0 - 4.0." << endl;
                }
            } while (ipkBaru < 0.0 || ipkBaru > 4.0);

            // Perbarui IPK dalam struktur
            mhs.ipk = ipkBaru;

            // Kembalikan posisi file pointer untuk menulis ulang data
            fseek(pfile, sizeof(Data), SEEK_CUR);
            fwrite(&mhs, sizeof(Data), 1, pfile);
            cout << "IPK mahasiswa dengan NIM " << nim << " berhasil diperbarui!" << endl;
            break;
        }
    }

    fclose(pfile);
    if (!ketemu) {
        cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan!" << endl;
    }
    system("pause");
} 

void hapusMahasiswa() {
    FILE *pfile = fopen("MahasiswaData.dat", "rb");
    if (!pfile) {
        cout << "Belum ada data mahasiswa!\n";
        return;
    }

    FILE *tempFile = fopen("Temp.dat", "wb");
    char nim[10];
    cout << "Masukkan NIM: ";
    cin.getline(nim, 10);
    Data mhs;
    bool ketemu = false;

    while (fread(&mhs, sizeof(Data), 1, pfile)) {
        if (strcmp(mhs.nim, nim) != 0)
            fwrite(&mhs, sizeof(Data), 1, tempFile);
        else ketemu = true;
    }

    fclose(pfile);
    fclose(tempFile);
    remove("MahasiswaData.dat");
    rename("Temp.dat", "MahasiswaData.dat");

    if (!ketemu) cout << "Mahasiswa tidak ditemukan!\n";
}
