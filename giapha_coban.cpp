#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

const int MAX_NODE = 1000;
const int NAM_NHO_NHAT = 1000;
const int NAM_LON_NHAT = 2100;

struct Node {
    string id;
    string name;
    int birthYear;
    char gender;
    Node* firstChild;
    Node* nextSibling;
    Node* spouse;
};

Node* root = NULL;
Node* dsNgoai = NULL;

string catKhoangTrang(string s);
string docDong(string loiNhac);
bool laSoNguyen(string s);
int docSoNguyen(string loiNhac, int nho, int lon);
bool xacNhan(string cauHoi);
string tenGioiTinh(char g);
bool maHopLe(string ma);
bool tenHopLe(string ten);
Node* taoNode(string id, string name, int nam, char gt);
void xoaCay(Node* n);
Node* timTheoMa(Node* n, string ma);
Node* timCha(Node* n, Node* dich);
bool namTrongCayCon(Node* goc, Node* dich);
int demCon(Node* n);
int demThanhVien(Node* n);
void themConCuoi(Node* cha, Node* con);
void thayTheTrongDanhSach(Node* cha, Node* x, Node* thayThe);
void tachNode(Node* cha, Node* x);
Node* hoiThanhVien(string loiNhac);
void inThongTin(Node* n);
void taoDuLieuMau();
void menuKhoiTao();
void hienHuongDanNhap();
void hienMenu();
Node* nhapThanhVienMoi(Node* cha, char gtBatBuoc);
void themThanhVien();
void timTheoTen(Node* n, string tuKhoa, int& soKetQua);
void timKiem();
void suaThanhVien();
void xoaThanhVien();
void chuyenNhanh();
void themConVaQuanHe();
void hienThiDanhSachCon();
void hienThiAnhChiEm();
void inMoTaQuanHe(int da, int db);
void traCuuQuanHe();
int tinhTheHe(Node* n, Node* dich, int doSau);
void dfsDeQuy(Node* n, int doSau);
void menuDFS();
void menuBFS();
Node* timLCA(Node* goc, Node* a, Node* b);
bool timDuongDi(Node* n, Node* dich, Node* duong[], int& soLuong);
void menuLCA();
void menuTheHe();
int chieuCao(Node* n);
void demGioiTinh(Node* n, int& nam, int& nu);
void timNamSinhNhoNhat(Node* n, int& namNho);
void inNguoiSinhNam(Node* n, int nam, bool& laDauTien);
void thongKe();
void inCayPhanCap(Node* n, string tienTo, bool laCuoi, bool laGoc);
int doRongHienThi(string s);
string soSangChuoi(int v);
void hienThiBangThanhVien();
void xuatGiaPha();
bool laNguoiNgoai(Node* n);
int demNgoai();
int tongThanhVien();
void themNgoai(Node* n);
void goNgoai(Node* n);
void giaiPhongNgoai();
void donNgoaiNeuCayRong();
Node* timThanhVien(string ma);
void ketHon(Node* a, Node* b);
void huyKetHon(Node* a);
void goQuanHeVoChongTrongCay(Node* n);
bool laHuyetThongGan(Node* a, Node* b);
string kiemTraKetHon(Node* a, Node* b);
string tenHienThi(Node* n);
string chuThuong(string s);
string boDauHaiCham(string s);
bool canTrongCay(Node* n);
int layDanhSach(Node* ds[]);
string moTaQuanHeBang(Node* n);
void hienThiBangChon();
void thuThapTheoTen(Node* n, string tuKhoaThuong, Node* kq[], int& so);
void inMotDong(Node* n);
Node* chonTheoMa();
Node* chonTheoTen();
Node* chonTheoDanhSach();
Node* chonThanhVien(string tieuDe, bool chiTrongCay);
void themQuanHeVoChong();
void taoVoChongMoi();
void huyQuanHeVoChong();
void menuVoChong();
string tenBacChuCoDiCau(Node* s, Node* m);
string tenAnhChiEm(Node* a, Node* b, bool ho);
void xacDinhChaMe(Node* n, Node*& cha, Node*& me, bool& chaSuyRa, bool& meSuyRa);
bool xacDinhQuanHe(Node* a, Node* b, string& ten, string& coSo);
void traCuuHaiNguoi();
void inDuongQuanHe(Node* a, Node* b, bool kemMoTaChung);
Node* themVoChongMau(Node* nguoi, string id, string ten, int nam, char gt);
void inChaMe(string nhan, Node* n, bool suyRa);
void xemQuanHeThanhVien();
void timTheoTenNgoai(string tuKhoa, int& soKetQua);
void thongKeNgoai(int& nam, int& nu, int& namNho);
void inNguoiSinhNamNgoai(int nam, bool& laDauTien);
int demCoVoChongTrongCay(Node* n);
int demCapVoChong();
void inO(string noiDung, int doRong);
void inDuongKe(int w1, int w2, int w3, int w4, int w5, int w6);

string catKhoangTrang(string s) {
    int dau = 0;
    int cuoi = (int)s.length() - 1;
    while (dau <= cuoi && (s[dau] == ' ' || s[dau] == '\t' || s[dau] == '\r' || s[dau] == '\n'))
        dau++;
    while (cuoi >= dau && (s[cuoi] == ' ' || s[cuoi] == '\t' || s[cuoi] == '\r' || s[cuoi] == '\n'))
        cuoi--;
    return s.substr(dau, cuoi - dau + 1);
}

string docDong(string loiNhac) {
    cout << loiNhac;
    string s;
    if (!getline(cin, s)) {
        cout << "\n(Het du lieu nhap, thoat chuong trinh)\n";
        exit(0);
    }
    return catKhoangTrang(s);
}

bool laSoNguyen(string s) {
    if (s.length() == 0) return false;
    for (int i = 0; i < (int)s.length(); i++) {
        if (s[i] < '0' || s[i] > '9') return false;
    }
    return true;
}

int docSoNguyen(string loiNhac, int nho, int lon) {
    while (true) {
        string s = docDong(loiNhac);
        if (laSoNguyen(s) && s.length() <= 9) {
            int v = atoi(s.c_str());
            if (v >= nho && v <= lon) return v;
        }
        cout << "  ! Hay nhap so nguyen tu " << nho << " den " << lon << ".\n";
    }
}

bool xacNhan(string cauHoi) {
    string s = docDong(cauHoi + " (c/k): ");
    return (s == "c" || s == "C" || s == "y" || s == "Y");
}

string tenGioiTinh(char g) {
    if (g == 'M') return "Nam";
    return "Nu";
}

bool maHopLe(string ma) {
    if (ma.length() == 0) return false;
    if (!isalnum((unsigned char)ma[0])) return false;
    for (int i = 0; i < (int)ma.length(); i++) {
        unsigned char c = (unsigned char)ma[i];
        if (!isalnum(c) && c != '_' && c != '-') return false;
    }
    return true;
}

bool tenHopLe(string ten) {
    if (ten.length() == 0) return false;
    if (ten.find('|') != string::npos) return false;
    return true;
}

Node* taoNode(string id, string name, int nam, char gt) {
    Node* n = new Node;
    n->id = id;
    n->name = name;
    n->birthYear = nam;
    n->gender = gt;
    n->firstChild = NULL;
    n->nextSibling = NULL;
    n->spouse = NULL;
    return n;
}

void xoaCay(Node* n) {
    if (n == NULL) return;
    xoaCay(n->firstChild);
    xoaCay(n->nextSibling);
    delete n;
}

Node* timTheoMa(Node* n, string ma) {
    if (n == NULL) return NULL;
    if (n->id == ma) return n;
    Node* kq = timTheoMa(n->firstChild, ma);
    if (kq != NULL) return kq;
    return timTheoMa(n->nextSibling, ma);
}

Node* timCha(Node* n, Node* dich) {
    if (n == NULL) return NULL;
    Node* c;
    for (c = n->firstChild; c != NULL; c = c->nextSibling) {
        if (c == dich) return n;
    }
    for (c = n->firstChild; c != NULL; c = c->nextSibling) {
        Node* kq = timCha(c, dich);
        if (kq != NULL) return kq;
    }
    return NULL;
}

bool namTrongCayCon(Node* goc, Node* dich) {
    if (goc == NULL) return false;
    if (goc == dich) return true;
    for (Node* c = goc->firstChild; c != NULL; c = c->nextSibling) {
        if (namTrongCayCon(c, dich)) return true;
    }
    return false;
}

int demCon(Node* n) {
    int dem = 0;
    for (Node* c = n->firstChild; c != NULL; c = c->nextSibling) dem++;
    return dem;
}

int demThanhVien(Node* n) {
    if (n == NULL) return 0;
    return 1 + demThanhVien(n->firstChild) + demThanhVien(n->nextSibling);
}

