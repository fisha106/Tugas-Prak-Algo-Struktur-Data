#include <iostream>
#include <string>
using namespace std;

struct Video {
    string judul;
    int durasi;
    string status;
    Video* next;
};

struct Playlist {
    Video* head;
    Video* tail;
};

struct Riwayat {
    Video* head;
    Video* tail;
};

Video* daftarVideo = NULL;
Playlist playlist = {NULL, NULL};
Riwayat riwayat = {NULL, NULL};

// Fungsi untuk menambahkan video ke linked list
void tambahVideoKeDaftar(Video* video) {
    if (daftarVideo == NULL) {
        daftarVideo = video;
    } else {
        Video* current = daftarVideo;
        Video* prev = NULL;
        
        // Insert secara terurut berdasarkan judul (ascending)
        while (current != NULL && current->judul < video->judul) {
            prev = current;
            current = current->next;
        }
        
        if (prev == NULL) {
            video->next = daftarVideo;
            daftarVideo = video;
        } else {
            prev->next = video;
            video->next = current;
        }
    }
}

// Fungsi untuk menambahkan video ke akhir linked list
void tambahVideoAkhir(Video** head, Video** tail, Video* video) {
    video->next = NULL;
    if (*head == NULL) {
        *head = video;
        *tail = video;
    } else {
        (*tail)->next = video;
        *tail = video;
    }
}

// Fungsi untuk menghapus video dari linked list
Video* hapusVideoDariDaftar(Video* head, string judul) {
    Video* current = head;
    Video* prev = NULL;
    
    while (current != NULL && current->judul != judul) {
        prev = current;
        current = current->next;
    }
    
    if (current == NULL) return head;
    
    if (prev == NULL) {
        head = current->next;
    } else {
        prev->next = current->next;
    }
    
    return head;
}

// Fungsi untuk mengecek apakah video ada di linked list
bool cekVideoAda(Video* head, string judul) {
    Video* current = head;
    while (current != NULL) {
        if (current->judul == judul) return true;
        current = current->next;
    }
    return false;
}

// Fungsi untuk menampilkan semua video dalam linked list
void tampilkanDaftar(Video* head) {
    Video* current = head;
    while (current != NULL) {
        cout << "- " << current->judul << " (" << current->durasi 
             << " menit) - Status: " << current->status << endl;
        current = current->next;
    }
}

void tambahVideo() {
    char lanjut;
    do {
        Video* videoBaru = new Video();
        cout << "\nMasukkan judul video: ";
        cin.ignore();
        getline(cin, videoBaru->judul);
        
        if (cekVideoAda(daftarVideo, videoBaru->judul)) {
            cout << "Video dengan judul tersebut sudah ada!" << endl;
            delete videoBaru;
        } else {
            cout << "Masukkan durasi video (menit): ";
            cin >> videoBaru->durasi;
            videoBaru->status = "tersedia";
            videoBaru->next = NULL;
            
            tambahVideoKeDaftar(videoBaru);
            cout << "Video berhasil ditambahkan!" << endl;
        }
        
        cout << "Tambah video lagi? (y/t): ";
        cin >> lanjut;
    } while (lanjut == 'y' || lanjut == 'Y');
}

void tampilkanDaftarVideo() {
    if (daftarVideo == NULL) {
        cout << "\nDaftar video kosong!" << endl;
        return;
    }
    
    cout << "\nDaftar Video:" << endl;
    tampilkanDaftar(daftarVideo);
}

void menuCariVideo() {
    if (daftarVideo == NULL) {
        cout << "\nDaftar video kosong!" << endl;
        return;
    }
    
    char pilihan;
    cout << "\nApakah Anda ingin mencari video (y/t)? ";
    cin >> pilihan;
    
    if (pilihan == 'y' || pilihan == 'Y') {
        string cariJudul;
        cout << "Masukkan judul video yang dicari: ";
        cin.ignore();
        getline(cin, cariJudul);
        
        bool ditemukan = false;
        Video* current = daftarVideo;
        while (current != NULL) {
            if (current->judul.find(cariJudul) != string::npos) {
                cout << "- " << current->judul << " (" << current->durasi 
                     << " menit) - Status: " << current->status << endl;
                ditemukan = true;
            }
            current = current->next;
        }
        
        if (!ditemukan) {
            cout << "Video tidak ditemukan!" << endl;
        }
    }
}

void tambahKePlaylist() {
   if (daftarVideo == nullptr) {
        cout << "\nDaftar video kosong!" << endl;
        return;
    }

    char lanjut;
    
    do {
        cout << "\nDaftar Video Tersedia:" << endl;
        tampilkanDaftar(daftarVideo);
        
        string pilihanJudul;
        bool inputValid = false;
        
        do {
            cout << "\nMasukkan judul video yang ingin ditambahkan ke playlist: ";
            cin.ignore();
            getline(cin, pilihanJudul);
            
            // Cek apakah video sudah ada di playlist
            Video* cekPlaylist = playlist.head;
            bool sudahDiPlaylist = false;
            while (cekPlaylist != nullptr) {
                if (cekPlaylist->judul == pilihanJudul) {
                    sudahDiPlaylist = true;
                    break;
                }
                cekPlaylist = cekPlaylist->next;
            }
            
            if (sudahDiPlaylist) {
                cout << "\nVideo '" << pilihanJudul << "' sudah ada di playlist!" << endl;
                inputValid = true; // Keluar dari loop input
                continue;
            }
            
            Video* current = daftarVideo;
            bool ditemukan = false;
            
            while (current != nullptr) {
                if (current->judul == pilihanJudul) {
                    ditemukan = true;
                    if (current->status == "tersedia") {
                        // Buat salinan video untuk playlist
                        Video* videoPlaylist = new Video();
                        *videoPlaylist = *current;
                        videoPlaylist->next = nullptr;
                        
                        tambahVideoAkhir(&playlist.head, &playlist.tail, videoPlaylist);
                        
                        // Update status di daftar video
                        current->status = (playlist.head == playlist.tail) ? 
                                        "sedang diputar" : "dalam antrean";
                        
                        cout << "\nVideo '" << current->judul << "' berhasil ditambahkan ke playlist!" << endl;
                        inputValid = true;
                    } else {
                        cout << "\nVideo tidak tersedia untuk ditambahkan ke playlist!" << endl;
                        inputValid = true;
                    }
                    break;
                }
                current = current->next;
            }
            
            if (!ditemukan) {
                cout << "\nVideo tidak ditemukan! Silakan coba lagi." << endl;
            }
            
        } while (!inputValid);
        
        cout << "\nTambahkan video lagi ke playlist? (y/t): ";
        cin >> lanjut;
    } while (lanjut == 'y' || lanjut == 'Y');
}

