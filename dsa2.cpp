#include <bits/stdc++.h>
using namespace std;

// Cấu trúc thông tin học phần / sinh viên
struct HocPhan {
    char MaHP[10];      // Mã học phần
    char TenHP[50];     // Tên học phần
    int SoTC;           // Số tín chỉ
};

// Node của danh sách liên kết
struct Node {
    HocPhan infor;
    Node* next;
};

typedef Node* Tro;      // Tro = con trỏ Node*

// 1. Khởi tạo danh sách rỗng
void KhoiTao(Tro &L) {
    L = NULL;
}

// 2. Nhập thông tin 1 học phần
void NhapHP(HocPhan &hp) {
    cout << "Nhap ma hoc phan: ";
    fflush(stdin); gets(hp.MaHP);

    cout << "Nhap ten hoc phan: ";
    fflush(stdin); gets(hp.TenHP);

    cout << "Nhap so tin chi: ";
    cin >> hp.SoTC;
}

// 3. Nhập danh sách (nhập đến khi muốn dừng hoặc nhập số lượng)
void NhapDS(Tro &L) {
    KhoiTao(L);
    int n;
    cout << "Nhap so luong hoc phan: ";
    cin >> n;

    Tro P, Q;
    for(int i = 1; i <= n; i++) {
        HocPhan x;
        cout << "\nHoc phan thu " << i << ":\n";
        NhapHP(x);

        P = new Node;
        P->infor = x;
        P->next = NULL;

        if(L == NULL) {
            L = P;
        } else {
            Q->next = P;
        }
        Q = P;
    }
}

// 4. Hiển thị danh sách
void HienThi(Tro L) {
    if(L == NULL) {
        cout << "Danh sach rong!\n";
        return;
    }

    cout << left;
    cout << setw(5)  << "STT"
         << setw(12) << "MaHP"
         << setw(35) << "TenHP"
         << setw(10) << "SoTC" << endl;

    int stt = 1;
    Tro Q = L;
    while(Q != NULL) {
        HocPhan x = Q->infor;
        cout << setw(5)  << stt++
             << setw(12) << x.MaHP
             << setw(35) << x.TenHP
             << setw(10) << x.SoTC << endl;
        Q = Q->next;
    }
    cout << endl;
}

// 5. Thêm vào đầu danh sách
void ChenVaoDau(Tro &L, HocPhan x) {
    Tro P = new Node;
    P->infor = x;
    P->next = L;
    L = P;
}

// 6. Thêm vào cuối danh sách
void ChenVaoCuoi(Tro &L, HocPhan x) {
    Tro P = new Node;
    P->infor = x;
    P->next = NULL;

    if(L == NULL) {
        L = P;
        return;
    }

    Tro Q = L;
    while(Q->next != NULL)
        Q = Q->next;
    Q->next = P;
}

// 7. Chèn vào vị trí thứ k (1-based)
bool ChenVaoViTriK(Tro &L, HocPhan x, int k) {
    if(k <= 0) return false;

    Tro P = new Node;
    P->infor = x;
    P->next = NULL;

    if(k == 1) {
        P->next = L;
        L = P;
        return true;
    }

    Tro Q = L;
    int dem = 1;
    while(Q != NULL && dem < k-1) {
        Q = Q->next;
        dem++;
    }

    if(Q == NULL) {
        delete P;
        return false;   // vị trí không hợp lệ
    }

    P->next = Q->next;
    Q->next = P;
    return true;
}

// 8. Xóa node đầu danh sách
bool XoaDau(Tro &L) {
    if(L == NULL) return false;
    Tro P = L;
    L = L->next;
    delete P;
    return true;
}

// 9. Xóa node cuối danh sách
bool XoaCuoi(Tro &L) {
    if(L == NULL) return false;
    if(L->next == NULL) {
        delete L;
        L = NULL;
        return true;
    }

    Tro Q = L;
    while(Q->next->next != NULL)
        Q = Q->next;

    delete Q->next;
    Q->next = NULL;
    return true;
}

// 10. Xóa node tại vị trí k (1-based)
bool XoaViTriK(Tro &L, int k) {
    if(L == NULL || k <= 0) return false;

    if(k == 1) {
        return XoaDau(L);
    }

    Tro Q = L;
    int dem = 1;
    while(Q->next != NULL && dem < k-1) {
        Q = Q->next;
        dem++;
    }

    if(Q->next == NULL) return false;

    Tro P = Q->next;
    Q->next = P->next;
    delete P;
    return true;
}

// 11. Tìm học phần theo mã (trả về con trỏ đến node)
Tro TimTheoMa(Tro L, char ma[]) {
    Tro Q = L;
    while(Q != NULL) {
        if(strcmp(Q->infor.MaHP, ma) == 0)
            return Q;
        Q = Q->next;
    }
    return NULL;
}