void themConCuoi(Node* cha, Node* con) {
    con->nextSibling = NULL;
    if (cha->firstChild == NULL) {
        cha->firstChild = con;
    } else {
        Node* t = cha->firstChild;
        while (t->nextSibling != NULL) t = t->nextSibling;
        t->nextSibling = con;
    }
}

void thayTheTrongDanhSach(Node* cha, Node* x, Node* thayThe) {
    if (cha->firstChild == x) {
        cha->firstChild = thayThe;
    } else {
        Node* truoc = cha->firstChild;
        while (truoc != NULL && truoc->nextSibling != x) truoc = truoc->nextSibling;
        if (truoc != NULL) truoc->nextSibling = thayThe;
    }
}

void tachNode(Node* cha, Node* x) {
    thayTheTrongDanhSach(cha, x, x->nextSibling);
    x->nextSibling = NULL;
}

Node* hoiThanhVien(string loiNhac) {
    return chonThanhVien(loiNhac, false);
}

void inThongTin(Node* n) {
    Node* cha = timCha(root, n);
    cout << "  Ma: " << n->id << " | Ten: " << n->name
         << " | Nam sinh: " << n->birthYear
         << " | Gioi tinh: " << tenGioiTinh(n->gender) << "\n";
    cout << "  Cha/me: ";
    if (laNguoiNgoai(n)) cout << "(chua co trong gia pha - nguoi nhap gia)";
    else if (cha == NULL) cout << "(nguoi goc)";
    else cout << cha->name << " [" << cha->id << "]";
    cout << " | So con: " << demCon(n) << " | The he: ";
    if (laNguoiNgoai(n)) cout << "(khong thuoc cay huyet thong)";
    else cout << tinhTheHe(root, n, 1);
    cout << "\n";
    cout << "  Vo/chong: ";
    if (n->spouse == NULL) cout << "(chua co)";
    else cout << n->spouse->name << " [" << n->spouse->id << "]";
    cout << "\n";
}

void taoDuLieuMau() {
    xoaCay(root);
    giaiPhongNgoai();
    root = taoNode("G001", "Nguyen Van An", 1940, 'M');
    Node* g002 = taoNode("G002", "Nguyen Van Binh", 1965, 'M');
    Node* g003 = taoNode("G003", "Nguyen Thi Lan", 1968, 'F');
    Node* g004 = taoNode("G004", "Nguyen Van Dung", 1972, 'M');
    Node* g005 = taoNode("G005", "Nguyen Van Cuong", 1990, 'M');
    Node* g006 = taoNode("G006", "Nguyen Thi Dao", 1993, 'F');
    Node* g007 = taoNode("G007", "Tran Van Duc", 1992, 'M');
    Node* g008 = taoNode("G008", "Tran Thi Em", 1995, 'F');
    Node* g009 = taoNode("G009", "Nguyen Van Khoa", 2015, 'M');
    Node* g010 = taoNode("G010", "Nguyen Thi Hoa", 2018, 'F');
    themConCuoi(root, g002);
    themConCuoi(root, g003);
    themConCuoi(root, g004);
    themConCuoi(g002, g005);
    themConCuoi(g002, g006);
    themConCuoi(g003, g007);
    themConCuoi(g003, g008);
    themConCuoi(g005, g009);
    themConCuoi(g005, g010);

    themVoChongMau(g002, "G011", "Tran Thi Mai", 1966, 'F');
    themVoChongMau(g005, "G012", "Le Thi Huong", 1992, 'F');
    themVoChongMau(g008, "G013", "Pham Van Son", 1991, 'M');
    themVoChongMau(g003, "G014", "Nguyen Van Long", 1967, 'M');
}

void hienHuongDanNhap() {
    cout << "\n========== HUONG DAN NHAP THANH VIEN ==========\n\n";
    cout << "Moi thanh vien can co cac thong tin:\n";
    cout << "1. Ma thanh vien: Ma rieng, khong duoc trung.\n";
    cout << "2. Ho va ten: Nhap day du ho ten.\n";
    cout << "3. Nam sinh: Nhap nam sinh hop le.\n";
    cout << "4. Gioi tinh: Chon Nam hoac Nu theo quy uoc cua chuong trinh.\n";
    cout << "5. Ma cha/me: Nhap ma cua thanh vien cha/me da ton tai.\n\n";
    cout << "Luu y:\n";
    cout << "- Thanh vien dau tien se la goc cua gia pha.\n";
    cout << "- Thanh vien dau tien khong can nhap ma cha/me.\n";
    cout << "- Tu thanh vien thu hai tro di, can nhap ma cha/me da ton tai.\n";
    cout << "- Neu nhap sai, chuong trinh phai thong bao va cho nhap lai.\n";
}

void menuKhoiTao() {
    cout << "\n========== KHOI TAO GIA PHA ==========\n";
    cout << "1. Su dung du lieu mau\n";
    cout << "2. Tu nhap du lieu gia pha moi\n";
    int chon = docSoNguyen("Lua chon cua ban: ", 1, 2);
    if (chon == 1) {
        taoDuLieuMau();
        cout << "\n";
        hienThiBangThanhVien();
    } else {
        xoaCay(root);
        root = NULL;
        giaiPhongNgoai();
        hienHuongDanNhap();
    }
}

void hienMenu() {
    cout << "\n================ QUAN LY GIA PHA GIA TOC MINI ================\n";
    cout << " 1. Them thanh vien\n";
    cout << " 2. Tim kiem thanh vien\n";
    cout << " 3. Sua thong tin thanh vien\n";
    cout << " 4. Xoa thanh vien\n";
    cout << " 5. Them con va thiet lap quan he gia dinh\n";
    cout << " 6. Hien thi danh sach con\n";
    cout << " 7. Hien thi anh/chi/em\n";
    cout << " 8. Duyet cay DFS\n";
    cout << " 9. Duyet cay BFS\n";
    cout << "10. Tim to tien chung gan nhat LCA\n";
    cout << "11. Tra cuu thong tin va quan he ho hang\n";
    cout << "12. Tinh bac the he\n";
    cout << "13. Thong ke gia pha\n";
    cout << "14. Xuat gia pha (cay phan cap / bang danh sach)\n";
    cout << "15. Quan ly quan he vo chong\n";
    cout << " 0. Thoat chuong trinh\n";
    cout << "==============================================================\n";
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif
    menuKhoiTao();

    int chon = -1;
    while (chon != 0) {
        hienMenu();
        chon = docSoNguyen("Chon chuc nang (0-15): ", 0, 15);
        cout << "\n";
        switch (chon) {
            case 1:  themThanhVien();       break;
            case 2:  timKiem();             break;
            case 3:  suaThanhVien();        break;
            case 4:  xoaThanhVien();        break;
            case 5:  themConVaQuanHe();     break;
            case 6:  hienThiDanhSachCon();  break;
            case 7:  hienThiAnhChiEm();     break;
            case 8:  menuDFS();             break;
            case 9:  menuBFS();             break;
            case 10: menuLCA();             break;
            case 11: traCuuQuanHe();        break;
            case 12: menuTheHe();           break;
            case 13: thongKe();             break;
            case 14: xuatGiaPha();          break;
            case 15: menuVoChong();         break;
            case 0:
                if (!xacNhan("Thoat chuong trinh? (du lieu chi nam trong bo nho nen se mat)")) chon = -1;
                break;
        }
    }
    xoaCay(root);
    giaiPhongNgoai();
    cout << "Tam biet!\n";
    return 0;
}

Node* nhapThanhVienMoi(Node* cha, char gtBatBuoc) {
    string id;
    while (true) {
        id = docDong("Ma dinh danh (chu/so/_/-, Enter de huy): ");
        if (id == "") return NULL;
        if (!maHopLe(id)) {
            cout << "  ! Ma khong hop le (khong co khoang trang hoac ky tu la).\n";
        } else if (timThanhVien(id) != NULL) {
            cout << "  ! Ma nay da ton tai, hay chon ma khac.\n";
        } else {
            break;
        }
    }
    string ten;
    while (true) {
        ten = docDong("Ho ten: ");
        if (tenHopLe(ten)) break;
        cout << "  ! Ten khong duoc de trong va khong chua ky tu '|'.\n";
    }
    int nam;
    while (true) {
        nam = docSoNguyen("Nam sinh: ", NAM_NHO_NHAT, NAM_LON_NHAT);
        if (cha != NULL && nam <= cha->birthYear) {
            cout << "  ! Nam sinh phai lon hon nam sinh cua cha/me (" << cha->birthYear << ").\n";
        } else {
            break;
        }
    }
    char kyHieu = gtBatBuoc;
    if (kyHieu == '\0') {
        int gt = docSoNguyen("Gioi tinh (1 = Nam, 2 = Nu): ", 1, 2);
        kyHieu = 'F';
        if (gt == 1) kyHieu = 'M';
    } else {
        cout << "Gioi tinh: " << tenGioiTinh(kyHieu) << " (tu xac dinh theo quy uoc vo chong)\n";
    }
    return taoNode(id, ten, nam, kyHieu);
}

