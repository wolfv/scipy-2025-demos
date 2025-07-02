#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "fireworks.hpp"

namespace py = pybind11;

PYBIND11_MODULE(fireworks_py, m) {
    m.doc() = "Terminal fireworks and text animation library";
    
    // Color class binding
    py::class_<Color>(m, "Color")
        .def(py::init<int, int, int>(), "Create a color with RGB values",
             py::arg("r") = 255, py::arg("g") = 255, py::arg("b") = 255)
        .def_readwrite("r", &Color::r, "Red component (0-255)")
        .def_readwrite("g", &Color::g, "Green component (0-255)")
        .def_readwrite("b", &Color::b, "Blue component (0-255)")
        .def("__repr__", [](const Color& c) {
            return "Color(r=" + std::to_string(c.r) + 
                   ", g=" + std::to_string(c.g) + 
                   ", b=" + std::to_string(c.b) + ")";
        });
    
    // Particle class binding
    py::class_<Particle>(m, "Particle")
        .def(py::init<double, double, double, double, double, Color, char>(),
             "Create a particle",
             py::arg("x"), py::arg("y"), py::arg("vx"), py::arg("vy"), 
             py::arg("life"), py::arg("color"), py::arg("character") = '*')
        .def_readwrite("x", &Particle::x, "X position")
        .def_readwrite("y", &Particle::y, "Y position")
        .def_readwrite("vx", &Particle::vx, "X velocity")
        .def_readwrite("vy", &Particle::vy, "Y velocity")
        .def_readwrite("life", &Particle::life, "Remaining life")
        .def_readwrite("color", &Particle::color, "Particle color")
        .def_readwrite("character", &Particle::character, "Display character")
        .def("__repr__", [](const Particle& p) {
            return "Particle(x=" + std::to_string(p.x) + 
                   ", y=" + std::to_string(p.y) + 
                   ", life=" + std::to_string(p.life) + ")";
        });
    
    // FireworksDisplay class binding
    py::class_<FireworksDisplay>(m, "FireworksDisplay")
        .def(py::init<int, int>(), "Create a fireworks display",
             py::arg("width") = 80, py::arg("height") = 24)
        
        // Core methods
        .def("add_firework", &FireworksDisplay::addFirework,
             "Add a firework explosion at position (x, y)",
             py::arg("x"), py::arg("y"), py::arg("particles") = 20)
        .def("add_text_firework", &FireworksDisplay::addTextFirework,
             "Create a firework from text characters",
             py::arg("text"), py::arg("x"), py::arg("y"))
        .def("update", &FireworksDisplay::update,
             "Update particle physics",
             py::arg("delta_time"))
        .def("render", &FireworksDisplay::render,
             "Render the current frame to terminal")
        .def("clear", &FireworksDisplay::clear,
             "Clear all particles and screen")
        
        // Animation methods
        .def("animate_text", &FireworksDisplay::animateText,
             "Animate text with fireworks for specified duration",
             py::arg("text"), py::arg("duration") = 5.0)
        .def("rainbow_text", &FireworksDisplay::rainbowText,
             "Display text with rainbow colors",
             py::arg("text"), py::arg("y"))
        .def("exploding_text", &FireworksDisplay::explodingText,
             "Make text explode into particles",
             py::arg("text"), py::arg("x"), py::arg("y"))
        
        // Utility methods
        .def("hide_cursor", &FireworksDisplay::hideCursor,
             "Hide terminal cursor")
        .def("show_cursor", &FireworksDisplay::showCursor,
             "Show terminal cursor")
        .def("sleep", &FireworksDisplay::sleep,
             "Sleep for specified milliseconds",
             py::arg("milliseconds"))
        
        // Properties
        .def_property_readonly("width", &FireworksDisplay::getWidth,
                              "Display width")
        .def_property_readonly("height", &FireworksDisplay::getHeight,
                              "Display height")
        .def_property_readonly("particle_count", &FireworksDisplay::getParticleCount,
                              "Current number of particles");
    
    // Convenience functions
    m.def("create_rainbow_color", [](double phase) {
        int r = static_cast<int>(127 * (1 + std::sin(phase)));
        int g = static_cast<int>(127 * (1 + std::sin(phase + 2.094)));
        int b = static_cast<int>(127 * (1 + std::sin(phase + 4.188)));
        return Color(r, g, b);
    }, "Create a rainbow color based on phase", py::arg("phase"));
    
    m.def("get_terminal_size", []() {
        return std::make_pair(80, 24); // Default size, could be enhanced to get actual terminal size
    }, "Get terminal dimensions (width, height)");
}
