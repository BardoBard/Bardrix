//
// Created by Bardio on 20/04/2024.
//

#include "window.h"

#ifdef _WIN32

bardrix::window::window(const char* title, int width, int height) {
    if (title == nullptr || title[0] == '\0')
        title_ = "Bardrix Window";
    else
        title_ = title;

    width_ = width > 0 ? width : -width;
    height_ = height > 0 ? height : -height;
    back_buffer_.resize(width_ * height_);
    front_buffer_.resize(width_ * height_);

    bmi_.bmiHeader.biSize = sizeof(bmi_.bmiHeader);
    bmi_.bmiHeader.biWidth = width_;
    bmi_.bmiHeader.biHeight = -height_; // top-down
    bmi_.bmiHeader.biPlanes = 1;
    bmi_.bmiHeader.biBitCount = 32; // 32 bit color RRGGBBAA
    bmi_.bmiHeader.biCompression = BI_RGB;
}

bardrix::window::~window() {
    DestroyWindow(hwnd_);
}

int bardrix::window::get_width() const {
    return width_;
}

int bardrix::window::get_height() const {
    return height_;
}

const char* bardrix::window::get_title() const {
    return title_;
}

bool bardrix::window::show(int x, int y) {

    WNDCLASS wc = {};
    wc.lpfnWndProc = window_proc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = title_;
    RegisterClass(&wc);

    hwnd_ = CreateWindowEx(0, wc.lpszClassName, title_, WS_OVERLAPPEDWINDOW, x, y, width_, height_, nullptr,
                           nullptr, GetModuleHandle(nullptr), this);
    if (hwnd_ == nullptr)
        return false;

    ShowWindow(hwnd_, SW_SHOW);

    return true;
}

void bardrix::window::hide() const {
    ShowWindow(hwnd_, SW_HIDE);
}

void bardrix::window::redraw() const {
    if (hwnd_)
        InvalidateRect(hwnd_, nullptr, FALSE);
}

void bardrix::window::close() const {
    if (hwnd_)
        DestroyWindow(hwnd_);
}

void bardrix::window::run() {
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK bardrix::window::window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    window* p_window = nullptr;
    if (msg == WM_NCCREATE) {
        CREATESTRUCT* create_struct = reinterpret_cast<CREATESTRUCT*>(lparam);
        p_window = reinterpret_cast<window*>(create_struct->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(p_window));
    } else
        p_window = reinterpret_cast<window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));


    if (!p_window)
        return DefWindowProc(hwnd, msg, wparam, lparam);

    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            if (p_window->on_close)
                p_window->on_close(p_window);
            break;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            if (p_window->on_paint) // Call the on_paint function
                p_window->on_paint(p_window, p_window->back_buffer_);

            std::swap(p_window->front_buffer_, p_window->back_buffer_);

            // Draw the front buffer to the screen
            StretchDIBits(hdc, 0, 0, p_window->width_, p_window->height_, 0, 0, p_window->width_,
                          p_window->height_, p_window->front_buffer_.data(), &p_window->bmi_, DIB_RGB_COLORS,
                          SRCCOPY);

            EndPaint(hwnd, &ps);
            break;
        }
        case WM_KEYDOWN:
            if (p_window->on_keydown)
                p_window->on_keydown(p_window, wparam);
            break;
        case WM_SIZE:
            p_window->width_ = LOWORD(lparam);
            p_window->height_ = HIWORD(lparam);
            p_window->bmi_.bmiHeader.biWidth = p_window->width_;
            p_window->bmi_.bmiHeader.biHeight = -p_window->height_; // top-down
            p_window->back_buffer_.resize(p_window->width_ * p_window->height_);
            p_window->front_buffer_.resize(p_window->width_ * p_window->height_);
            if (p_window->on_resize)
                p_window->on_resize(p_window, p_window->width_, p_window->height_);
            break;
        default:
            return DefWindowProc(hwnd, msg, wparam, lparam);
    }
    return 0;
}

#endif // _WIN32