void themThanhVien() {
    if (tongThanhVien() >= MAX_NODE) {
        cout << "  ! Da dat so thanh vien toi da (" << MAX_NODE << ").\n";
        return;
    }
    Node* cha = NULL;
    if (root == NULL) {
        cout << "Gia pha dang rong: thanh vien dau tien se la NGUOI GOC.\n";
    } else {
        cout << "(Moi nguoi, tru nguoi goc, phai co cha/me trong gia pha)\n";
        cha = chonThanhVien("Chon cha/me cua thanh vien moi", true);
        if (cha == NULL) return;
    }
    Node* moi = nhapThanhVienMoi(cha, '\0');
    if (moi == NULL) {
        cout << "  Da huy.\n";
        return;
    }
    if (cha == NULL) {
        root = moi;
        cout << "  => Da tao nguoi goc: " << moi->name << "\n";
    } else {
        themConCuoi(cha, moi);
        cout << "  => Da them " << moi->name << " lam con cua " << cha->name << ".\n";
    }
}

void timTheoTen(Node* n, string tuKhoa, int& soKetQua) {
    if (n == NULL) return;
    if (n->name.find(tuKhoa) != string::npos) {
        inThongTin(n);
        soKetQua++;
    }
    timTheoTen(n->firstChild, tuKhoa, soKetQua);
    timTheoTen(n->nextSibling, tuKhoa, soKetQua);
}

void timKiem() {
    if (root == NULL) {
        cout << "  ! Gia pha dang rong.\n";
        return;
    }
    int cach = docSoNguyen("Tim theo: 1 = Ma, 2 = Ten : ", 1, 2);
    if (cach == 1) {
        string ma = docDong("Nhap ma: ");
        Node* n = timThanhVien(ma);
        if (n == NULL) cout << "  ! Khong tim thay thanh vien co ma '" << ma << "'.\n";
        else inThongTin(n);
    } else {
        string tuKhoa = docDong("Nhap ten (hoac mot phan ten): ");
        if (tuKhoa == "") {
            cout << "  ! Ban chua nhap ten.\n";
            return;
        }
        int soKetQua = 0;
        timTheoTen(root, tuKhoa, soKetQua);
        timTheoTenNgoai(tuKhoa, soKetQua);
        if (soKetQua == 0) cout << "  ! Khong tim thay thanh vien nao.\n";
        else cout << "  => Tim thay " << soKetQua << " thanh vien.\n";
    }
}

void suaThanhVien() {
    if (root == NULL) {
        cout << "  ! Gia pha dang rong.\n";
        return;
    }
    Node* n = hoiThanhVien("Ma thanh vien can sua: ");
    if (n == NULL) return;
    inThongTin(n);
    Node* cha = timCha(root, n);

    string s = docDong("Ten moi (Enter = giu nguyen): ");
    if (s != "") {
        if (tenHopLe(s)) n->name = s;
        else cout << "  ! Ten khong hop le, giu nguyen.\n";
    }

    s = docDong("Nam sinh moi (Enter = giu nguyen): ");
    if (s != "") {
        bool hopLe = laSoNguyen(s) && s.length() <= 4;
        int nam = 0;
        if (hopLe) {
            nam = atoi(s.c_str());
            if (nam < NAM_NHO_NHAT || nam > NAM_LON_NHAT) hopLe = false;
        }
        if (hopLe && cha != NULL && nam <= cha->birthYear) hopLe = false;
        for (Node* c = n->firstChild; hopLe && c != NULL; c = c->nextSibling) {
            if (c->birthYear <= nam) hopLe = false;
        }
        if (hopLe) n->birthYear = nam;
        else cout << "  ! Nam sinh khong hop le hoac mau thuan voi cha/me - con, giu nguyen.\n";
    }

    s = docDong("Gioi tinh moi (1 = Nam, 2 = Nu, Enter = giu nguyen): ");
    if (s == "1" || s == "2") {
        char gMoi = 'F';
        if (s == "1") gMoi = 'M';
        if (n->spouse != NULL && n->spouse->gender == gMoi)
            cout << "  ! Khong doi duoc: se cung gioi tinh voi vo/chong (" << n->spouse->name << "), giu nguyen.\n";
        else n->gender = gMoi;
    } else if (s != "") cout << "  ! Lua chon khong hop le, giu nguyen.\n";

    cout << "  => Thong tin sau khi sua:\n";
    inThongTin(n);
}

void xoaThanhVien() {
    if (root == NULL) {
        cout << "  ! Gia pha dang rong.\n";
        return;
    }
    Node* x = hoiThanhVien("Ma thanh vien can xoa: ");
    if (x == NULL) return;
    inThongTin(x);
    if (laNguoiNgoai(x)) {
        if (!xacNhan("Xoa " + x->name + " (nguoi nhap gia)?")) {
            cout << "  Da huy.\n";
            return;
        }
        huyKetHon(x);
        goNgoai(x);
        delete x;
        cout << "  => Da xoa; quan he vo chong lien quan (neu co) da duoc go.\n";
        return;
    }
    cout << "Cach xoa:\n";
    cout << "  1 = Chi xoa nguoi nay (con chau duoc noi len cho cha/me cua ho)\n";
    cout << "  2 = Xoa ca nhanh (nguoi nay va toan bo hau due)\n";
    int cach = docSoNguyen("Chon: ", 1, 2);
    Node* cha = timCha(root, x);

    if (cach == 2) {
        int soNguoi = 1 + demThanhVien(x->firstChild);
        cout << "  Se xoa " << soNguoi << " nguoi.\n";
        if (!xacNhan("Xac nhan xoa ca nhanh?")) {
            cout << "  Da huy.\n";
            return;
        }
        if (cha == NULL) {
            goQuanHeVoChongTrongCay(root);
            xoaCay(root);
            root = NULL;
            donNgoaiNeuCayRong();
        } else {
            tachNode(cha, x);
            goQuanHeVoChongTrongCay(x);
            xoaCay(x);
        }
        cout << "  => Da xoa " << soNguoi << " thanh vien.\n";
        return;
    }

    if (cha == NULL) {
        if (x->firstChild == NULL) {
            huyKetHon(x);
            delete x;
            root = NULL;
            donNgoaiNeuCayRong();
        } else if (x->firstChild->nextSibling == NULL) {
            Node* moi = x->firstChild;
            huyKetHon(x);
            delete x;
            root = moi;
            cout << "  (" << moi->name << " tro thanh nguoi goc moi)\n";
        } else {
            cout << "  ! Nguoi goc co nhieu con nen khong the chi xoa rieng nguoi goc\n";
            cout << "    (se tao ra nhieu cay). Hay chon cach 2.\n";
            return;
        }
        cout << "  => Da xoa.\n";
        return;
    }
    if (!xacNhan("Xoa " + x->name + " (con chau chuyen len " + cha->name + ")?")) {
        cout << "  Da huy.\n";
        return;
    }
    Node* conDau = x->firstChild;
    Node* emKe = x->nextSibling;
    Node* thayThe = emKe;
    if (conDau != NULL) {
        Node* cuoi = conDau;
        while (cuoi->nextSibling != NULL) cuoi = cuoi->nextSibling;
        cuoi->nextSibling = emKe;
        thayThe = conDau;
    }
    thayTheTrongDanhSach(cha, x, thayThe);
    huyKetHon(x);
    delete x;
    cout << "  => Da xoa; con chau duoc chuyen len lam con cua " << cha->name << ".\n";
}

void chuyenNhanh() {
    if (root == NULL) {
        cout << "  ! Gia pha dang rong.\n";
        return;
    }
    Node* con = chonThanhVien("Thanh vien can chuyen", true);
    if (con == NULL) return;
    Node* chaMoi = chonThanhVien("Cha/me moi", true);
    if (chaMoi == NULL) return;

    if (con == root) {
        cout << "  ! Nguoi goc khong the tro thanh con cua ai.\n";
        return;
    }
    if (con == chaMoi) {
        cout << "  ! Mot nguoi khong the la cha/me cua chinh minh.\n";
        return;
    }
    if (namTrongCayCon(con, chaMoi)) {
        cout << "  ! Tu choi: " << chaMoi->name << " la hau due cua " << con->name
             << " nen se tao chu trinh.\n";
        return;
    }
    Node* chaCu = timCha(root, con);
    if (chaCu == chaMoi) {
        cout << "  ! " << con->name << " da la con cua " << chaMoi->name << ".\n";
        return;
    }
    if (con->spouse == chaMoi) {
        cout << "  ! Tu choi: " << chaMoi->name << " la vo/chong cua " << con->name
             << " nen khong the tro thanh cha/me cua nguoi nay.\n";
        return;
    }
    if (con->spouse != NULL && namTrongCayCon(con->spouse, chaMoi)) {
        cout << "  ! Tu choi: " << chaMoi->name << " la hau due cua " << con->spouse->name
             << " (vo/chong cua " << con->name << "), chuyen nhu vay se lam sai quan he vo chong.\n";
        return;
    }
    if (chaMoi->spouse != NULL && namTrongCayCon(con, chaMoi->spouse)) {
        cout << "  ! Tu choi: vo/chong cua " << chaMoi->name << " (" << chaMoi->spouse->name
             << ") la hau due cua " << con->name << ".\n";
        return;
    }
    if (con->birthYear <= chaMoi->birthYear) {
        cout << "  ! Nam sinh cua con phai lon hon nam sinh cua cha/me moi.\n";
        return;
    }
    tachNode(chaCu, con);
    themConCuoi(chaMoi, con);
    cout << "  => Da chuyen " << con->name << " (cung hau due) sang lam con cua "
         << chaMoi->name << ".\n";
}

