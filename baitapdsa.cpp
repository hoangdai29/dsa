#include <iostream>
#include <string>
using namespace std;

struct SinhVien {
    string maSo;      // ma so (vd: SV01)
    string ten;       // ho ten
    float diemTB;     // diem trung binh
    int soMonTruot;   // so mon truot
};

struct Node {
    SinhVien infor;
    Node *next;
};

typedef Node* TRO;

// tao moi danh sach rong
void creat(TRO &L)
{
    L = NULL;
}

// kiem tra danh sach rong
int empty(TRO &L)
{
    return L == NULL;
}

// Nhap thong tin cho 1 sinh vien
void input(SinhVien &sv)
{
    cout << " - Nhap vao ma sinh vien: ";
    cin >> sv.maSo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << " - Nhap ho ten: ";
    getline(cin, sv.ten);
    cout << " - Nhap diem trung binh: ";
    cin >> sv.diemTB;
    cout << " - Nhap so mon truot: ";
    cin >> sv.soMonTruot;
}

// In thong tin sinh vien
void display(SinhVien sv)
{
    cout << fixed;
    cout << setw(8) << left << sv.maSo;
    cout << setw(25) << left << sv.ten;
    cout << setw(8) << right << fixed << setprecision(2) << sv.diemTB;
    cout << setw(12) << right << sv.soMonTruot;
    cout << endl;
}

// Chen 1 nut vao cuoi danh sach
void add(TRO &L, SinhVien elem)
{
    TRO P, Q;
    P = new Node;
    P->infor = elem;
    P->next = NULL;
    if (L == NULL)
    {
        L = P;
    }
    else
    {
        Q = L;
        while (Q->next != NULL)
            Q = Q->next;
        Q->next = P;
    }
}

// tao mot danh sach mau
void khoiTaoDanhSach(TRO &L)
{
    creat(L);
    SinhVien sv;

    sv.maSo = "SV01"; sv.ten = "Nguyen Van A"; sv.diemTB = 7.5f; sv.soMonTruot = 0; add(L, sv);
    sv.maSo = "SV02"; sv.ten = "Tran Thi B"; sv.diemTB = 4.2f; sv.soMonTruot = 2; add(L, sv);
    sv.maSo = "SV03"; sv.ten = "Le Van C"; sv.diemTB = 5.6f; sv.soMonTruot = 1; add(L, sv);
    sv.maSo = "SV04"; sv.ten = "Pham Thi D"; sv.diemTB = 8.1f; sv.soMonTruot = 0; add(L, sv);
    sv.maSo = "SV05"; sv.ten = "Hoang Van E"; sv.diemTB = 3.9f; sv.soMonTruot = 3; add(L, sv);
    sv.maSo = "SV06"; sv.ten = "Vu Thi F"; sv.diemTB = 6.0f; sv.soMonTruot = 0; add(L, sv);
}

