#include "headers.h"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 500

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

    v3 CameraLookat = v3(0, 0, 5);
    v3 CameraPos    = {0, 1, -1};//{2, 1, -1};

    v3 CameraZ = (CameraLookat - CameraPos).Normalize();
    v3 CameraX = ((v3(0,1,0)).Cross(CameraZ)).Normalize();
    v3 CameraY = CameraZ.Cross(CameraX).Normalize();

    m4 CameraToWorld = {};

    CameraToWorld.SetRow(0, CameraX.x, CameraX.y, CameraX.z, 0);
    CameraToWorld.SetRow(1, CameraY.x, CameraY.y, CameraY.z, 0);
    CameraToWorld.SetRow(2, CameraZ.x, CameraZ.y, CameraZ.z, 0);
    CameraToWorld.SetRow(3, CameraPos.x, CameraPos.y, CameraPos.z, 1);

    CameraToWorld.Inverse().Print();
    
    world.spheres   = (Sphere*)VirtualAlloc(NULL, MAX_OBJECT_COUNT * sizeof(Sphere), MEM_COMMIT, PAGE_READWRITE);
    world.planes   = (Plane*)VirtualAlloc(NULL, MAX_OBJECT_COUNT * sizeof(Plane), MEM_COMMIT, PAGE_READWRITE);
    world.materials = (Material*)VirtualAlloc(NULL, MAX_OBJECT_COUNT * sizeof(Material), MEM_COMMIT, PAGE_READWRITE);
    world.positions  = (v3*)VirtualAlloc(NULL, MAX_OBJECT_COUNT * sizeof(v3), MEM_COMMIT, PAGE_READWRITE);

    Sphere sphere;
    sphere.position = 0;
    sphere.material = 0;
    sphere.radius   = 1.0f;
    Plane plane;
    plane.position = 1;
    plane.material = 1;
    plane.normal   = v3(0, 1, 0);
    plane.offset   = 0.0f;
    Sphere sphere2;
    sphere2.position = 1;
    sphere2.material = 0;
    sphere2.radius   = 3.0f;
    Sphere sphere3;
    sphere3.position = 2;
    sphere3.material = 0;
    sphere3.radius   = 2.0f;

    Material m0;
    Material m1;
    m0.color = v3(1, 0, 1);
    m1.color = v3(1, 1, 0);

    world.sphere_count = 3;
    world.plane_count  = 1;
    world.positions[0] = v3(-3, 1, 5);
    world.positions[1] = v3(5, 1, 5);
    world.positions[2] = v3(0, -1, 2);
    world.materials[0] = m0;
    world.materials[1] = m1;
    world.spheres[0] = sphere;
    world.spheres[1] = sphere2;
    world.spheres[2] = sphere3;
    world.planes[0] = plane;

    v3 resolution = { (float)width, (float)height, 0 };
    u8* row  = (u8*)bitmap_memory;
    u32 pitch = width * 4;
    for(u32 y = 0; y < height; ++y) {
        u8* pixel = row;
        for(u32 x = 0; x < width; ++x) {
            v3 uv = { ((f32)x + 0.5f)/resolution.x, ((f32)y + 0.5f)/resolution.y, 0 };
            uv.x = (2.0f * uv.x - 1) * (resolution.x / resolution.y);
            uv.y = 2.0f * uv.y - 1;
            uv.z = 1;

            v4 PixelWorld = CameraToWorld * v4(uv, 1.0f);
            v3 PixelCoord = v3(PixelWorld.x, PixelWorld.y, PixelWorld.z);
            
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
