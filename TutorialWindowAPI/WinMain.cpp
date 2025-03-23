
#include <sstream>
#include <Windows.h>

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
        L"1-2 Drawing Shapes",
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
    return static_cast<int>(msg.wParam);
}

    // Write the Window procesure 
    LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lparam)
    {
        switch (message)
        {
        case WM_LBUTTONDOWN:
            {
                HDC hdc = nullptr;
                hdc = GetDC(hWnd);
                Rectangle (hdc, 0, 0, 100, 100);
                ReleaseDC (hWnd, hdc); // must release the DC once you get it (like new delete) 
                break;
            }
        case WM_PAINT: // using window message to draw permernent regtangles.  
            {
                PAINTSTRUCT ps; // Drawing the shapes no matter how screen size is.
                HDC hdc = BeginPaint(hWnd, &ps);

                HPEN bluePen = CreatePen (PS_DOT, 1, RGB(0,0,255));
                //Rectangle (hdc, 0, 0, 100, 100);
                SetPixel (hdc, 50, 50, RGB(255,0,0));
                LineTo (hdc, 100, 110);
                DeleteObject (bluePen);

                HBRUSH hatchbrush = CreateHatchBrush(HS_CROSS, RGB(0, 255,0));
                HBRUSH oldBrush = (HBRUSH)SelectObject (hdc, hatchbrush); 
                Rectangle (hdc, 0 ,0, 200,200);
                DeleteObject (hatchbrush);
                SelectObject (hdc, oldBrush);
                
                EndPaint(hWnd, &ps);
            }
        case WM_KEYDOWN:
            {
                std::wostringstream oss;
                oss<< "Virtual Key = " << wParam << ", Extra = " <<std::hex << lparam << std::endl;
                OutputDebugString(oss.str().c_str());
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