// Nhap ds tu ban phim
void input_List(TRO &L)
{
    TRO P, Q = NULL;
    SinhVien elem;
    char tieptuc;

    creat(L);

    do
    {
        input(elem);
        P = new Node;
        P->infor = elem;
        P->next = NULL;
        if (L == NULL)
        {
            L = P;
        }
        else
        {
            Q->next = P;
        }

        Q = P;
        cout << "! Co nhap tiep khong? (C/K): ";
        cin >> tieptuc;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (toupper(tieptuc) == 'C');
}

// Hien thi danh sach
void showList(TRO L)
{
    TRO Q;
    if (!empty(L))
    {
        cout << fixed;
        cout << setw(8) << left << "Ma SV";
        cout << setw(25) << left << "Ho Ten";
        cout << setw(8) << right << "Diem";
        cout << setw(12) << right << "SoTruot";
        cout << endl;
        cout << string(60, '-') << endl;
        Q = L;
        while (Q != NULL)
        {
            display(Q->infor);
            Q = Q->next;
        }
    }
    else
    {
        cout << " !!! Danh sach rong !!!\n";
    }
}

// chieu dai danh sach
int lenghtList(TRO L)
{
    int count = 0;
    TRO Q = L;
    while (Q != NULL)
    {
        count++;
        Q = Q->next;
    }
    return count;
}

// tim kiem theo ma so (tra ve nut)
TRO search(TRO L, string ma)
{
    TRO Q = L;
    while (Q != NULL && Q->infor.maSo != ma)
        Q = Q->next;
    return Q; // tra ve NULL neu ko tim thay
}

// hien thi theo dieu kien diemTB > diemNguong
void hienThiTheoDieuKien(TRO L, float diemNguong)
{
    TRO Q = L;
    bool found = false;
    cout << "\nSinh vien co diemTB > " << diemNguong << ":\n";
    cout << setw(8) << left << "Ma SV" << setw(25) << left << "Ho Ten" << setw(8) << right << "Diem" << setw(12) << right << "SoTruot" << endl;
    cout << string(60, '-') << endl;
    while (Q != NULL)
    {
        if (Q->infor.diemTB > diemNguong)
        {
            display(Q->infor);
            found = true;
        }
        Q = Q->next;
    }
    if (!found) cout << "(Khong co sinh vien phu hop)\n";
}

// chen 1 nut vao vi tri (1-based)
void chenNode(TRO &L, SinhVien elem, int viTri)
{
    TRO P, Q;
    P = new Node;
    P->infor = elem;
    P->next = NULL;

    if (viTri <= 1 || L == NULL)
    {
        P->next = L;
        L = P;
        return;
    }

    Q = L;
    int i = 1;
    while (Q->next != NULL && i < viTri - 1)
    {
        Q = Q->next;
        i++;
    }
    // chen sau Q
    P->next = Q->next;
    Q->next = P;
}

// xoa 1 nut theo ma so (su dung p va q)
void xoaNode(TRO &L, string ma)
{
    if (L == NULL)
    {
        cout << "Danh sach rong, khong co gi de xoa.\n";
        return;
    }
    TRO Q = L;
    // tim Q la nut can xoa
    while (Q != NULL && Q->infor.maSo != ma) Q = Q->next;
    if (Q == NULL)
    {
        cout << "Khong tim thay sinh vien co ma = " << ma << "\n";
        return;
    }
    if (Q == L) // xoa dau
    {
        L = L->next;
        delete Q;
        cout << "Da xoa sinh vien tai dau danh sach (ma = " << ma << ").\n";
        return;
    }
    TRO P = L;
    while (P->next != Q) P = P->next; // tim nut truoc Q
    P->next = Q->next;
    delete Q;
    cout << "Da xoa sinh vien co ma = " << ma << "\n";
}

// xoa theo dieu kien: xoa phan tu dau tien co diemTB < diemNguong
void xoaTheoDieuKien(TRO &L, float diemNguong)
{
    if (L == NULL)
    {
        cout << "Danh sach rong, khong co gi de xoa.\n";
        return;
    }
    TRO Q = L;
    while (Q != NULL && Q->infor.diemTB >= diemNguong) Q = Q->next;
    if (Q == NULL)
    {
        cout << "Khong co sinh vien nao co diemTB < " << diemNguong << "\n";
        return;
    }
    if (Q == L)
    {
        L = L->next;
        delete Q;
        cout << "Da xoa sinh vien dau tien co diemTB < " << diemNguong << "\n";
        return;
    }
    TRO P = L;
    while (P->next != Q) P = P->next;
    P->next = Q->next;
    delete Q;
    cout << "Da xoa sinh vien dau tien co diemTB < " << diemNguong << "\n";
}

// xoa toan bo danh sach
void xoaToanBoDanhSach(TRO &L)
{
    TRO P = L;
    while (P != NULL)
    {
        TRO Q = P;
        P = P->next;
        delete Q;
    }
    L = NULL;
    cout << "Da xoa toan bo danh sach.\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    TRO L;
    // khoi tao tu mau
    khoiTaoDanhSach(L);

    cout << "=========== DANH SACH NHAP ===========\n";
    showList(L);
    cout << " Co tong cong " << lenghtList(L) << " sinh vien. \n";

    // Hien thi sinh vien co diemTB > 5
    hienThiTheoDieuKien(L, 5.0f);

    // Chen sinh vien moi vao vi tri 5
    SinhVien sv;
    sv.maSo = "SV99"; sv.ten = "Nguyen Van X"; sv.diemTB = 6.5f; sv.soMonTruot = 0;
    chenNode(L, sv, 5);
    cout << "\nSau khi chen 1 sinh vien vao vi tri 5:\n";
    showList(L);

    // Xoa phan tu dau tien co diemTB < 5
    xoaTheoDieuKien(L, 5.0f);
    cout << "\nSau khi xoa phan tu dau tien co diemTB < 5:\n";
    showList(L);

    // Tim kiem 1 sinh vien
    string ma;
    cout << "\n * Ma sinh vien can tim: "; cin >> ma;
    TRO KQ = search(L, ma);
    if (KQ == NULL)
    {
        cout << "!!! Khong tim thay sinh vien co ma " << ma << " trong danh sach !!!\n";
    }
    else
    {
        cout << "=========== Thong tin sinh vien co ma " << ma << " ===========\n";
        display(KQ->infor);
    }

    // Xoa toan bo danh sach
    xoaToanBoDanhSach(L);
    showList(L);

    return 0;
}

