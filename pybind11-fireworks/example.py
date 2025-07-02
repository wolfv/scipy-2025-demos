#!/usr/bin/env python3
"""
Quick example showing how to use the fireworks library
"""

import sys
import time

def quick_example():
    """A simple example that works with or without the compiled module"""
    
    try:
        # Try to use the compiled C++ module
        import fireworks_py as fw
        print("🎆 Using compiled C++ module for maximum performance!")
        
        # Create display
        display = fw.FireworksDisplay(100, 25)
        
        # Show a quick demonstration
        print("Starting fireworks demonstration...")
        time.sleep(2)
        
        # Add some fireworks
        for i in range(5):
            x = 20 + i * 15
            y = 10 + (i % 3) * 3
            display.add_firework(x, y, 20)
        
        # Animate for a few seconds
        for frame in range(60):  # 3 seconds at 20fps
            display.update(0.05)
            display.render()
            display.sleep(50)
        
        # Show text animation
        display.clear()
        display.animate_text("SCIPY 2025!", 4.0)
        
        display.show_cursor()
        
    except ImportError:
        # Fallback to pure Python
        print("📝 Using pure Python fallback (install pybind11 for better performance)")
        
        import math
        import random
        import os
        
        # Check if terminal supports ANSI colors
        if not (sys.stdout.isatty() and os.getenv('TERM') != 'dumb'):
            print("❌ Terminal doesn't support ANSI colors. Try running in a proper terminal.")
            return
        
        print("\033[2J\033[H\033[?25l")  # Clear screen and hide cursor
        
        try:
            # Simple fireworks simulation
            for frame in range(100):
                print("\033[2J\033[H")  # Clear screen
                
                # Draw some "fireworks"
                for i in range(15):
                    x = random.randint(10, 70)
                    y = random.randint(5, 20)
                    r = random.randint(100, 255)
                    g = random.randint(100, 255) 
                    b = random.randint(100, 255)
                    char = random.choice(['*', '+', 'o', '#', '@'])
                    
                    print(f"\033[{y};{x}H\033[38;2;{r};{g};{b}m{char}", end='')
                
                # Rainbow text
                text = "SCIPY 2025!"
                center_x = 35
                center_y = 12
                
                for i, char in enumerate(text):
                    if char != ' ':
                        hue = (i * 0.3 + frame * 0.1) % (2 * math.pi)
                        r = int(127 * (1 + math.sin(hue)))
                        g = int(127 * (1 + math.sin(hue + 2.094)))
                        b = int(127 * (1 + math.sin(hue + 4.188)))
                        
                        x = center_x + i * 2
                        print(f"\033[{center_y};{x}H\033[38;2;{r};{g};{b}m{char}", end='')
                
                print("\033[0m", end='')
                sys.stdout.flush()
                time.sleep(0.1)
                
        finally:
            print("\033[0m\033[?25h\033[2J\033[H")  # Reset and show cursor

if __name__ == "__main__":
    print("🎆 Terminal Fireworks Quick Example 🎆")
    print("====================================")
    quick_example()
    print("✨ Demo completed! ✨")