void themConVaQuanHe() {
    cout << "  1 = Tao thanh vien moi lam con\n";
    cout << "  2 = Chuyen thanh vien da co sang lam con cua nguoi khac\n";
    int chon = docSoNguyen("Chon: ", 1, 2);
    if (chon == 1) themThanhVien();
    else chuyenNhanh();
}

void hienThiDanhSachCon() {
    if (root == NULL) {
        cout << "  ! Gia pha dang rong.\n";
        return;
    }
    Node* n = hoiThanhVien("Ma cha/me: ");
    if (n == NULL) return;
    if (n->firstChild == NULL) {
        cout << "  " << n->name << " chua co con.\n";
        if (n->spouse != NULL && n->spouse->firstChild != NULL)
            cout << "  (Vo/chong " << n->spouse->name << " co con trong gia pha; xem o chuc nang 11.)\n";
        return;
    }
    cout << "  Con cua " << n->name << " (" << demCon(n) << " nguoi):\n";
    int stt = 1;
    for (Node* c = n->firstChild; c != NULL; c = c->nextSibling) {
        cout << "   " << stt << ". " << c->name << " [" << c->id << "] - "
             << c->birthYear << ", " << tenGioiTinh(c->gender) << "\n";
        stt++;
    }
}

void hienThiAnhChiEm() {
    if (root == NULL) {
        cout << "  ! Gia pha dang rong.\n";
        return;
    }
    Node* n = hoiThanhVien("Ma thanh vien: ");
    if (n == NULL) return;
    if (!canTrongCay(n)) return;
    Node* cha = timCha(root, n);
    if (cha == NULL) {
        cout << "  " << n->name << " la nguoi goc nen khong co anh/chi/em.\n";
        return;
    }
    int dem = 0;
    for (Node* c = cha->firstChild; c != NULL; c = c->nextSibling) {
        if (c == n) continue;
        if (dem == 0)
            cout << "  Anh/chi/em cua " << n->name << " (cung cha/me " << cha->name << "):\n";
        cout << "   - " << c->name << " [" << c->id << "] - " << c->birthYear
             << ", " << tenGioiTinh(c->gender) << "\n";
        dem++;
    }
    if (dem == 0) cout << "  " << n->name << " la con mot (khong co anh/chi/em).\n";
}

void inMoTaQuanHe(int da, int db) {
    if (da == 0 && db == 0) {
        cout << "cung mot nguoi";
    } else if (da == 0) {
        if (db == 1) cout << "cha/me";
        else if (db == 2) cout << "ong/ba";
        else if (db == 3) cout << "cu";
        else cout << "to tien (cach " << db << " doi)";
    } else if (db == 0) {
        if (da == 1) cout << "con";
        else if (da == 2) cout << "chau";
        else if (da == 3) cout << "chat";
        else cout << "hau due (cach " << da << " doi)";
    } else if (da == 1 && db == 1) {
        cout << "anh/chi/em (cung cha/me)";
    } else if (da == 1 && db == 2) {
        cout << "chu/bac/co/cau/di (anh/chi/em cua cha/me)";
    } else if (da == 2 && db == 1) {
        cout << "chau (con cua anh/chi/em)";
    } else if (da == 2 && db == 2) {
        cout << "anh/chi/em ho";
    } else {
        cout << "ho hang (A cach to tien chung " << da << " doi, B cach " << db << " doi)";
    }
}

void inDuongQuanHe(Node* a, Node* b, bool kemMoTaChung) {
    Node* l = timLCA(root, a, b);
    Node* duongA[MAX_NODE];
    Node* duongB[MAX_NODE];
    int soA = 0, soB = 0;
    timDuongDi(root, a, duongA, soA);
    timDuongDi(root, b, duongB, soB);

    int theHeL = tinhTheHe(root, l, 1);
    int da = soA - theHeL;
    int db = soB - theHeL;

    if (kemMoTaChung) {
        cout << "  Mo ta chung: " << a->name << " la ";
        inMoTaQuanHe(da, db);
        cout << " cua " << b->name << ".\n";
    }

    cout << "  Duong quan he: ";
    int i;
    for (i = soA - 1; i >= theHeL - 1; i--) {
        cout << duongA[i]->name;
        if (i > theHeL - 1) cout << " -> ";
    }
    for (i = theHeL; i < soB; i++) {
        cout << " -> " << duongB[i]->name;
    }
    cout << "\n  (To tien chung gan nhat: " << l->name << ")\n";
}

void traCuuQuanHe() {
    if (tongThanhVien() == 0) {
        cout << "  ! Gia pha dang rong.\n";
        return;
    }
    cout << "  1 = Xem thong tin va quan he cua MOT thanh vien (cha, me, vo/chong, con, anh/chi/em...)\n";
    cout << "  2 = Tra cuu quan he giua HAI thanh vien (ong, ba, chu, bac, co, di, cau, chau...)\n";
    cout << "  0 = Quay lai\n";
    int chon = docSoNguyen("Chon: ", 0, 2);
    if (chon == 1) xemQuanHeThanhVien();
    else if (chon == 2) traCuuHaiNguoi();
}

int tinhTheHe(Node* n, Node* dich, int doSau) {
    if (n == NULL) return -1;
    if (n == dich) return doSau;
    int kq = tinhTheHe(n->firstChild, dich, doSau + 1);
    if (kq != -1) return kq;
    return tinhTheHe(n->nextSibling, dich, doSau);
}

void dfsDeQuy(Node* n, int doSau) {
    if (n == NULL) return;
    cout << string(doSau * 3, ' ') << "- [" << n->id << "] " << n->name
         << " (" << n->birthYear << ", " << tenGioiTinh(n->gender)
         << ") - the he " << doSau + 1 << "\n";
    dfsDeQuy(n->firstChild, doSau + 1);
    dfsDeQuy(n->nextSibling, doSau);
}

void menuDFS() {
    if (root == NULL) {
        cout << "  ! Gia pha dang rong.\n";
        return;
    }
    cout << "--- Duyet DFS (theo chieu sau) ---\n";
    dfsDeQuy(root, 0);
}

void menuBFS() {
    if (root == NULL) {
        cout << "  ! Gia pha dang rong.\n";
        return;
    }
    cout << "--- Duyet BFS (theo the he) ---\n";
    Node* hang[MAX_NODE];
    int mucNut[MAX_NODE];
    int dau = 0, cuoi = 0;
    hang[cuoi] = root;
    mucNut[cuoi] = 1;
    cuoi++;
    int mucHienTai = 0;
    while (dau < cuoi) {
        Node* n = hang[dau];
        int muc = mucNut[dau];
        dau++;
        if (muc != mucHienTai) {
            if (mucHienTai != 0) cout << "\n";
            cout << "The he " << muc << ": ";
            mucHienTai = muc;
        }
        cout << n->name << " [" << n->id << "]   ";
        for (Node* c = n->firstChild; c != NULL; c = c->nextSibling) {
            hang[cuoi] = c;
            mucNut[cuoi] = muc + 1;
            cuoi++;
        }
    }
    cout << "\n";
}

Node* timLCA(Node* goc, Node* a, Node* b) {
    if (goc == NULL) return NULL;
    if (goc == a || goc == b) return goc;
    Node* ketQua = NULL;
    int soNhanhThay = 0;
    for (Node* c = goc->firstChild; c != NULL; c = c->nextSibling) {
        Node* x = timLCA(c, a, b);
        if (x != NULL) {
            soNhanhThay++;
            ketQua = x;
        }
    }
    if (soNhanhThay >= 2) return goc;
    return ketQua;
}

