//
// Created by Bardio on 20/04/2024.
//

#pragma once
#ifdef _WIN32

#include <bardrix/bardrix.h>
#include <bardrix/color.h>

#undef UNICODE // This is for the window class to work with char* instead of wchar_t* (unicode)
#include <Windows.h>

#include <cstdint>
#include <functional>
#include <vector>

namespace bardrix {

    /// \brief This class serves as a simple window creation and management class, it can be used for simple applications,
    ///        if you'd like to do more complex stuff that also supports unix, mac, etc. I recommend using GLFW, QT, etc.
    /// \details This class is only for Windows, use a different library for other platforms.
    class window {
    public:
        /// \brief The on_resize function, called when the window is resized.
        /// \param window The original window that was resized.
        /// \param width The new width of the window.
        /// \param height The new height of the window.
        /// \example window.on_resize = [](window* window, int width, int height) { original_window->redraw(); };
        std::function<void(bardrix::window* window, int width, int height)> on_resize;

        /// \brief The on_paint function, called when the window needs to be painted.
        /// \param window The original window that needs to be painted.
        /// \param buffer The buffer to paint to where the format used is AARRGGBB.
        /// \example window.on_paint = [](bardrix::window* window, std::vector<uint32_t>& buffer) {    \n
        ///         for (unsigned int & i : buffer) {                                                           \n
        ///             bardrix::color red = bardrix::color::magenta();                                         \n
        ///             i = red.a() << 24 | red.r() << 16 | red.g() << 8 | red.b();                             \n
        ///         }                                                                                           \n
        ///     };
        std::function<void(bardrix::window* window, std::vector<uint32_t>& buffer)> on_paint;

        /// \brief The on_close function, called when the window is closed.
        /// \param window The window that was closed.
        std::function<void(bardrix::window* window)> on_close;

    protected:
        /// \brief The title of the window.
        const char* title_;

        /// \brief The size of the window.
        int width_, height_;

        /// \brief The handle to the window.
        HWND hwnd_{};

        /// \brief Buffers for swapping between displaying and drawing.
        std::vector<uint32_t> back_buffer, front_buffer;
        /// \brief The bitmap info for the window.
        BITMAPINFO bmi = {};

    public:
        /// \brief Constructor for the window class.
        /// \param title The title of the window, if it's nullptr or empty, it will be converted to "Bardrix Window".
        /// \param width The width of the window, when negative, it will be converted to positive.
        /// \param height The height of the window, when negative, it will be converted to positive.
        window(const char* title, int width, int height);

        /// \brief Destructor for the window class.
        ~window();

        /// \brief Gets the width of the window.
        /// \return The width of the window.
        NODISCARD int get_width() const;

        /// \brief Gets the height of the window.
        /// \return The height of the window.
        NODISCARD int get_height() const;

        /// \brief Gets the title of the window.
        /// \return The title of the window.
        NODISCARD const char* get_title() const;

        /// \brief Shows the window at a specified position.
        /// \param x The x position of the window.
        /// \param y The y position of the window.
        /// \return If the window was shown successfully.
        /// \note If the window cannot be shown correctly due to an error, it will return false.
        /// \example if (!window.show(100, 100)) return 1;
        NODISCARD bool show(int x = 0, int y = 0);

        /// \brief Hides the window.
        void hide() const;

        /// \brief Refreshes this specific window.
        /// \note This will call the on_paint function.
        void redraw() const;

        /// \brief Runs all windows.
        static void run();

    protected:
        /// \brief The window procedure for the window (this is windows API)
        /// \param hwnd The handle to the window.
        /// \param msg The message to the window.
        /// \param wparam The wparam to the window.
        /// \param lparam The lparam to the window.
        /// \return The result of the window procedure.
        static LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

    }; // class window
} // namespace bardrix

#endif // _WIN32