void tontonVideo() {
    if (playlist.head == NULL) {
        cout << "\nTidak ada video dalam playlist!" << endl;
        return;
    }
    
    Video* videoDitonton = playlist.head;
    cout << "\nMenonton video: " << videoDitonton->judul 
         << " (" << videoDitonton->durasi << " menit)" << endl;
    
    // Hapus dari playlist
    playlist.head = playlist.head->next;
    if (playlist.head == NULL) {
        playlist.tail = NULL;
    }
    
    // Update status di daftar video
    Video* current = daftarVideo;
    while (current != NULL) {
        if (current->judul == videoDitonton->judul) {
            current->status = "tersedia";
            break;
        }
        current = current->next;
    }
    
    // Tambahkan ke riwayat (sebagai salinan)
    Video* videoRiwayat = new Video();
    *videoRiwayat = *videoDitonton;
    videoRiwayat->next = NULL;
    tambahVideoAkhir(&riwayat.head, &riwayat.tail, videoRiwayat);
    
    // Update video berikutnya di playlist (jika ada)
    if (playlist.head != NULL) {
        current = daftarVideo;
        while (current != NULL) {
            if (current->judul == playlist.head->judul) {
                current->status = "sedang diputar";
                break;
            }
            current = current->next;
        }
    }
    
    delete videoDitonton;
}

void tampilkanRiwayat() {
    if (riwayat.head == NULL) {
        cout << "\nRiwayat tontonan kosong!" << endl;
        return;
    }
    
    cout << "\nRiwayat Tontonan:" << endl;
    Video* current = riwayat.head;
    while (current != NULL) {
        cout << "- " << current->judul << " (" << current->durasi << " menit)" << endl;
        current = current->next;
    }
}

void hapusVideo() {
    if (daftarVideo == NULL) {
        cout << "\nDaftar video kosong!" << endl;
        return;
    }
    
    tampilkanDaftarVideo();
    
    string pilihanJudul;
    cout << "\nMasukkan judul video yang ingin dihapus: ";
    cin.ignore();
    getline(cin, pilihanJudul);
    
    Video* current = daftarVideo;
    while (current != NULL) {
        if (current->judul == pilihanJudul) {
            if (current->status == "sedang diputar" || current->status == "dalam antrean") {
                char konfirmasi;
                cout << "Video yang ingin dihapus [" << current->status 
                     << "]. Yakin untuk tetap menghapus? (y/t) ";
                cin >> konfirmasi;
                
                if (konfirmasi != 'y' && konfirmasi != 'Y') {
                    return;
                }
            }
            
            // Hapus dari daftar video
            daftarVideo = hapusVideoDariDaftar(daftarVideo, pilihanJudul);
            
            // Hapus dari playlist jika ada
            Video* temp = playlist.head;
            while (temp != NULL) {
                if (temp->judul == pilihanJudul) {
                    playlist.head = hapusVideoDariDaftar(playlist.head, pilihanJudul);
                    break;
                }
                temp = temp->next;
            }
            
            cout << "\nVideo berhasil dihapus!" << endl;
            return;
        }
        current = current->next;
    }
    
    cout << "\nVideo tidak ditemukan!" << endl;
}

void tampilkanMenu() {
    cout << "\n=== IDLIX Tube ===" << endl;
    cout << "1. Tambah Video" << endl;
    cout << "2. Tampilkan Daftar Video" << endl;
    cout << "3. Tambahkan ke Playlist" << endl;
    cout << "4. Tonton Video" << endl;
    cout << "5. Riwayat Tontonan" << endl;
    cout << "6. Hapus Video" << endl;
    cout << "7. Keluar" << endl;
    cout << "Pilihan: ";
}

int main() {
    int pilihan;
    
    do {
        tampilkanMenu();
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                tambahVideo();
                break;
            case 2:
                tampilkanDaftarVideo();
                menuCariVideo();
                break;
            case 3:
                tambahKePlaylist();
                break;
            case 4:
                tontonVideo();
                break;
            case 5:
                tampilkanRiwayat();
                break;
            case 6:
                hapusVideo();
                break;
            case 7:
                cout << "\nTerima kasih telah menggunakan IDLIX Tube!" << endl;
                break;
            default:
                cout << "\nPilihan tidak valid!" << endl;
        }
    } while (pilihan != 7);
    
    // Bersihkan memory
    Video* current = daftarVideo;
    while (current != NULL) {
        Video* temp = current;
        current = current->next;
        delete temp;
    }
    
    current = playlist.head;
    while (current != NULL) {
        Video* temp = current;
        current = current->next;
        delete temp;
    }
    
    current = riwayat.head;
    while (current != NULL) {
        Video* temp = current;
        current = current->next;
        delete temp;
    }
    
    return 0;
}