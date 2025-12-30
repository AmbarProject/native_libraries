#!/bin/bash

set -e

echo "🚀 Setting up Ambar Package Manager development environment..."
echo "============================================================="

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Check for required tools
check_tool() {
    if ! command -v $1 &> /dev/null; then
        echo -e "${RED}Error: $1 is not installed${NC}"
        exit 1
    fi
}

echo -e "${YELLOW}Checking required tools...${NC}"
check_tool cmake
check_tool git
check_tool make

# Install system dependencies
echo -e "\n${YELLOW}Installing system dependencies...${NC}"

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    # Ubuntu/Debian
    if command -v apt-get &> /dev/null; then
        sudo apt-get update
        sudo apt-get install -y \
            build-essential \
            cmake \
            git \
            wget \
            curl \
            libssl-dev \
            pkg-config
    # Fedora/RHEL
    elif command -v dnf &> /dev/null; then
        sudo dnf install -y \
            gcc-c++ \
            cmake \
            git \
            wget \
            curl \
            openssl-devel
    fi
    
elif [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS
    if ! command -v brew &> /dev/null; then
        echo -e "${RED}Homebrew is required for macOS development${NC}"
        echo "Visit: https://brew.sh"
        exit 1
    fi
    
    brew update
    brew install \
        cmake \
        git \
        wget \
        curl \
        openssl
    
elif [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" ]]; then
    # Windows (Git Bash/Cygwin)
    echo -e "${YELLOW}Windows detected - please install manually:${NC}"
    echo "1. CMake: https://cmake.org/download/"
    echo "2. Git: https://git-scm.com/download/win"
    echo "3. Build Tools: Visual Studio Build Tools"
    
else
    echo -e "${YELLOW}Unsupported OS. Please install manually:${NC}"
    echo "- CMake 3.20+"
    echo "- C++20 compatible compiler"
    echo "- Git"
fi

# Create build directory
echo -e "\n${YELLOW}Creating build directory...${NC}"
mkdir -p build
cd build

# Configure CMake
echo -e "\n${YELLOW}Configuring CMake...${NC}"
cmake .. \
    -DCMAKE_BUILD_TYPE=Debug \
    -DAMB_BUILD_TESTS=ON \
    -DAMB_ENABLE_SANITIZERS=ON

# Build
echo -e "\n${YELLOW}Building project...${NC}"
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

echo -e "\n${GREEN}✅ Setup complete!${NC}"
echo "============================================================="
echo "You can now run:"
echo "  cd build && ./bin/amb --help"
echo ""
echo "Development commands:"
echo "  make              # Build the project"
echo "  make test         # Run tests"
echo "  make clean        # Clean build"
echo "============================================================="