#include <graphics.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

// Hàm vẽ mảng dưới dạng các cột
void drawArray(int arr[], int size, int current = -1, int swapIdx = -1) {
    cleardevice(); // Xóa màn hình
    int width = 1280;
    int height = 720;
    int barWidth = width / size;

    // Tìm giá trị lớn nhất để tỷ lệ chiều cao
    int maxVal = arr[0];
    for(int i = 1; i < size; i++) {
        if(arr[i] > maxVal)
            maxVal = arr[i];
    }

    for(int i = 0; i < size; i++) {
        // Tính chiều cao của cột
        int barHeight = (arr[i] * (height - 100)) / maxVal; // 100 pixel để lề

        // Xác định vị trí của cột
        int x = i * barWidth;
        int y = height - barHeight;

        // Đặt màu sắc
        if(i == current || i == swapIdx) {
            setfillstyle(SOLID_FILL, RED); // Các cột đang được so sánh sẽ đỏ
        }
        else {
            setfillstyle(SOLID_FILL, BLUE); // Các cột còn lại màu xanh dương
        }

        // Vẽ cột
        bar(x, y, x + barWidth - 2, height);

        // Hiển thị giá trị trên cột
        char buffer[4];
        sprintf(buffer, "%d", arr[i]);
        setcolor(WHITE);
        outtextxy(x + barWidth / 4, y - 20, buffer); // Hiển thị giá trị lên trên cột
    }

    delay(500); // Độ trễ để quan sát quá trình (500 mili giây)
}
int main() {
    // Khởi tạo mảng ngẫu nhiên
    const int SIZE = 10;
    int arr[SIZE];
    srand(time(0));

    for(int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 100 + 1; // Giá trị từ 1 đến 100
    }

    // Khởi tạo đồ họa
    initwindow(1289, 720, "Bubble sort"); // Đường dẫn đến thư mục chứa BGI, để trống nếu đã cài đặt đúng

    // Vẽ mảng ban đầu
    drawArray(arr, SIZE);
    
    // Thực hiện Bubble Sort với trực quan hóa
    bool swapped;
    for(int i = 0; i < SIZE - 1; i++) {
        swapped = false;
        for(int j = 0; j < SIZE - i - 1; j++) {
            // Vẽ các cột đang so sánh
            drawArray(arr, SIZE, j, j+1);

            if(arr[j] > arr[j+1]) {
                // Hoán đổi nếu cần
                std::swap(arr[j], arr[j+1]);
                swapped = true;

                // Vẽ lại sau khi hoán đổi
                drawArray(arr, SIZE, j, j+1);
            }
        }
        // Nếu không có hoán đổi nào, mảng đã được sắp xếp
        if(!swapped)
            break;
    }

    // Vẽ mảng sau khi sắp xếp
    drawArray(arr, SIZE);
    setcolor(RED);
    outtextxy(10, 10, (char*)"Bubble Sort Completed!");

    // Chờ người dùng đóng cửa sổ
    getch();
    closegraph();
    return 0;
}