bool timDuongDi(Node* n, Node* dich, Node* duong[], int& soLuong) {
    duong[soLuong] = n;
    soLuong++;
    if (n == dich) return true;
    for (Node* c = n->firstChild; c != NULL; c = c->nextSibling) {
        if (timDuongDi(c, dich, duong, soLuong)) return true;
    }
    soLuong--;
    return false;
}

void menuLCA() {
    if (root == NULL) {
        cout << "  ! Gia pha dang rong.\n";
        return;
    }
    Node* a = hoiThanhVien("Ma thanh vien thu nhat: ");
    if (a == NULL) return;
    Node* b = hoiThanhVien("Ma thanh vien thu hai: ");
    if (b == NULL) return;
    if (!canTrongCay(a) || !canTrongCay(b)) return;
    Node* l = timLCA(root, a, b);
    if (l == NULL) {
        cout << "  ! Khong ton tai to tien chung.\n";
    } else if (a == b) {
        cout << "  Hai ma la cung mot nguoi: " << a->name << ".\n";
    } else if (l == a) {
        cout << "  " << a->name << " la to tien cua " << b->name
             << " nen LCA chinh la " << l->name << ".\n";
    } else if (l == b) {
        cout << "  " << b->name << " la to tien cua " << a->name
             << " nen LCA chinh la " << l->name << ".\n";
    } else {
        cout << "  To tien chung gan nhat cua " << a->name << " va " << b->name
             << " la: " << l->name << " [" << l->id << "].\n";
    }
}

void menuTheHe() {
    if (root == NULL) {
        cout << "  ! Gia pha dang rong.\n";
        return;
    }
    Node* n = hoiThanhVien("Ma thanh vien: ");
    if (n == NULL) return;
    if (!canTrongCay(n)) return;
    int g = tinhTheHe(root, n, 1);
    cout << "  " << n->name << " thuoc the he " << g;
    if (g == 1) cout << " (nguoi goc).\n";
    else cout << " (cach nguoi goc " << g - 1 << " doi).\n";
}

int chieuCao(Node* n) {
    if (n == NULL) return 0;
    int hCon = 1 + chieuCao(n->firstChild);
    int hEm = chieuCao(n->nextSibling);
    if (hCon > hEm) return hCon;
    return hEm;
}

void demGioiTinh(Node* n, int& nam, int& nu) {
    if (n == NULL) return;
    if (n->gender == 'M') nam++;
    else nu++;
    demGioiTinh(n->firstChild, nam, nu);
    demGioiTinh(n->nextSibling, nam, nu);
}

void timNamSinhNhoNhat(Node* n, int& namNho) {
    if (n == NULL) return;
    if (n->birthYear < namNho) namNho = n->birthYear;
    timNamSinhNhoNhat(n->firstChild, namNho);
    timNamSinhNhoNhat(n->nextSibling, namNho);
}

void inNguoiSinhNam(Node* n, int nam, bool& laDauTien) {
    if (n == NULL) return;
    if (n->birthYear == nam) {
        if (!laDauTien) cout << ", ";
        cout << n->name << " [" << n->id << "]";
        laDauTien = false;
    }
    inNguoiSinhNam(n->firstChild, nam, laDauTien);
    inNguoiSinhNam(n->nextSibling, nam, laDauTien);
}

void thongKe() {
    if (root == NULL) {
        cout << "  ! Gia pha dang rong.\n";
        return;
    }
    int nam = 0, nu = 0;
    demGioiTinh(root, nam, nu);
    int namNho = NAM_LON_NHAT + 1;
    timNamSinhNhoNhat(root, namNho);
    thongKeNgoai(nam, nu, namNho);

    cout << "--- Thong ke gia pha ---\n";
    cout << "  Tong so thanh vien : " << tongThanhVien() << "\n";
    cout << "  So the he          : " << chieuCao(root) << "\n";
    cout << "  Nam / Nu           : " << nam << " / " << nu << "\n";
    cout << "  Nguoi lon tuoi nhat (sinh nam " << namNho << "): ";
    bool laDauTien = true;
    inNguoiSinhNam(root, namNho, laDauTien);
    inNguoiSinhNamNgoai(namNho, laDauTien);
    cout << "\n";
    if (dsNgoai != NULL)
        cout << "  Nguoi nhap gia     : " << demNgoai() << " (khong thuoc cay huyet thong)\n";
    if (demCapVoChong() > 0)
        cout << "  So cap vo chong    : " << demCapVoChong() << "\n";

    string ma = docDong("Nhap ma de xem so con truc tiep (Enter = bo qua): ");
    if (ma != "") {
        Node* n = timThanhVien(ma);
        if (n == NULL) cout << "  ! Khong tim thay thanh vien co ma '" << ma << "'.\n";
        else cout << "  " << n->name << " co " << demCon(n) << " con truc tiep.\n";
    }
}

void inCayPhanCap(Node* n, string tienTo, bool laCuoi, bool laGoc) {
    cout << tienTo;
    if (!laGoc) {
        if (laCuoi) cout << "`-- ";
        else cout << "|-- ";
    }
    cout << n->name << " [" << n->id << "] (" << n->birthYear << ", "
         << tenGioiTinh(n->gender) << ")\n";
    string tienToCon = tienTo;
    if (!laGoc) {
        if (laCuoi) tienToCon += "    ";
        else tienToCon += "|   ";
    }
    for (Node* c = n->firstChild; c != NULL; c = c->nextSibling) {
        inCayPhanCap(c, tienToCon, c->nextSibling == NULL, false);
    }
}

int doRongHienThi(string s) {
    int dem = 0;
    for (int i = 0; i < (int)s.length(); i++) {
        if (((unsigned char)s[i] & 0xC0) != 0x80) dem++;
    }
    return dem;
}

string soSangChuoi(int v) {
    if (v == 0) return "0";
    string kq = "";
    while (v > 0) {
        kq = string(1, (char)('0' + v % 10)) + kq;
        v = v / 10;
    }
    return kq;
}

void inO(string noiDung, int doRong) {
    cout << "| " << noiDung << string(doRong - doRongHienThi(noiDung), ' ') << " ";
}

void inDuongKe(int w1, int w2, int w3, int w4, int w5, int w6) {
    cout << "+" << string(w1 + 2, '-') << "+" << string(w2 + 2, '-')
         << "+" << string(w3 + 2, '-') << "+" << string(w4 + 2, '-')
         << "+" << string(w5 + 2, '-') << "+" << string(w6 + 2, '-') << "+\n";
}

void hienThiBangThanhVien() {
    if (root == NULL) {
        cout << "Gia pha chua co du lieu.\n";
        cout << "Hay chon chuc nang 1 de them thanh vien dau tien (nguoi goc),\n";
        cout << "sau do them cac thanh vien khac bang cach nhap ma cha/me.\n";
        return;
    }
    hienThiBangChon();
}

void xuatGiaPha() {
    if (root == NULL) {
        hienThiBangThanhVien();
        return;
    }
    cout << "  1 = Cay phan cap\n";
    cout << "  2 = Bang danh sach thanh vien\n";
    int chon = docSoNguyen("Chon: ", 1, 2);
    if (chon == 1) {
        cout << "--- GIA PHA ---\n";
        inCayPhanCap(root, "", true, true);
    } else {
        hienThiBangThanhVien();
    }
}

bool laNguoiNgoai(Node* n) {
    for (Node* t = dsNgoai; t != NULL; t = t->nextSibling) {
        if (t == n) return true;
    }
    return false;
}

int demNgoai() {
    int dem = 0;
    for (Node* t = dsNgoai; t != NULL; t = t->nextSibling) dem++;
    return dem;
}

int tongThanhVien() {
    return demThanhVien(root) + demNgoai();
}

void themNgoai(Node* n) {
    n->firstChild = NULL;
    n->nextSibling = NULL;
    if (dsNgoai == NULL) {
        dsNgoai = n;
        return;
    }
    Node* t = dsNgoai;
    while (t->nextSibling != NULL) t = t->nextSibling;
    t->nextSibling = n;
}

void goNgoai(Node* n) {
    if (dsNgoai == n) {
        dsNgoai = n->nextSibling;
    } else {
        Node* t = dsNgoai;
        while (t != NULL && t->nextSibling != n) t = t->nextSibling;
        if (t != NULL) t->nextSibling = n->nextSibling;
    }
    n->nextSibling = NULL;
}

void giaiPhongNgoai() {
    while (dsNgoai != NULL) {
        Node* t = dsNgoai;
        dsNgoai = t->nextSibling;
        delete t;
    }
}

void donNgoaiNeuCayRong() {
    if (root == NULL && dsNgoai != NULL) {
        cout << "  (Gia pha khong con cay huyet thong nen " << demNgoai()
             << " nguoi nhap gia cung duoc xoa theo.)\n";
        giaiPhongNgoai();
    }
}

Node* timThanhVien(string ma) {
    Node* n = timTheoMa(root, ma);
    if (n != NULL) return n;
    for (Node* t = dsNgoai; t != NULL; t = t->nextSibling) {
        if (t->id == ma) return t;
    }
    return NULL;
}

