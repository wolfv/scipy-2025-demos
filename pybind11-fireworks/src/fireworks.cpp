#include "fireworks.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <thread>
#include <algorithm>

FireworksDisplay::FireworksDisplay(int width, int height) 
    : width(width), height(height), 
      rng(std::chrono::steady_clock::now().time_since_epoch().count()),
      uniform_dist(0.0, 1.0),
      color_dist(0, 255) {
    hideCursor();
}

void FireworksDisplay::clearScreen() {
    std::cout << "\033[2J\033[H" << std::flush;
}

void FireworksDisplay::moveCursor(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H" << std::flush;
}

void FireworksDisplay::setColor(const Color& color) {
    std::cout << "\033[38;2;" << color.r << ";" << color.g << ";" << color.b << "m";
}

void FireworksDisplay::resetColor() {
    std::cout << "\033[0m";
}

std::string FireworksDisplay::getColorCode(const Color& color) {
    std::ostringstream oss;
    oss << "\033[38;2;" << color.r << ";" << color.g << ";" << color.b << "m";
    return oss.str();
}

void FireworksDisplay::addFirework(double x, double y, int particleCount) {
    for (int i = 0; i < particleCount; ++i) {
        double angle = 2.0 * M_PI * i / particleCount + uniform_dist(rng) * 0.5;
        double speed = 5.0 + uniform_dist(rng) * 10.0;
        double vx = std::cos(angle) * speed;
        double vy = std::sin(angle) * speed;
        
        Color color(color_dist(rng), color_dist(rng), color_dist(rng));
        double life = 1.0 + uniform_dist(rng) * 2.0;
        
        char chars[] = {'*', '+', 'o', '.', '#', '@', '&', '%'};
        char character = chars[static_cast<int>(uniform_dist(rng) * 8)];
        
        particles.emplace_back(x, y, vx, vy, life, color, character);
    }
}

void FireworksDisplay::addTextFirework(const std::string& text, double x, double y) {
    for (size_t i = 0; i < text.length(); ++i) {
        if (text[i] != ' ') {
            double charX = x + i * 2;
            double angle = uniform_dist(rng) * 2.0 * M_PI;
            double speed = 2.0 + uniform_dist(rng) * 5.0;
            double vx = std::cos(angle) * speed;
            double vy = std::sin(angle) * speed;
            
            Color color(color_dist(rng), color_dist(rng), color_dist(rng));
            double life = 2.0 + uniform_dist(rng) * 3.0;
            
            particles.emplace_back(charX, y, vx, vy, life, color, text[i]);
        }
    }
}

void FireworksDisplay::update(double deltaTime) {
    for (auto it = particles.begin(); it != particles.end();) {
        it->x += it->vx * deltaTime;
        it->y += it->vy * deltaTime;
        it->vy += 20.0 * deltaTime; // gravity
        it->life -= deltaTime;
        
        // Fade color based on remaining life
        double lifeFactor = std::max(0.0, it->life / 3.0);
        it->color.r = static_cast<int>(it->color.r * lifeFactor);
        it->color.g = static_cast<int>(it->color.g * lifeFactor);
        it->color.b = static_cast<int>(it->color.b * lifeFactor);
        
        if (it->life <= 0 || it->x < 0 || it->x >= width || it->y >= height) {
            it = particles.erase(it);
        } else {
            ++it;
        }
    }
}

void FireworksDisplay::render() {
    clearScreen();
    
    for (const auto& particle : particles) {
        if (particle.x >= 0 && particle.x < width && particle.y >= 0 && particle.y < height) {
            moveCursor(static_cast<int>(particle.x), static_cast<int>(particle.y));
            setColor(particle.color);
            std::cout << particle.character;
        }
    }
    
    resetColor();
    std::cout << std::flush;
}

void FireworksDisplay::clear() {
    particles.clear();
    clearScreen();
}

void FireworksDisplay::animateText(const std::string& text, double duration) {
    auto startTime = std::chrono::steady_clock::now();
    auto lastTime = startTime;
    
    // Initial text display with rainbow colors
    double centerX = (width - text.length() * 2) / 2.0;
    double centerY = height / 2.0;
    
    while (true) {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration<double>(currentTime - startTime).count();
        auto deltaTime = std::chrono::duration<double>(currentTime - lastTime).count();
        lastTime = currentTime;
        
        if (elapsed >= duration) break;
        
        // Add some random fireworks
        if (uniform_dist(rng) < 0.1) {
            double fx = uniform_dist(rng) * width;
            double fy = uniform_dist(rng) * height * 0.7; // Upper part of screen
            addFirework(fx, fy, 15 + static_cast<int>(uniform_dist(rng) * 10));
        }
        
        // Periodically explode the text
        if (static_cast<int>(elapsed * 2) % 3 == 0 && uniform_dist(rng) < 0.05) {
            explodingText(text, centerX, centerY);
        }
        
        update(deltaTime);
        render();
        
        // Display the main text with rainbow effect
        rainbowText(text, centerY - 5);
        
        sleep(50); // 50ms delay for smooth animation
    }
}

void FireworksDisplay::rainbowText(const std::string& text, double y) {
    double centerX = (width - text.length() * 2) / 2.0;
    auto currentTime = std::chrono::steady_clock::now();
    double time = std::chrono::duration<double>(currentTime.time_since_epoch()).count();
    
    for (size_t i = 0; i < text.length(); ++i) {
        if (text[i] != ' ') {
            moveCursor(static_cast<int>(centerX + i * 2), static_cast<int>(y));
            
            // Create rainbow effect
            double hue = (i * 0.1 + time) * 2.0;
            int r = static_cast<int>(127 * (1 + std::sin(hue)));
            int g = static_cast<int>(127 * (1 + std::sin(hue + 2.094))); // 120 degrees
            int b = static_cast<int>(127 * (1 + std::sin(hue + 4.188))); // 240 degrees
            
            Color rainbowColor(r, g, b);
            setColor(rainbowColor);
            std::cout << text[i];
        }
    }
}

void FireworksDisplay::explodingText(const std::string& text, double x, double y) {
    addTextFirework(text, x, y);
}

void FireworksDisplay::hideCursor() {
    std::cout << "\033[?25l";
}

void FireworksDisplay::showCursor() {
    std::cout << "\033[?25h";
}

void FireworksDisplay::sleep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
