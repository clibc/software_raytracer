#include "headers.h"

#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT 720

#define PUTPIXEL(r, g, b) {                     \
        *pixel = (u8)b;                      \
        ++pixel;                                \
        *pixel = (u8)g;                      \
        ++pixel;                                \
        *pixel = (u8)r;                      \
        ++pixel;                                \
        *pixel = 0;                             \
        ++pixel;                                \
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); 

static BITMAPINFO bitmap_info;
static void* bitmap_memory;

void Win32UpdateWindow(HDC device_context,
                       s32 X, s32 Y,
                       s32 width, s32 height) {
    StretchDIBits(device_context,
                   X, Y, width, height,
                   X, Y, width, height,
                   bitmap_memory, &bitmap_info, DIB_RGB_COLORS, SRCCOPY);
}

s32 WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    (void)hPrevInstance;
    (void)pCmdLine;

    char* name = "SoftRayTracer";
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = name;
    RegisterClass(&wc);
    
    HWND hwnd = CreateWindowEx(0, name, name, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);
    
    if (hwnd == NULL) return 0;
    ShowWindow(hwnd, nCmdShow);

    // Create DIB thing
    RECT client_rect = {0};
    GetClientRect(hwnd, &client_rect);
    u32 width  = client_rect.right - client_rect.left;
    u32 height = client_rect.bottom - client_rect.top;
    
    bitmap_info.bmiHeader.biSize = sizeof(bitmap_info.bmiHeader);
    bitmap_info.bmiHeader.biWidth = width;
    bitmap_info.bmiHeader.biHeight = height;
    bitmap_info.bmiHeader.biPlanes = 1;
    bitmap_info.bmiHeader.biBitCount = 32;
    bitmap_info.bmiHeader.biCompression = BI_RGB;

    u32 pixel_count = width * height;
    bitmap_memory = VirtualAlloc(NULL, pixel_count * 4, MEM_COMMIT, PAGE_READWRITE);

    v3 ro = {0,0,-1.0f};
    v3 s  = {0,0,5};
    float radius = 2;
    v3 resolution = { (float)width, (float)height, 0 };

    ((u32*)bitmap_memory)[0] = 0x00ff0000;
    ((u32*)bitmap_memory)[1] = 0x00ff0000;
    ((u32*)bitmap_memory)[2] = 0x00ff0000;
    

#if 1
    // fill pixels
    u8* row  = (u8*)bitmap_memory;
    u32 pitch = width * 4;
    for(u32 y = 0; y < height; ++y) {
        u8* pixel = row;
        for(u32 x = 0; x < width; ++x) {
            v3 uv = { (float)x/resolution.x, (float)y/resolution.y, 0 };
            uv.x -= 0.5f;
            uv.x *= resolution.x/resolution.y;
            uv.y -= 0.5f;
            
            v3 col = {0, 0, 0};
            v3 rd = (uv - ro).Normalized();
            v3  p = ro + abs((s - ro).Dot(rd)) * rd;
            f32 d = (p - s).SqrLength();
            
            if(d < radius * radius) {
                // hit
                f32 rad = p.Length() - sqrtf(radius*radius - d);
                v3  t   = ro + rad*rd;
                v3 n = (t-s).Normalized();

                col = n;
            }
            else {
                // miss
            }

            col.x = max(0, col.x);
            col.y = max(0, col.y);
            col.z = max(0, col.z);
            col *= 255;
            PUTPIXEL(col.x, col.y, col.z);
        }
        row += pitch;
    }
#endif
    
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
        const u32 X = ps.rcPaint.right;
        const u32 Y = ps.rcPaint.bottom;
        Win32UpdateWindow(hdc, 0, 0, X, Y);

        EndPaint(hwnd, &ps);
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