void ketHon(Node* a, Node* b) {
    a->spouse = b;
    b->spouse = a;
}

void huyKetHon(Node* a) {
    if (a->spouse != NULL) {
        a->spouse->spouse = NULL;
        a->spouse = NULL;
    }
}

void goQuanHeVoChongTrongCay(Node* n) {
    if (n == NULL) return;
    huyKetHon(n);
    goQuanHeVoChongTrongCay(n->firstChild);
    goQuanHeVoChongTrongCay(n->nextSibling);
}

bool laHuyetThongGan(Node* a, Node* b) {
    if (namTrongCayCon(a, b) || namTrongCayCon(b, a)) return true;
    Node* pa = timCha(root, a);
    return (pa != NULL && pa == timCha(root, b));
}

string kiemTraKetHon(Node* a, Node* b) {
    if (a == b) return "Mot nguoi khong the ket hon voi chinh minh.";
    if (a->spouse == b) return a->name + " va " + b->name + " da la vo chong.";
    if (a->spouse != NULL) return a->name + " da co vo/chong la " + a->spouse->name + ".";
    if (b->spouse != NULL) return b->name + " da co vo/chong la " + b->spouse->name + ".";
    if (a->gender == b->gender) {
        return "Theo quy uoc cua chuong trinh, vo chong phai gom mot Nam va mot Nu (ca hai dang la "
               + tenGioiTinh(a->gender) + ").";
    }
    if (laHuyetThongGan(a, b)) {
        return "Khong the ket hon vi hai nguoi la cha/me - con/hau due hoac anh/chi/em cung cha/me.";
    }
    return "";
}

string tenHienThi(Node* n) {
    return n->name + " [" + n->id + "]";
}

string chuThuong(string s) {
    for (int i = 0; i < (int)s.length(); i++) s[i] = (char)tolower((unsigned char)s[i]);
    return s;
}

string boDauHaiCham(string s) {
    int cuoi = (int)s.length() - 1;
    while (cuoi >= 0 && (s[cuoi] == ' ' || s[cuoi] == ':')) cuoi--;
    return s.substr(0, cuoi + 1);
}

bool canTrongCay(Node* n) {
    if (!laNguoiNgoai(n)) return true;
    cout << "  ! " << tenHienThi(n) << " la nguoi nhap gia (chi co quan he vo/chong,\n"
         << "    chua co cha/me trong gia pha) nen chuc nang nay khong ap dung duoc.\n"
         << "    Hay dung chuc nang 11 de xem quan he cua nguoi nay.\n";
    return false;
}

int layDanhSach(Node* ds[]) {
    int cuoi = 0;
    if (root != NULL) {
        int dau = 0;
        ds[cuoi] = root;
        cuoi++;
        while (dau < cuoi) {
            Node* n = ds[dau];
            dau++;
            for (Node* c = n->firstChild; c != NULL; c = c->nextSibling) {
                ds[cuoi] = c;
                cuoi++;
            }
        }
    }
    for (Node* t = dsNgoai; t != NULL; t = t->nextSibling) {
        ds[cuoi] = t;
        cuoi++;
    }
    return cuoi;
}

string moTaQuanHeBang(Node* n) {
    string kq = "";
    Node* tp = timCha(root, n);
    if (n == root) kq = "Nguoi goc";
    else if (tp != NULL) kq = (n->gender == 'M' ? "Con trai cua " : "Con gai cua ") + tp->name;
    if (n->spouse != NULL) {
        string vc = (n->gender == 'M' ? "Chong cua " : "Vo cua ") + n->spouse->name;
        if (kq == "") kq = vc;
        else kq += "; " + vc;
    }
    if (kq == "") kq = "Chua co quan he";
    return kq;
}

void hienThiBangChon() {
    Node* ds[MAX_NODE];
    string qh[MAX_NODE];
    int tong = layDanhSach(ds);
    if (tong == 0) {
        cout << "  ! Gia pha dang rong.\n";
        return;
    }
    int wStt = (int)soSangChuoi(tong).length();
    if (wStt < 3) wStt = 3;
    int wMa = doRongHienThi("Ma thanh vien");
    int wTen = doRongHienThi("Ho ten");
    int wNam = doRongHienThi("Nam sinh");
    int wGt = doRongHienThi("Gioi tinh");
    int wQh = doRongHienThi("Quan he");
    int i;
    for (i = 0; i < tong; i++) {
        qh[i] = moTaQuanHeBang(ds[i]);
        int d = doRongHienThi(ds[i]->id);
        if (d > wMa) wMa = d;
        d = doRongHienThi(ds[i]->name);
        if (d > wTen) wTen = d;
        d = doRongHienThi(qh[i]);
        if (d > wQh) wQh = d;
    }
    cout << "\n===== DANH SACH THANH VIEN =====\n";
    inDuongKe(wStt, wMa, wTen, wNam, wGt, wQh);
    inO("STT", wStt);  inO("Ma thanh vien", wMa);  inO("Ho ten", wTen);
    inO("Nam sinh", wNam);  inO("Gioi tinh", wGt);  inO("Quan he", wQh);
    cout << "|\n";
    inDuongKe(wStt, wMa, wTen, wNam, wGt, wQh);
    for (i = 0; i < tong; i++) {
        inO(soSangChuoi(i + 1), wStt);
        inO(ds[i]->id, wMa);
        inO(ds[i]->name, wTen);
        inO(soSangChuoi(ds[i]->birthYear), wNam);
        inO(tenGioiTinh(ds[i]->gender), wGt);
        inO(qh[i], wQh);
        cout << "|\n";
    }
    inDuongKe(wStt, wMa, wTen, wNam, wGt, wQh);
    cout << "Tong so thanh vien: " << tong;
    if (dsNgoai != NULL) cout << " (trong do " << demNgoai() << " nguoi nhap gia, khong thuoc cay huyet thong)";
    cout << "\n";
}

void thuThapTheoTen(Node* n, string tuKhoaThuong, Node* kq[], int& so) {
    if (n == NULL) return;
    if (chuThuong(n->name).find(tuKhoaThuong) != string::npos) {
        kq[so] = n;
        so++;
    }
    thuThapTheoTen(n->firstChild, tuKhoaThuong, kq, so);
    thuThapTheoTen(n->nextSibling, tuKhoaThuong, kq, so);
}

void inMotDong(Node* n) {
    cout << tenHienThi(n) << " - " << n->birthYear << ", " << tenGioiTinh(n->gender)
         << " (" << moTaQuanHeBang(n) << ")\n";
}

Node* chonTheoMa() {
    string ma = docDong("Nhap ma dinh danh (Enter = quay lai): ");
    if (ma == "") return NULL;
    Node* n = timThanhVien(ma);
    if (n == NULL) cout << "  ! Khong tim thay thanh vien co ma '" << ma << "'. Hay thu lai.\n";
    return n;
}

Node* chonTheoTen() {
    string tu = docDong("Nhap ho ten hoac mot phan ho ten (Enter = quay lai): ");
    if (tu == "") return NULL;
    string tuThuong = chuThuong(tu);
    Node* kq[MAX_NODE];
    int so = 0;
    thuThapTheoTen(root, tuThuong, kq, so);
    for (Node* t = dsNgoai; t != NULL; t = t->nextSibling) {
        if (chuThuong(t->name).find(tuThuong) != string::npos) {
            kq[so] = t;
            so++;
        }
    }
    if (so == 0) {
        cout << "  ! Khong tim thay thanh vien nao co ten chua '" << tu << "'. Hay thu lai.\n";
        return NULL;
    }
    if (so == 1) {
        cout << "  Tim thay 1 nguoi: ";
        inMotDong(kq[0]);
        return kq[0];
    }
    cout << "  Co " << so << " nguoi phu hop, hay chon chinh xac:\n";
    for (int i = 0; i < so; i++) {
        cout << "   " << (i + 1) << ". ";
        inMotDong(kq[i]);
    }
    int stt = docSoNguyen("Nhap STT nguoi can chon (0 = tim lai): ", 0, so);
    if (stt == 0) return NULL;
    return kq[stt - 1];
}

Node* chonTheoDanhSach() {
    hienThiBangChon();
    Node* ds[MAX_NODE];
    int tong = layDanhSach(ds);
    if (tong == 0) return NULL;
    int stt = docSoNguyen("Nhap STT thanh vien can chon (0 = quay lai): ", 0, tong);
    if (stt == 0) return NULL;
    return ds[stt - 1];
}