// 12. Sửa thông tin học phần theo mã
bool SuaTheoMa(Tro L, char ma[]) {
    Tro P = TimTheoMa(L, ma);
    if(P == NULL) return false;

    cout << "Thong tin cu:\n";
    cout << "Ma: " << P->infor.MaHP << " - " 
         << P->infor.TenHP << " - " << P->infor.SoTC << " TC\n";

    cout << "\nNhap thong tin moi:\n";
    NhapHP(P->infor);
    return true;
}

// 13. Xóa tất cả học phần có số tín chỉ = x
void XoaTheoSoTC(Tro &L, int sotc) {
    Tro Q = L;
    Tro prev = NULL;

    while(Q != NULL) {
        if(Q->infor.SoTC == sotc) {
            if(prev == NULL) {      // xóa đầu
                L = Q->next;
                delete Q;
                Q = L;
            } else {
                prev->next = Q->next;
                delete Q;
                Q = prev->next;
            }
        } else {
            prev = Q;
            Q = Q->next;
        }
    }
}

// 14. Tính tổng số tín chỉ
int TongSoTC(Tro L) {
    int tong = 0;
    Tro Q = L;
    while(Q != NULL) {
        tong += Q->infor.SoTC;
        Q = Q->next;
    }
    return tong;
}

// ================= MAIN =================
int main() {
    Tro L;
    KhoiTao(L);

    int chon;
    do {
        cout << "\n===== MENU DANH SACH LIEN KET =====\n";
        cout << "1. Nhap danh sach\n";
        cout << "2. Hien thi danh sach\n";
        cout << "3. Them vao dau\n";
        cout << "4. Them vao cuoi\n";
        cout << "5. Chen vao vi tri k\n";
        cout << "6. Xoa dau\n";
        cout << "7. Xoa cuoi\n";
        cout << "8. Xoa vi tri k\n";
        cout << "9. Tim va sua theo ma HP\n";
        cout << "10. Xoa tat ca hoc phan co SoTC = x\n";
        cout << "11. Tinh tong so tin chi\n";
        cout << "0. Thoat\n";
        cout << "Chon: "; cin >> chon;

        switch(chon) {
            case 1: {
                NhapDS(L);
                break;
            }
            case 2: {
                HienThi(L);
                break;
            }
            case 3: {
                HocPhan x;
                cout << "Nhap hoc phan can them vao dau:\n";
                NhapHP(x);
                ChenVaoDau(L, x);
                cout << "Da them vao dau!\n";
                break;
            }
            case 4: {
                HocPhan x;
                cout << "Nhap hoc phan can them vao cuoi:\n";
                NhapHP(x);
                ChenVaoCuoi(L, x);
                cout << "Da them vao cuoi!\n";
                break;
            }
            case 5: {
                HocPhan x;
                int k;
                cout << "Nhap hoc phan: \n"; NhapHP(x);
                cout << "Nhap vi tri can chen (1-based): "; cin >> k;
                if(ChenVaoViTriK(L, x, k))
                    cout << "Chen thanh cong!\n";
                else
                    cout << "Vi tri khong hop le!\n";
                break;
            }
            case 6: {
                if(XoaDau(L)) cout << "Da xoa dau!\n";
                else cout << "Danh sach rong!\n";
                break;
            }
            case 7: {
                if(XoaCuoi(L)) cout << "Da xoa cuoi!\n";
                else cout << "Danh sach rong hoac chi co 1 phan tu!\n";
                break;
            }
            case 8: {
                int k;
                cout << "Nhap vi tri can xoa: "; cin >> k;
                if(XoaViTriK(L, k))
                    cout << "Da xoa!\n";
                else
                    cout << "Vi tri khong hop le!\n";
                break;
            }
            case 9: {
                char ma[10];
                cout << "Nhap ma HP can sua: "; fflush(stdin); gets(ma);
                if(SuaTheoMa(L, ma))
                    cout << "Da sua thanh cong!\n";
                else
                    cout << "Khong tim thay ma HP!\n";
                break;
            }
            case 10: {
                int tc;
                cout << "Xoa tat ca hoc phan co so TC = "; cin >> tc;
                XoaTheoSoTC(L, tc);
                cout << "Da xoa xong!\n";
                break;
            }
            case 11: {
                cout << "Tong so tin chi: " << TongSoTC(L) << endl;
                break;
            }
            case 0:
                cout << "Tam biet!\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while(chon != 0);

    // Giải phóng bộ nhớ (tốt nhất nên có)
    while(L != NULL) {
        Tro tam = L;
        L = L->next;
        delete tam;
    }

    return 0;
}