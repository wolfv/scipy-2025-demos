#!/usr/bin/env python3
"""
Demo script for the fireworks_py module.
This script demonstrates various animation features.
"""

import time
import sys

def demo_basic_usage():
    """Basic usage demo"""
    try:
        import fireworks_py as fw
        
        print("Creating fireworks display...")
        display = fw.FireworksDisplay(100, 30)
        
        # Demo 1: Simple firework explosions
        print("Demo 1: Basic fireworks (press Ctrl+C to continue)")
        try:
            start_time = time.time()
            last_firework = 0
            
            while time.time() - start_time < 10:
                current_time = time.time() - start_time
                
                # Add fireworks every 0.5 seconds
                if current_time - last_firework > 0.5:
                    display.add_firework(50 + (current_time * 10) % 40, 10, 25)
                    last_firework = current_time
                
                display.update(0.05)
                display.render()
                display.sleep(50)
                
        except KeyboardInterrupt:
            pass
        
        display.clear()
        
        # Demo 2: Animated text
        print("\\nDemo 2: Text animation")
        display.animate_text("HELLO SCIPY 2025!", 8.0)
        
        # Demo 3: Exploding text
        display.clear()
        print("\\nDemo 3: Exploding text effects")
        
        texts = ["FIREWORKS!", "AMAZING!", "SPECTACULAR!"]
        for text in texts:
            display.exploding_text(text, 40, 15)
            
            for _ in range(100):  # Run for ~5 seconds
                display.update(0.05)
                display.render()
                display.sleep(50)
            
            display.clear()
            time.sleep(1)
        
        display.show_cursor()
        print("\\nDemo completed!")
        
    except ImportError:
        print("fireworks_py module not found. Please build it first using:")
        print("pip install pybind11")
        print("python setup.py build_ext --inplace")
        return False
    
    return True

def demo_python_only():
    """Python-only demo using ANSI escape codes"""
    import random
    import math
    
    print("\\033[2J\\033[H")  # Clear screen
    print("\\033[?25l")      # Hide cursor
    
    try:
        width, height = 80, 24
        
        # Rainbow text animation
        text = "PYTHON FIREWORKS!"
        
        for frame in range(200):
            print("\\033[2J\\033[H")  # Clear and go to top
            
            # Rainbow text
            center_x = (width - len(text) * 2) // 2
            center_y = height // 2
            
            for i, char in enumerate(text):
                if char != ' ':
                    x = center_x + i * 2
                    y = center_y
                    
                    # Rainbow color calculation
                    hue = (i * 0.3 + frame * 0.1) % (2 * math.pi)
                    r = int(127 * (1 + math.sin(hue)))
                    g = int(127 * (1 + math.sin(hue + 2.094)))
                    b = int(127 * (1 + math.sin(hue + 4.188)))
                    
                    print(f"\\033[{y};{x}H\\033[38;2;{r};{g};{b}m{char}", end='')
            
            # Add some "fireworks" (random colored characters)
            for _ in range(10):
                x = random.randint(1, width)
                y = random.randint(1, height - 5)
                r = random.randint(100, 255)
                g = random.randint(100, 255)
                b = random.randint(100, 255)
                char = random.choice(['*', '+', 'o', '#', '@', '&', '%'])
                
                print(f"\\033[{y};{x}H\\033[38;2;{r};{g};{b}m{char}", end='')
            
            print("\\033[0m", end='')  # Reset color
            print(f"\\033[{height-1};1HFrame: {frame}/200 - Press Ctrl+C to exit", end='')
            sys.stdout.flush()
            time.sleep(0.1)
            
    except KeyboardInterrupt:
        pass
    finally:
        print("\\033[0m")    # Reset color
        print("\\033[?25h")  # Show cursor
        print("\\033[2J\\033[H")  # Clear screen

if __name__ == "__main__":
    print("Terminal Fireworks Demo")
    print("=" * 50)
    
    if not demo_basic_usage():
        print("\\nFalling back to Python-only demo...")
        demo_python_only()
    
    print("\\nThanks for watching!")