Node* chonThanhVien(string tieuDe, bool chiTrongCay) {
    tieuDe = boDauHaiCham(tieuDe);
    while (true) {
        cout << "\n--- CHON THANH VIEN: " << tieuDe << " ---\n";
        cout << "  1 = Nhap ma dinh danh\n";
        cout << "  2 = Tim theo ho ten (hoac mot phan ho ten)\n";
        cout << "  3 = Xem danh sach thanh vien roi chon\n";
        cout << "  0 = Huy\n";
        int cach = docSoNguyen("Chon cach tim: ", 0, 3);
        if (cach == 0) {
            cout << "  Da huy.\n";
            return NULL;
        }
        Node* n = NULL;
        if (cach == 1) n = chonTheoMa();
        else if (cach == 2) n = chonTheoTen();
        else n = chonTheoDanhSach();
        if (n == NULL) continue;
        if (chiTrongCay && laNguoiNgoai(n)) {
            cout << "  ! " << tenHienThi(n) << " la nguoi nhap gia (khong thuoc cay huyet thong) nen khong\n"
                 << "    the lam cha/me trong cay.";
            if (n->spouse != NULL) cout << " Hay chon vo/chong cua nguoi nay: " << tenHienThi(n->spouse) << ".";
            cout << "\n";
            continue;
        }
        cout << "  => Da chon: " << tenHienThi(n) << "\n";
        return n;
    }
}

void themQuanHeVoChong() {
    Node* a = chonThanhVien("Chon nguoi thu nhat", false);
    if (a == NULL) return;
    Node* b = chonThanhVien("Chon nguoi thu hai", false);
    if (b == NULL) return;
    string loi = kiemTraKetHon(a, b);
    if (loi != "") {
        cout << "  ! " << loi << "\n";
        return;
    }
    ketHon(a, b);
    Node* chong = a;
    Node* vo = b;
    if (a->gender == 'F') {
        chong = b;
        vo = a;
    }
    cout << "  => Da thiet lap: " << chong->name << " la chong cua " << vo->name << ".\n";
}

void taoVoChongMoi() {
    if (tongThanhVien() >= MAX_NODE) {
        cout << "  ! Da dat so thanh vien toi da (" << MAX_NODE << ").\n";
        return;
    }
    Node* a = chonThanhVien("Chon thanh vien da co (nguoi se co them vo/chong)", true);
    if (a == NULL) return;
    if (a->spouse != NULL) {
        cout << "  ! " << a->name << " da co vo/chong la " << a->spouse->name << ".\n";
        return;
    }
    char gt = 'F';
    if (a->gender == 'F') gt = 'M';
    cout << "Nhap thong tin " << (gt == 'F' ? "nguoi vo" : "nguoi chong") << " moi cua " << a->name << ":\n";
    cout << "(Day la thanh vien doc lap, chua co cha/me trong gia pha.)\n";
    Node* moi = nhapThanhVienMoi(NULL, gt);
    if (moi == NULL) {
        cout << "  Da huy.\n";
        return;
    }
    themNgoai(moi);
    ketHon(a, moi);
    cout << "  => Da them " << moi->name << " va thiet lap la " << (gt == 'F' ? "vo" : "chong")
         << " cua " << a->name << ".\n";
}

void huyQuanHeVoChong() {
    Node* a = chonThanhVien("Chon thanh vien can huy quan he vo chong", false);
    if (a == NULL) return;
    if (a->spouse == NULL) {
        cout << "  " << a->name << " chua co vo/chong.\n";
        return;
    }
    Node* b = a->spouse;
    if (!xacNhan("Huy quan he vo chong giua " + a->name + " va " + b->name + " (hai nguoi van o trong gia pha)?")) {
        cout << "  Da huy.\n";
        return;
    }
    huyKetHon(a);
    cout << "  => Da huy quan he vo chong giua " << a->name << " va " << b->name << ".\n";
}

void menuVoChong() {
    if (root == NULL) {
        cout << "  ! Gia pha dang rong.\n";
        return;
    }
    cout << "  1 = Them quan he vo chong giua hai thanh vien da co\n";
    cout << "  2 = Tao thanh vien moi lam vo/chong cua mot thanh vien\n";
    cout << "  3 = Huy quan he vo chong\n";
    cout << "  0 = Quay lai\n";
    int chon = docSoNguyen("Chon: ", 0, 3);
    if (chon == 1) themQuanHeVoChong();
    else if (chon == 2) taoVoChongMoi();
    else if (chon == 3) huyQuanHeVoChong();
}

string tenBacChuCoDiCau(Node* s, Node* m) {
    if (m->gender == 'M') {
        if (s->gender == 'F') return "co";
        if (s->birthYear < m->birthYear) return "bac";
        if (s->birthYear > m->birthYear) return "chu";
        return "bac/chu (cung nam sinh voi cha nen chua phan biet duoc)";
    }
    if (s->gender == 'M') return "cau";
    return "di";
}

string tenAnhChiEm(Node* a, Node* b, bool ho) {
    if (a->birthYear < b->birthYear) {
        if (ho) return (a->gender == 'M') ? "anh ho" : "chi ho";
        return (a->gender == 'M') ? "anh trai" : "chi gai";
    }
    if (a->birthYear > b->birthYear) {
        if (ho) return "em ho";
        return (a->gender == 'M') ? "em trai" : "em gai";
    }
    if (ho) return "anh/chi/em ho (cung nam sinh nen chua phan biet duoc)";
    return "anh/chi/em (cung nam sinh nen chua phan biet duoc)";
}

void xacDinhChaMe(Node* n, Node*& cha, Node*& me, bool& chaSuyRa, bool& meSuyRa) {
    cha = NULL;
    me = NULL;
    chaSuyRa = false;
    meSuyRa = false;
    Node* tp = timCha(root, n);
    if (tp == NULL) return;
    if (tp->gender == 'M') {
        cha = tp;
        me = tp->spouse;
        meSuyRa = true;
    } else {
        me = tp;
        cha = tp->spouse;
        chaSuyRa = true;
    }
}

bool xacDinhQuanHe(Node* a, Node* b, string& ten, string& coSo) {
    if (a == b) {
        ten = "cung mot nguoi";
        coSo = "hai lua chon trung nhau";
        return true;
    }
    if (a->spouse == b) {
        ten = (a->gender == 'M') ? "chong" : "vo";
        coSo = "luu truc tiep (quan he vo chong)";
        return true;
    }
    Node* tpA = timCha(root, a);
    Node* tpB = timCha(root, b);
    if (tpB != NULL && tpB->spouse == a) {
        ten = (a->gender == 'M') ? "cha" : "me";
        coSo = "suy ra: la vo/chong cua " + tpB->name + ", nguoi duoc ghi la cha/me cua " + b->name;
        return true;
    }
    if (tpA != NULL && tpA->spouse == b) {
        ten = (a->gender == 'M') ? "con trai" : "con gai";
        coSo = "suy ra: " + b->name + " la vo/chong cua " + tpA->name + ", nguoi duoc ghi la cha/me cua " + a->name;
        return true;
    }
    if (laNguoiNgoai(a) || laNguoiNgoai(b)) {
        ten = "mot trong hai nguoi la nguoi nhap gia, gia pha chua ghi cha/me cua nguoi do nen chi biet quan he vo/chong";
        return false;
    }
    Node* l = timLCA(root, a, b);
    int theHeL = tinhTheHe(root, l, 1);
    int da = tinhTheHe(root, a, 1) - theHeL;
    int db = tinhTheHe(root, b, 1) - theHeL;
    coSo = "suy ra tu cay gia pha";
    if (da == 0) {
        if (db == 1) {
            ten = (a->gender == 'M') ? "cha" : "me";
            coSo = "luu truc tiep (cha/me - con trong cay)";
        } else if (db == 2) {
            string ben = (tpB->gender == 'M') ? "noi" : "ngoai";
            ten = ((a->gender == 'M') ? "ong " : "ba ") + ben;
        } else if (db == 3) {
            string ben = (tpB->gender == 'M') ? "noi" : "ngoai";
            ten = ((a->gender == 'M') ? "cu ong (ben " : "cu ba (ben ") + ben + ")";
        } else {
            ten = "to tien (cach " + soSangChuoi(db) + " doi)";
        }
        return true;
    }
    if (db == 0) {
        if (da == 1) {
            ten = (a->gender == 'M') ? "con trai" : "con gai";
            coSo = "luu truc tiep (cha/me - con trong cay)";
        } else if (da == 2) {
            ten = (tpA->gender == 'M') ? "chau noi" : "chau ngoai";
        } else if (da == 3) {
            ten = "chat";
        } else {
            ten = "hau due (cach " + soSangChuoi(da) + " doi)";
        }
        return true;
    }
    if (da == 1 && db == 1) {
        ten = tenAnhChiEm(a, b, false);
        coSo = "suy ra: cung cha/me trong cay (" + tpA->name + ")";
        return true;
    }
    if (da == 1 && db == 2) {
        ten = tenBacChuCoDiCau(a, tpB);
        coSo = "suy ra: " + a->name + " la anh/chi/em cua " + tpB->name + ", nguoi duoc ghi la cha/me cua " + b->name;
        return true;
    }
    if (da == 2 && db == 1) {
        ten = "chau";
        coSo = "suy ra: " + a->name + " la con cua " + tpA->name + ", anh/chi/em cua " + b->name
               + "; " + a->name + " goi " + b->name + " la " + tenBacChuCoDiCau(b, tpA);
        return true;
    }
    if (da == 2 && db == 2) {
        ten = tenAnhChiEm(a, b, true);
        coSo = "suy ra: cha/me cua hai nguoi la anh/chi/em";
        return true;
    }
    ten = "ho hang xa, chuong trinh chua xac dinh cach goi (" + a->name + " cach to tien chung "
          + soSangChuoi(da) + " doi, " + b->name + " cach " + soSangChuoi(db) + " doi)";
    return false;
}

