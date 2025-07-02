#pragma once
#include <vector>
#include <string>
#include <random>
#include <chrono>

struct Color {
    int r, g, b;
    Color(int r = 255, int g = 255, int b = 255) : r(r), g(g), b(b) {}
};

struct Particle {
    double x, y;
    double vx, vy;
    double life;
    Color color;
    char character;
    
    Particle(double x, double y, double vx, double vy, double life, Color color, char character = '*')
        : x(x), y(y), vx(vx), vy(vy), life(life), color(color), character(character) {}
};

class FireworksDisplay {
private:
    int width, height;
    std::vector<Particle> particles;
    std::mt19937 rng;
    std::uniform_real_distribution<double> uniform_dist;
    std::uniform_int_distribution<int> color_dist;
    
    void clearScreen();
    void moveCursor(int x, int y);
    void setColor(const Color& color);
    void resetColor();
    std::string getColorCode(const Color& color);
    
public:
    FireworksDisplay(int width = 80, int height = 24);
    
    void addFirework(double x, double y, int particles = 20);
    void addTextFirework(const std::string& text, double x, double y);
    void update(double deltaTime);
    void render();
    void clear();
    
    // Animation methods
    void animateText(const std::string& text, double duration = 5.0);
    void rainbowText(const std::string& text, double y);
    void explodingText(const std::string& text, double x, double y);
    
    // Utility methods
    void hideCursor();
    void showCursor();
    void sleep(int milliseconds);
    
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    size_t getParticleCount() const { return particles.size(); }
};
