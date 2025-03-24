
#include <complex>
#include <Windows.h>
#include <gdiplus.h>
#include <sstream>
#pragma comment (lib, "gdiplus.lib")

using namespace Gdiplus; 

const wchar_t gClassName[]= L"MyWindowsClass";
LRESULT CALLBACK WindowProc(
    HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPSTR     lpCmdLine,
   _In_ int       nCmdShow
)
{
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup (&gdiplusToken, &gdiplusStartupInput, nullptr);
    HWND hWnd;
    WNDCLASSEX wc;

    // register the window class
    ZeroMemory (&wc, sizeof (WNDCLASSEX)); // intialise the memory as 0. 

    // initialising the windows.
    wc.style = CS_HREDRAW | CS_VREDRAW; // redraw when the window is moved. 
    wc.lpszClassName = gClassName;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpfnWndProc = WindowProc;
    wc.cbSize = sizeof (WNDCLASSEX);

    if (!RegisterClassEx (&wc))
    {
        // if windows has been failed to be loaded, send the error message 
        MessageBox (
            nullptr, L"Failed to register the window class.\n",L"Error",
            MB_ICONEXCLAMATION | MB_OK
    );
        return 0;
    }

    // Generate the windows
    hWnd = CreateWindowEx(NULL,
        gClassName,
        L"1-3",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        640,
        480,
        NULL,
        NULL,
        hInstance,
        NULL);

    if (hWnd == nullptr)
    {
        MessageBox (
            nullptr, L"Failed to create the window class.\n",L"Error",
            MB_ICONEXCLAMATION | MB_OK
            );
        return 0; 
    }
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // message handles 
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    Gdiplus::GdiplusShutdown(gdiplusToken); 
    return static_cast<int>(msg.wParam);
}

// get the text with the font in the window. 
void OnPaint (HWND hwnd)
{
    HDC hdc;
    PAINTSTRUCT ps;
    hdc = BeginPaint(hwnd, &ps);

    Graphics graphic(hdc);
    Pen pen (Color(255,0, 0, 255));
    graphic.DrawLine(&pen, 0, 0, 100, 100);

    SolidBrush brush(Color(255, 0, 0, 255));
    FontFamily fontFamily(L"Arial");
    Font font (&fontFamily, 24, FontStyleRegular, UnitPixel);
    PointF pointF(200.f, 200.f);
    graphic.DrawString(L"This is the test string", -1 ,&font, pointF, &brush);

    EndPaint(hwnd, &ps);
}

// get the shiroko.jpg file and display it on the window.
void GetPic (HWND hwnd)
{
    HDC hdc;
    PAINTSTRUCT ps;

    hdc = BeginPaint(hwnd, &ps);
    Graphics graphic(hdc);

    Image image(L"Shiroko.jpg");

    //Draw the image with the rescaling. 
    int x = ps.rcPaint.left;
    int y = ps.rcPaint.top;
    int w = ps.rcPaint.right - ps.rcPaint.left;
    int h = ps.rcPaint.bottom - ps.rcPaint.top;
    graphic.DrawImage(&image, x, y, w, h);
    
    //draw the image with the original size.
    // graphic.DrawImage(&image, 120, 10, image.GetWidth(), image.GetHeight());
    
    EndPaint(hwnd, &ps);
}


    // Write the Window procesure 
    LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lparam)
    {
        switch (message)
        {

        case WM_LBUTTONDOWN:
            {
                break;
            }
        case WM_PAINT: // using window message to draw permernent regtangles.  
            {
                GetPic (hWnd);
                break; 
            }
        case WM_KEYDOWN:
            {
                /*std::ostringstream oss;
                oss<< "Virtual Key = " << wParam << ", Extra = " <<std::hex << lparam << std::endl;
                OutputDebugString(oss.str().c_str());*/
                break; 
            }

        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lparam);
        }
    return 0; 
    }

// window area vs client area? 
