
#include <stdio.h>
#include <string.h>

#define MAX_VE 100

int main() {
    struct VeMayBay {
        char maVe[16];
        char tenHanhKhach[51];
        char hangVe[21];
        float canNangHanhLy;
        double cuocHanhLy;
    };

    struct VeMayBay danhSachVe[MAX_VE];
    int soLuong, i;
    int viTriNangNhat = 0;
    int viTriTimThay = -1;
    char maCanTim[16];
    double tongCuoc = 0;

    printf("Nhap so luong ve may bay: ");
    scanf("%d", &soLuong);
    while (getchar() != '\n');

    if (soLuong < 1 || soLuong > MAX_VE) {
        printf("So luong ve khong hop le!\n");
        return 0;
    }

    for (i = 0; i < soLuong; i++) {
        printf("\n--- Nhap thong tin ve thu %d ---\n", i + 1);
        printf("Ma ve PNR: ");
        scanf("%15s", danhSachVe[i].maVe);
        while (getchar() != '\n');

        printf("Ho ten hanh khach: ");
        fgets(danhSachVe[i].tenHanhKhach, sizeof(danhSachVe[i].tenHanhKhach), stdin);
        danhSachVe[i].tenHanhKhach[ strcspn(danhSachVe[i].tenHanhKhach, "\n")] = '\0';

        printf("Hang ve (Business/Deluxe/Eco): ");
        scanf("%20s", danhSachVe[i].hangVe);
        while (getchar() != '\n');

        do {
            printf("Khoi luong hanh ly (kg): ");
            scanf("%f", &danhSachVe[i].canNangHanhLy);
            while (getchar() != '\n');

            if (danhSachVe[i].canNangHanhLy < 0) {
                printf("Can nang khong duoc am! Nhap lai.\n");
            }
        } while (danhSachVe[i].canNangHanhLy < 0);

        if (strcmp(danhSachVe[i].hangVe, "Business") == 0) {
            if (danhSachVe[i].canNangHanhLy <= 20) { danhSachVe[i].cuocHanhLy = 0;
            } else {
                danhSachVe[i].cuocHanhLy = (danhSachVe[i].canNangHanhLy - 20) * 50000;
            }
        } else if (strcmp(danhSachVe[i].hangVe, "Eco") == 0 || strcmp(danhSachVe[i].hangVe, "Deluxe") == 0) {
            danhSachVe[i].cuocHanhLy = danhSachVe[i].canNangHanhLy * 50000;
        } else {
            printf("Hang ve khong hop le!\n");
            return 0;
        }
    }

    for (i = 0; i < soLuong; i++) {
        tongCuoc += danhSachVe[i].cuocHanhLy;

        if (danhSachVe[i].canNangHanhLy > danhSachVe[viTriNangNhat].canNangHanhLy) {
            viTriNangNhat = i;
        }
    }
    printf("\n================ DANH SACH VE MAY BAY ================\n");
    printf("%-5s %-12s %-25s %-12s %12s %15s\n",
           "STT", "MA VE", "HO TEN HANH KHACH", "HANG VE",
           "HANH LY(KG)", "CUOC(VND)");
    printf("-------------------------------------------------------------------------------\n");

    for (i = 0; i < soLuong; i++) {
        printf("%-5d %-12s %-25s %-12s %12.1f %15.0f\n", i + 1, danhSachVe[i].maVe, danhSachVe[i].tenHanhKhach, danhSachVe[i].hangVe, danhSachVe[i].canNangHanhLy, danhSachVe[i].cuocHanhLy);
    }

    printf("-------------------------------------------------------------------------------\n");
    printf("Tong cuoc hanh ly toan chuyen: %.0f VND\n", tongCuoc);
    printf("Ve co hanh ly nang nhat: %s - %s (%.1f kg)\n", danhSachVe[viTriNangNhat].maVe, danhSachVe[viTriNangNhat].tenHanhKhach, danhSachVe[viTriNangNhat].canNangHanhLy);

    printf("\n--- CAP NHAT THONG TIN HANH LY ---\n");
    printf("Nhap ma ve PNR can cap nhat: ");
    scanf("%15s", maCanTim);
    while (getchar() != '\n');

    for (i = 0; i < soLuong; i++) {
        if (strcmp(danhSachVe[i].maVe, maCanTim) == 0) {
            viTriTimThay = i;
            break;
        }
    }
    if (viTriTimThay == -1) {
        printf("Khong tim thay ma ve PNR nay trong he thong!\n");
    } else {
        printf("Tim thay hanh khach: %s\n",
               danhSachVe[viTriTimThay].tenHanhKhach);

        do {
            printf("Nhap can nang hanh ly moi (kg): ");
            scanf("%f", &danhSachVe[viTriTimThay].canNangHanhLy);
            while (getchar() != '\n');

            if (danhSachVe[viTriTimThay].canNangHanhLy < 0) {
                printf("Can nang khong duoc am! Nhap lai.\n");
            }
        } while (danhSachVe[viTriTimThay].canNangHanhLy < 0);

        if (strcmp(danhSachVe[viTriTimThay].hangVe, "Business") == 0) {
            if (danhSachVe[viTriTimThay].canNangHanhLy <= 20) {
                danhSachVe[viTriTimThay].cuocHanhLy = 0;
            } else {
                danhSachVe[viTriTimThay].cuocHanhLy = (danhSachVe[viTriTimThay].canNangHanhLy - 20) * 50000;
            }
        } else {
            danhSachVe[viTriTimThay].cuocHanhLy = danhSachVe[viTriTimThay].canNangHanhLy * 50000;
        }

        printf("Cap nhat thanh cong! Cuoc moi: %.0f VND\n", danhSachVe[viTriTimThay].cuocHanhLy);

        tongCuoc = 0;
        viTriNangNhat = 0;

        for (i = 0; i < soLuong; i++) {
            tongCuoc += danhSachVe[i].cuocHanhLy;

            if (danhSachVe[i].canNangHanhLy > danhSachVe[viTriNangNhat].canNangHanhLy) {
                viTriNangNhat = i;
            }
        }
        printf("\n=========== DANH SACH VE SAU CAP NHAT ===========\n");
        printf("%-5s %-12s %-25s %-12s %12s %15s\n",
               "STT", "MA VE", "HO TEN HANH KHACH", "HANG VE",
               "HANH LY(KG)", "CUOC(VND)");
        printf("-------------------------------------------------------------------------------\n");
        for (i = 0; i < soLuong; i++) {
            printf("%-5d %-12s %-25s %-12s %12.1f %15.0f\n", i + 1, danhSachVe[i].maVe, danhSachVe[i].tenHanhKhach, danhSachVe[i].hangVe, danhSachVe[i].canNangHanhLy, danhSachVe[i].cuocHanhLy);
        }

        printf("-------------------------------------------------------------------------------\n");
        printf("Tong cuoc hanh ly toan chuyen: %.0f VND\n", tongCuoc);
        printf("Ve co hanh ly nang nhat: %s - %s (%.1f kg)\n", danhSachVe[viTriNangNhat].maVe, danhSachVe[viTriNangNhat].tenHanhKhach, danhSachVe[viTriNangNhat].canNangHanhLy);
    }

    return 0;
}