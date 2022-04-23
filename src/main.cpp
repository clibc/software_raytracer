#include "headers.h"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

#define PUTPIXEL(r, g, b) {                     \
        *pixel = (u8)b;                         \
        ++pixel;                                \
        *pixel = (u8)g;                         \
        ++pixel;                                \
        *pixel = (u8)r;                         \
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

void test() {
    m4 m = {};
    
    for(int i = 0; i < 16; ++i) {
        m[i] = (float)i;
    }

    m4 m2 = {};

    m2 = m;

    v3 vec = {0,1,0};

    v3 neeew = m2*vec;
    
    
//    DebugLog("test %f", 0.0f);
    return;
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

    test();
    
    v3 CameraLookat = v3(0,0,5);
    v3 CameraPos    = {2, 5, -1};

    v3 CameraZ = (CameraPos - CameraLookat).Normalize();
    v3 CameraX = CameraZ.Cross({0,1,0}).Normalize();
    v3 CameraY = CameraX.Cross(CameraZ).Normalize();
    const f32 FilmDistance = 2.0f;
    v3 FilmCenter = CameraPos - CameraZ * FilmDistance;

    m4 CameraToWorld = {};

    CameraToWorld.SetRow(0, CameraX.x, CameraX.y, CameraX.z, 0);
    CameraToWorld.SetRow(1, CameraY.x, CameraY.y, CameraY.z, 0);
    CameraToWorld.SetRow(2, CameraZ.x, CameraZ.y, CameraZ.z, 0);
    CameraToWorld.SetRow(3, CameraPos.x, CameraPos.y, CameraPos.z, 0);

    v3 resolution = { (float)width, (float)height, 0 };
    // fill pixels
    u8* row  = (u8*)bitmap_memory;
    u32 pitch = width * 4;
    for(u32 y = 0; y < height; ++y) {
        u8* pixel = row;
        for(u32 x = 0; x < width; ++x) {
            v3 uv = { ((f32)x + 0.5f)/resolution.x, ((f32)y + 0.5f)/resolution.y, 0 };
            uv.x = (2.0f * uv.x - 1) * (resolution.x / resolution.y);
            uv.y = 1 - 2.0f * uv.y;
            uv.z = -2;
            //v3 PixelCoord = FilmCenter + (CameraX * uv.x) + (CameraY * uv.y);
            v3 PixelCoord = CameraToWorld * uv;
            
            v3 rd = (PixelCoord - CameraPos).Normalize();
            v3 col = RaycastWorld(CameraPos, rd);
            
            col.x = max(0, col.x);
            col.y = max(0, col.y);
            col.z = max(0, col.z);
            col *= 255;
            PUTPIXEL(col.x, col.y, col.z);
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
        const u32 X = ps.rcPaint.right;
        const u32 Y = ps.rcPaint.bottom;
        Win32UpdateWindow(hdc, 0, 0, X, Y);

        EndPaint(hwnd, &ps);
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