void traCuuHaiNguoi() {
    if (tongThanhVien() == 0) {
        cout << "  ! Gia pha dang rong.\n";
        return;
    }
    Node* a = chonThanhVien("Chon nguoi A", false);
    if (a == NULL) return;
    Node* b = chonThanhVien("Chon nguoi B", false);
    if (b == NULL) return;
    if (a == b) {
        cout << "  ! Hai lua chon la cung mot nguoi: " << a->name << ".\n";
        return;
    }
    string ten, coSo;
    bool xacDinh = xacDinhQuanHe(a, b, ten, coSo);
    if (xacDinh) {
        cout << "  " << a->name << " la " << ten << " cua " << b->name << ".\n";
        cout << "    Co so: " << coSo << "\n";
        string ten2, coSo2;
        if (xacDinhQuanHe(b, a, ten2, coSo2))
            cout << "  Nguoc lai: " << b->name << " la " << ten2 << " cua " << a->name << ".\n";
    } else {
        cout << "  Chua the xac dinh quan he giua " << a->name << " va " << b->name << ": " << ten << ".\n";
    }
    if (!laNguoiNgoai(a) && !laNguoiNgoai(b))
        inDuongQuanHe(a, b, !xacDinh);
}

Node* themVoChongMau(Node* nguoi, string id, string ten, int nam, char gt) {
    if (timThanhVien(id) != NULL) return NULL;
    Node* moi = taoNode(id, ten, nam, gt);
    if (kiemTraKetHon(nguoi, moi) != "") {
        delete moi;
        return NULL;
    }
    themNgoai(moi);
    ketHon(nguoi, moi);
    return moi;
}

void inChaMe(string nhan, Node* n, bool suyRa) {
    cout << "  " << nhan;
    if (n == NULL) cout << "chua xac dinh (gia pha chua co du lieu)\n";
    else cout << tenHienThi(n) << (suyRa ? "  [suy ra: vo/chong cua cha/me trong cay]" : "  [luu truc tiep]") << "\n";
}

void xemQuanHeThanhVien() {
    if (tongThanhVien() == 0) {
        cout << "  ! Gia pha dang rong.\n";
        return;
    }
    Node* n = chonThanhVien("Chon thanh vien can xem quan he", false);
    if (n == NULL) return;
    bool ngoai = laNguoiNgoai(n);
    Node* tp = timCha(root, n);

    cout << "\n===== THONG TIN VA QUAN HE CUA " << n->name << " =====\n";
    cout << "  Ma dinh danh : " << n->id << "\n";
    cout << "  Ho ten       : " << n->name << "\n";
    cout << "  Nam sinh     : " << n->birthYear << "\n";
    cout << "  Gioi tinh    : " << tenGioiTinh(n->gender) << "\n";
    if (ngoai) cout << "  The he       : khong thuoc cay huyet thong (nguoi nhap gia)\n";
    else cout << "  The he       : " << tinhTheHe(root, n, 1) << "\n";

    Node* cha;
    Node* me;
    bool chaSR, meSR;
    xacDinhChaMe(n, cha, me, chaSR, meSR);
    inChaMe("Cha          : ", cha, chaSR);
    inChaMe("Me           : ", me, meSR);

    cout << "  Vo/chong     : ";
    if (n->spouse == NULL) cout << "chua co\n";
    else cout << tenHienThi(n->spouse) << " (" << (n->spouse->gender == 'M' ? "chong" : "vo") << ")  [luu truc tiep]\n";

    cout << "  Cac con      : ";
    int soCon = 0;
    Node* c;
    for (c = n->firstChild; c != NULL; c = c->nextSibling) {
        cout << (soCon == 0 ? "" : "                 ") << tenHienThi(c) << " (" << (c->gender == 'M' ? "con trai" : "con gai")
             << ")  [luu truc tiep]\n";
        soCon++;
    }
    if (n->spouse != NULL) {
        for (c = n->spouse->firstChild; c != NULL; c = c->nextSibling) {
            cout << (soCon == 0 ? "" : "                 ") << tenHienThi(c) << " (" << (c->gender == 'M' ? "con trai" : "con gai")
                 << ")  [suy ra: con cua vo/chong " << n->spouse->name << " trong cay]\n";
            soCon++;
        }
    }
    if (soCon == 0) cout << "chua co con trong du lieu\n";

    cout << "  Anh chi em   : ";
    if (ngoai) {
        cout << "chua xac dinh (chua co du lieu cha/me)\n";
    } else if (tp == NULL) {
        cout << "khong co (nguoi goc, chua co du lieu cha/me)\n";
    } else {
        int dem = 0;
        for (c = tp->firstChild; c != NULL; c = c->nextSibling) {
            if (c == n) continue;
            cout << (dem == 0 ? "" : "                 ") << tenHienThi(c) << " (" << tenAnhChiEm(c, n, false)
                 << ")  [suy ra: cung cha/me " << tp->name << "]\n";
            dem++;
        }
        if (dem == 0) cout << "khong co (con mot trong du lieu)\n";
    }

    cout << "  Ong/ba       : ";
    Node* ong = NULL;
    if (tp != NULL) ong = timCha(root, tp);
    if (ong == NULL) {
        cout << "chua xac dinh (gia pha chua co du lieu ong/ba)\n";
    } else {
        string ten, coSo;
        xacDinhQuanHe(ong, n, ten, coSo);
        cout << tenHienThi(ong) << " (" << ten << ")  [suy ra tu cay]\n";
    }

    cout << "  Co/di/chu/bac/cau: ";
    if (tp == NULL) {
        cout << "chua xac dinh (chua co du lieu cha/me cua " << n->name << ")\n";
    } else if (ong == NULL) {
        cout << "chua xac dinh (chua co du lieu cha/me cua " << tp->name << ", nen chua biet anh/chi/em cua nguoi nay)\n";
    } else {
        int dem = 0;
        for (c = ong->firstChild; c != NULL; c = c->nextSibling) {
            if (c == tp) continue;
            cout << (dem == 0 ? "" : "                     ") << tenHienThi(c) << " ("
                 << tenBacChuCoDiCau(c, tp) << ")  [suy ra: anh/chi/em cua " << tp->name << "]\n";
            dem++;
        }
        if (dem == 0) cout << "khong co (" << tp->name << " la con mot trong du lieu)\n";
    }
    if (tp != NULL) cout << "  (Ho hang ben cha/me con lai: chua xac dinh - gia pha chi ghi nhanh cua "
                         << tp->name << ".)\n";
}

void timTheoTenNgoai(string tuKhoa, int& soKetQua) {
    for (Node* t = dsNgoai; t != NULL; t = t->nextSibling) {
        if (t->name.find(tuKhoa) != string::npos) {
            inThongTin(t);
            soKetQua++;
        }
    }
}

void thongKeNgoai(int& nam, int& nu, int& namNho) {
    for (Node* t = dsNgoai; t != NULL; t = t->nextSibling) {
        if (t->gender == 'M') nam++;
        else nu++;
        if (t->birthYear < namNho) namNho = t->birthYear;
    }
}

void inNguoiSinhNamNgoai(int nam, bool& laDauTien) {
    for (Node* t = dsNgoai; t != NULL; t = t->nextSibling) {
        if (t->birthYear == nam) {
            if (!laDauTien) cout << ", ";
            cout << t->name << " [" << t->id << "]";
            laDauTien = false;
        }
    }
}

int demCoVoChongTrongCay(Node* n) {
    if (n == NULL) return 0;
    int dem = 0;
    if (n->spouse != NULL) dem = 1;
    return dem + demCoVoChongTrongCay(n->firstChild) + demCoVoChongTrongCay(n->nextSibling);
}

int demCapVoChong() {
    int dem = demCoVoChongTrongCay(root);
    for (Node* t = dsNgoai; t != NULL; t = t->nextSibling) {
        if (t->spouse != NULL) dem++;
    }
    return dem / 2;
}
