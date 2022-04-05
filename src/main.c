#include "headers.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static BITMAPINFO bitmap_info;
static void* bitmap_memory;

void Win32UpdateWindow(HDC device_context,
                       int32 X, int32 Y,
                       int32 width, int32 height) {
    StretchDIBits(device_context,
                   X, Y, width, height,
                   X, Y, width, height,
                   bitmap_memory, &bitmap_info, DIB_RGB_COLORS, SRCCOPY);
}

void TestCode() {
    vec3 v = vec3_make(2);
    vec3 v1 = vec3_mulf(v, 3.0f);
    vec3 mulv = vec3_mulv(v, v1);
    vec3 divf = vec3_mulf(mulv, 0.5f);

    vec3 add = vec3_addv(divf, mulv);
    add = vec3_subf(add, 10.0f);
    add = vec3_addf(add, 9.0f);
    
    int a = 32;
}

int32 WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    (void)hPrevInstance;
    (void)pCmdLine;

    TestCode();
    
    char* name = "SoftRayTracer";
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = name;
    RegisterClass(&wc);
    
    HWND hwnd = CreateWindowEx(0, name, name, WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT, 800, 460, NULL, NULL, hInstance, NULL);

    printfl("Some bullshit");
    
    if (hwnd == NULL) return 0;
    ShowWindow(hwnd, nCmdShow);

    // Create DIB thing
    RECT client_rect = {0};
    GetClientRect(hwnd, &client_rect);
    
    uint32 width  = client_rect.right - client_rect.left;
    uint32 height = client_rect.bottom - client_rect.top;
    
    bitmap_info.bmiHeader.biSize = sizeof(bitmap_info.bmiHeader);
    bitmap_info.bmiHeader.biWidth = width;
    bitmap_info.bmiHeader.biHeight = -(int)height; // for topdown upper-left pixel order
    bitmap_info.bmiHeader.biPlanes = 1;
    bitmap_info.bmiHeader.biBitCount = 32;
    bitmap_info.bmiHeader.biCompression = BI_RGB;

    uint32 pixel_count = width * height;
    bitmap_memory = VirtualAlloc(NULL, pixel_count * 4, MEM_COMMIT, PAGE_READWRITE);

    // fill pixels
    uint8* row  = (uint8*)bitmap_memory;
    uint32 pitch = width * 4;
    for(uint32 y = 0; y < height; ++y) {
        uint8* pixel = row;
        for(uint32 x = 0; x < width; ++x) {
            *pixel = 0;
            ++pixel;
            *pixel = (uint8)((float)(((float)x/(float)width)*100.0f));
            ++pixel;
            *pixel = 0;
            ++pixel;
            *pixel = 0;
            ++pixel;
        }
        row += pitch;
    }
    
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        const uint32 X = ps.rcPaint.right;
        const uint32 Y = ps.rcPaint.bottom;
        Win32UpdateWindow(hdc, 0, 0, X, Y);

        EndPaint(hwnd, &ps);
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
