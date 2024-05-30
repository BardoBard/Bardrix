//
// Created by Bardio on 22/05/2024.
//

#include <iostream>

#ifdef _WIN32

#include "sphere.h"
#include "window.h"

#include <bardrix/ray.h>
#include <bardrix/light.h>
#include <bardrix/camera.h>

int main() {
    int width = 600;
    int height = 600;
    // Create a window
    bardrix::window window("Raytracing", width, height);

    // Create a camera
    bardrix::camera camera = bardrix::camera({0,0,0}, {0,0,1}, width, height, 60);

    // Create a sphere
    sphere sphere(1.0, bardrix::point3(0.0, 0.0, 3.0));

    // [&camera, &sphere] is a capture list, this means we can access those objects outside the lambda
    // If you'd want to add a light you'd have to add this to the capture list too.
    window.on_paint = [&camera, &sphere](bardrix::window* window, std::vector<uint32_t>& buffer) {
        // Go through all the pixels
        for (int y = 0; y < window->get_height(); y++) {
            for (int x = 0; x < window->get_width(); x++) {

                // Shoot a ray from the camera to the pixel
                bardrix::ray ray = *camera.shoot_ray(x, y, 10);

                // Optional means that we can or cannot have a value
                // In order to check if the optional has a value, we use the has_value() method
                // If the optional has a value, we can access it using the value() method
                // E.g. intersection.value() -> bardrix::point3
                std::optional<bardrix::point3> intersection = sphere.intersection(ray);

                // Default color is black
                bardrix::color color = bardrix::color::black();

                // If the ray intersects the sphere, paint the pixel white
                if (intersection.has_value()) {
                    color = bardrix::color::white();
                }

                // Set the pixel
                buffer[y * window->get_width() + x] = color.argb(); // ARGB is the format used by Windows API
            }
        }
    };

    window.on_resize = [&camera](bardrix::window* window, int width, int height) {
        // Resize the camera
        camera.set_width(width);
        camera.set_height(height);

        window->redraw(); // Redraw the window (calls on_paint)
    };

    // Get width and height of the screen
    int screen_width = GetSystemMetrics(SM_CXSCREEN);
    int screen_height = GetSystemMetrics(SM_CYSCREEN);

    // Show the window in the center of the screen
    if (!window.show(screen_width / 2 - width / 2, screen_height / 2 - height / 2)) {
        std::cout << GetLastError() << std::endl;
        return -1;
    }

    bardrix::window::run();
}

#else // _WIN32

int main() {
    std::cout << "This example is only available on Windows." << std::endl;
    return 0;
}

#endif // _WIN32