#include "fireworks.hpp"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

void demo_basic_fireworks() {
    std::cout << "Starting basic fireworks demo..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    FireworksDisplay display(100, 30);
    
    auto startTime = std::chrono::steady_clock::now();
    auto lastFirework = startTime;
    
    while (true) {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration<double>(currentTime - startTime).count();
        auto timeSinceLastFirework = std::chrono::duration<double>(currentTime - lastFirework).count();
        
        if (elapsed > 15.0) break; // Run for 15 seconds
        
        // Add fireworks every 0.8 seconds
        if (timeSinceLastFirework > 0.8) {
            double x = 20 + (elapsed * 8.0) + (rand() % 40);
            double y = 5 + (rand() % 15);
            display.addFirework(x, y, 20 + rand() % 15);
            lastFirework = currentTime;
        }
        
        display.update(0.05);
        display.render();
        display.sleep(50);
    }
    
    display.clear();
    display.showCursor();
}

void demo_text_animations() {
    std::cout << "Starting text animation demo..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    FireworksDisplay display(120, 30);
    
    // Demo different text animations
    std::vector<std::string> messages = {
        "WELCOME TO SCIPY 2025!",
        "C++ MEETS PYTHON",
        "FIREWORKS EVERYWHERE!",
        "AMAZING COLORS!"
    };
    
    for (const auto& message : messages) {
        display.animateText(message, 6.0);
        display.clear();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    
    display.showCursor();
}

void demo_interactive() {
    std::cout << "Interactive demo - Type messages to explode them!" << std::endl;
    std::cout << "Type 'quit' to exit, 'firework' for random fireworks, or any text to explode it." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    FireworksDisplay display(120, 30);
    std::string input;
    
    while (true) {
        display.clear();
        std::cout << "\033[31;1HEnter text (or 'quit'): ";
        display.showCursor();
        std::getline(std::cin, input);
        display.hideCursor();
        
        if (input == "quit") break;
        
        if (input == "firework") {
            // Add random fireworks
            for (int i = 0; i < 5; ++i) {
                double x = 10 + (rand() % 100);
                double y = 5 + (rand() % 20);
                display.addFirework(x, y, 25);
            }
            
            // Animate for a few seconds
            for (int frame = 0; frame < 100; ++frame) {
                display.update(0.05);
                display.render();
                display.sleep(50);
            }
        } else if (!input.empty()) {
            // Explode the text
            display.explodingText(input, 60 - input.length(), 15);
            
            // Also show rainbow version
            for (int frame = 0; frame < 150; ++frame) {
                display.update(0.05);
                display.render();
                display.rainbowText(input, 5);
                display.sleep(50);
            }
        }
    }
    
    display.showCursor();
}

int main(int argc, char* argv[]) {
    std::cout << "Terminal Fireworks C++ Demo" << std::endl;
    std::cout << "===========================" << std::endl;
    
    if (argc > 1) {
        std::string mode(argv[1]);
        
        if (mode == "basic") {
            demo_basic_fireworks();
        } else if (mode == "text") {
            demo_text_animations();
        } else if (mode == "interactive") {
            demo_interactive();
        } else {
            std::cout << "Unknown mode: " << mode << std::endl;
            std::cout << "Available modes: basic, text, interactive" << std::endl;
            return 1;
        }
    } else {
        // Run all demos
        std::cout << "Running all demos..." << std::endl;
        
        demo_basic_fireworks();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        demo_text_animations();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        demo_interactive();
    }
    
    std::cout << "Demo completed!" << std::endl;
    return 0;
}
