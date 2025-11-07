# 📚 ĐỒ ÁN NHẬP MÔN LẬP TRÌNH  
## QUẢN LÝ THƯ VIỆN  

**Sinh viên thực hiện:** Bùi Hưng Khang  
**MSSV:** 25810006   
**Trường:** Đại học Khoa học Tự nhiên – Khoa Công nghệ Thông tin  
**Thời gian:** 11/2025  

---

## MỤC TIÊU  
Xây dựng hệ thống **Quản lý Thư viện**, hỗ trợ người quản lý thực hiện các nghiệp vụ cơ bản như: quản lý sách, độc giả, lập phiếu mượn – trả và thống kê dữ liệu.

---

## CẤU TRÚC DỰ ÁN
    QuanLyThuVien/
    ├── main.c
    ├── docGia.c / docGia.h # Quản lý thông tin độc giả
    ├── sach.c / sach.h # Quản lý thông tin sách
    ├── phieuMuonTra.c / phieuMuonTra.h # Quản lý phiếu mượn và trả sách
    ├── thongKe.c / thongKe.h # Các chức năng thống kê
    ├── time_helpers.c / time_helpers.h # Xử lý thời gian (ngày, tháng, năm)
    ├── currency_vnd.c / currency_vnd.h # Định dạng tiền tệ VNĐ
    ├── constants.h # Các hằng số chung
    ├── sach.txt # Dữ liệu sách
    ├── docgia.txt # Dữ liệu độc giả
    ├── phieu.txt # Dữ liệu phiếu mượn – trả
    └── README.md

## CÁC CHỨC NĂNG CHÍNH  

### 1. Quản lý Độc Giả  
- Xem danh sách độc giả  
- Thêm, sửa, xóa độc giả  
- Tìm kiếm độc giả theo **CCCD** hoặc **họ tên**

### 2. Quản lý Sách  
- Xem danh sách sách  
- Thêm, sửa, xóa sách  
- Tìm kiếm sách theo **ISBN** hoặc **tên sách**

### 3. Lập Phiếu Mượn Sách  
- Tạo mã phiếu tự động: `PYYYYMMDD_XXXX`  
- Lưu thông tin mượn: ngày mượn, ngày trả dự kiến, số sách mượn, ISBN…  
- Khi mượn sách, số lượng sách trong kho sẽ tự động giảm.

### 4. Lập Phiếu Trả Sách  
- Cập nhật ngày trả thực tế  
- Tính tiền phạt khi trả trễ hoặc mất sách  
- Khi trả đúng hạn, số lượng sách được hoàn lại vào kho.

### 5. Thống kê  
- Tổng số sách trong thư viện  
- Sách theo thể loại  
- Tổng số độc giả và phân theo giới tính  
- Danh sách sách đang được mượn  
- Độc giả trả trễ hạn  

---

## CÁC CHỨC NĂNG PHỤ TRỢ  

- **Định dạng tiền tệ**: `format_vnd()` → Ví dụ: `36500` → `36,500 VND`  
- **Xử lý ngày tháng**:  
  - `change_date("DD/MM/YYYY") → YYYYMMDD`  
  - `format_date(YYYYMMDD) → DD/MM/YYYY`  
  - `between_days()` – tính số ngày trễ  

  - `add_days()` – cộng ngày tự động
