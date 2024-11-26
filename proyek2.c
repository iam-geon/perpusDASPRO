#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct History {
    char buku[50];     
    char aksi[10];     
    char peminjam[50]; 
};

struct Reservasi {
    char buku[50];
    char namaPeminjam[50];
};

char *buku[100] = {"Pemrograman C", "Algoritma Bahasa", 
                "Jaringan Komputer", "Sistem Operasi"};
int stok[100] = {5, 3, 2, 4}; 
int jumlahBuku = 4; 

struct History history[100];
int historyCount = 0;

struct Reservasi daftarReservasi[100]; 
int jumlahReservasi = 0;

int borrowed[100] = {0};  

void lihatBuku() {
    printf("\n ---DAFTAR BUKU ---\n");
    for (int i = 0; i < jumlahBuku; i++) {
        printf("%d. %s (Stok: %d)\n", i + 1, buku[i], stok[i]);
    }
}

void pinjamBuku() {
    int pilihan;
    char peminjam[50];
    lihatBuku();

    printf("\nMasukkan nomor buku yang ingin dipinjam: ");
    scanf("%d", &pilihan);
    pilihan--;

    if (pilihan >= 0 && pilihan < jumlahBuku) {
        if (stok[pilihan] > 0) {
            printf("Masukkan nama peminjam: ");
            getchar();
            fgets(peminjam, sizeof(peminjam), stdin);
            peminjam[strcspn(peminjam, "\n")] = '\0';

            stok[pilihan]--;
            borrowed[pilihan] = 1;
            printf("Anda berhasil meminjam buku '%s'.\n", buku[pilihan]);

            strcpy(history[historyCount].buku, buku[pilihan]);
            strcpy(history[historyCount].aksi, "Pinjam");
            strcpy(history[historyCount].peminjam, peminjam);
            historyCount++;
        } else {
            printf("Maaf, buku '%s' sedang habis.\n", buku[pilihan]);
        }
    } else {
        printf("Pilihan buku tidak valid.\n");
    }
}

void kembalikanBuku() {
    int pilihan;
    char peminjam[50];
    lihatBuku();

    printf("\nMasukkan nomor buku yang ingin dikembalikan: ");
    scanf("%d", &pilihan);
    pilihan--;

    if (pilihan >= 0 && pilihan < jumlahBuku) {
        if (borrowed[pilihan] == 1) {
            printf("Masukkan nama peminjam yang mengembalikan buku: ");
            getchar();
            fgets(peminjam, sizeof(peminjam), stdin);
            peminjam[strcspn(peminjam, "\n")] = '\0';

            stok[pilihan]++;
            borrowed[pilihan] = 0;
            printf("Anda berhasil mengembalikan buku '%s'.\n", buku[pilihan]);

            strcpy(history[historyCount].buku, buku[pilihan]);
            strcpy(history[historyCount].aksi, "Kembali");
            strcpy(history[historyCount].peminjam, peminjam);
            historyCount++;
        } else {
            printf("Buku '%s' belum dipinjam.\n", buku[pilihan]);
        }
    } else {
        printf("Pilihan buku tidak valid.\n");
    }
}

void tambahBuku() {
    if (jumlahBuku >= 100) {
        printf("Tidak dapat menambah lebih banyak buku.\n");
        return;
    }

    char judulBaru[50];
    int stokBaru;

    getchar();
    printf("Masukkan judul buku baru: ");
    fgets(judulBaru, sizeof(judulBaru), stdin);
    judulBaru[strcspn(judulBaru, "\n")] = '\0';

    printf("Masukkan jumlah stok: ");
    scanf("%d", &stokBaru);

    buku[jumlahBuku] = strdup(judulBaru);
    stok[jumlahBuku] = stokBaru;
    jumlahBuku++;

    printf("Buku '%s' berhasil ditambahkan dengan stok %d.\n", judulBaru, stokBaru);
}

void lihatHistory() {
    printf("\n ---RIWAYAT PEMINJAMAN---\n");
    if (historyCount == 0) {
        printf("Tidak ada riwayat peminjaman atau pengembalian.\n");
    } else {
        for (int i = 0; i < historyCount; i++) {
            printf("%d. Buku: %s \nAksi: %s\nPeminjam: %s\n", 
                   i + 1, history[i].buku, history[i].aksi, history[i].peminjam);
        }
    }
}

void reservasiBuku() {
    int pilihan;
    char namaPeminjam[50];

    lihatBuku();
    printf("\nMasukkan nomor buku yang ingin Anda reservasi: ");
    scanf("%d", &pilihan);
    pilihan--;

    if (pilihan >= 0 && pilihan < jumlahBuku) {
        if (stok[pilihan] == 0) {
            printf("Masukkan nama Anda untuk reservasi: ");
            getchar();
            fgets(namaPeminjam, sizeof(namaPeminjam), stdin);
            namaPeminjam[strcspn(namaPeminjam, "\n")] = '\0';

            strcpy(daftarReservasi[jumlahReservasi].buku, buku[pilihan]);
            strcpy(daftarReservasi[jumlahReservasi].namaPeminjam, namaPeminjam);
            jumlahReservasi++;

            printf("Reservasi untuk buku '%s' berhasil.\n", buku[pilihan]);
        } else {
            printf("Buku '%s' masih tersedia.\n", buku[pilihan]);
        }
    } else {
        printf("Pilihan tidak valid.\n");
    }
}

void lihatReservasi() {
    printf("\n ---DAFTAR RESERVASI---\n");
    if (jumlahReservasi == 0) {
        printf("Tidak ada reservasi.\n");
    } else {
        for (int i = 0; i < jumlahReservasi; i++) {
            printf("%d. Buku: %s \nNama Peminjam: %s\n", 
                   i + 1, daftarReservasi[i].buku, daftarReservasi[i].namaPeminjam);
        }
    }
}

int login() {
    char id[20], password[20];
    int percobaan = 0;

    while (percobaan < 3) {
        printf("\n=== LOGIN ===\n");
        printf("Masukkan ID: ");
        scanf("%s", id);
        printf("Masukkan Password: ");
        scanf("%s", password);

        if (strcmp(id, "admin") == 0 && strcmp(password, "1234") == 0) {
            printf("Login berhasil!\n");
            return 1;
        } else {
            printf("ID atau Password salah.\n");
            percobaan++;
            if (percobaan < 3) {
                printf("Percobaan tersisa: %d\n", 3 - percobaan);
            }
        }
    }

    printf("Anda telah gagal login 3 kali. Program keluar.\n");
    return 0;
}

int main() {
    int pilihan;

    if (!login()) {
        return 0; 
    }

    do {
        printf("\n###SELAMAT DATANG DI PERPUSTAKAAN MATAHARI###");
        printf("\n=== MENU PERPUSTAKAAN ===\n");
        printf("1. Lihat Buku\n");
        printf("2. Pinjam Buku\n");
        printf("3. Kembalikan Buku\n");
        printf("4. Tambah Buku\n");
        printf("5. Lihat Riwayat\n");
        printf("6. Reservasi Buku\n");
        printf("7. Lihat Reservasi\n");
        printf("8. Keluar\n");

        printf("Masukkan pilihan Anda: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                lihatBuku();
                break;
            case 2:
                pinjamBuku();
                break;
            case 3:
                kembalikanBuku();
                break;
            case 4:
                tambahBuku();
                break;
            case 5:
                lihatHistory();
                break;
            case 6:
                reservasiBuku();
                break;
            case 7:
                lihatReservasi();
                break;
            case 8:
                printf("\nTerima kasih telah menggunakan Perpustakaan Matahari.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 8);

    return 0;
}
