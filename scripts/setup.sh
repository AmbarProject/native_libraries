#!/bin/bash

set -e

echo "🚀 Setting up Ambar Package Manager development environment..."

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Check for required tools
check_command() {
    if ! command -v $1 &> /dev/null; then
        echo -e "${RED}Error: $1 is not installed${NC}"
        return 1
    fi
    return 0
}

echo -e "${YELLOW}Checking dependencies...${NC}"

check_command cmake || exit 1
check_command g++ || check_command clang++ || {
    echo -e "${RED}Error: No C++ compiler found${NC}"
    exit 1
}

# Clean previous build
echo -e "${YELLOW}Cleaning previous build...${NC}"
rm -rf build
mkdir -p build
cd build

# Configure CMake with minimal options for MVP
echo -e "${YELLOW}Configuring CMake...${NC}"
cmake .. \
    -DCMAKE_BUILD_TYPE=Debug \
    -DAMB_BUILD_TESTS=OFF \
    -DAMB_DOWNLOAD_CLI11=ON

# Build
echo -e "${YELLOW}Building...${NC}"
cmake --build . -- -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# Create symbolic link for development
echo -e "${YELLOW}Setting up development link...${NC}"
cd ..
if [[ ! -f "amb" && -f "build/amb" ]]; then
    ln -s build/amb amb 2>/dev/null || cp build/amb . 2>/dev/null || true
fi

# Test básico
echo -e "${YELLOW}Running basic test...${NC}"
if [[ -f "amb" ]]; then
    echo -e "${GREEN}Build successful! Testing executable...${NC}"
    ./amb --help
    echo ""
    echo -e "${GREEN}✅ Setup complete!${NC}"
else
    echo -e "${RED}❌ Build failed - executable not found${NC}"
    exit 1
fi

echo ""
echo "Next steps:"
echo "  ./amb --help                      # Show help"
echo "  ./amb init my_project             # Create a new project"
echo "  ./amb list                        # List installed packages"
echo ""
echo "Development:"
echo "  cd build && make                  # Rebuild"
echo "  ./amb --verbose install <pkg>     # Test with verbose output"