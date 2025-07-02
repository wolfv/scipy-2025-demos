#!/bin/bash

# Terminal Fireworks Build Script
# This script helps build and test the project

set -e  # Exit on any error

echo "🎆 Terminal Fireworks Build Script 🎆"
echo "====================================="

# Function to check if command exists
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Check dependencies
echo "📋 Checking dependencies..."

if ! command_exists g++; then
    echo "❌ g++ not found. Please install a C++ compiler."
    exit 1
fi

if ! command_exists python3; then
    echo "❌ python3 not found. Please install Python 3.6+."
    exit 1
fi

echo "✅ Dependencies look good!"

# Build C++ demo
echo ""
echo "🔨 Building C++ demo..."
make clean
make demo

if [ $? -eq 0 ]; then
    echo "✅ C++ demo built successfully!"
else
    echo "❌ C++ build failed!"
    exit 1
fi

# Test Python animation
echo ""
echo "🐍 Testing Python animation..."
python3 test_animation.py

if [ $? -eq 0 ]; then
    echo "✅ Python animation test passed!"
else
    echo "❌ Python animation test failed!"
    exit 1
fi

# Try to build Python module (optional)
echo ""
echo "📦 Attempting to build Python module..."
if command_exists pip; then
    pip install pybind11 2>/dev/null || echo "⚠️  Could not install pybind11 automatically"
    python3 setup.py build_ext --inplace 2>/dev/null && echo "✅ Python module built!" || echo "⚠️  Python module build failed (pybind11 may not be available)"
else
    echo "⚠️  pip not found, skipping Python module build"
fi

echo ""
echo "🎉 Build completed!"
echo ""
echo "📖 Quick start:"
echo "   ./demo                    # Run C++ demo (all modes)"
echo "   ./demo basic              # Run basic fireworks"
echo "   ./demo text               # Run text animations"
echo "   ./demo interactive        # Run interactive mode"
echo "   python3 demo.py           # Run Python demo"
echo ""
echo "📚 For more information, see README.md"
