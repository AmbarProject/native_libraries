#!/bin/bash

set -e

echo "🔧 Formatting code with clang-format..."

# Check if clang-format is installed
if ! command -v clang-format &> /dev/null; then
    echo "Error: clang-format is not installed"
    echo "Install it with:"
    echo "  Ubuntu: sudo apt-get install clang-format"
    echo "  macOS: brew install clang-format"
    echo "  Windows: Download from LLVM website"
    exit 1
fi

# Create .clang-format if it doesn't exist
if [ ! -f .clang-format ]; then
    cat > .clang-format << 'EOF'
BasedOnStyle: LLVM
IndentWidth: 4
UseTab: Never
BreakBeforeBraces: Allman
AllowShortFunctionsOnASingleLine: None
AllowShortIfStatementsOnASingleLine: false
AllowShortLoopsOnASingleLine: false
ColumnLimit: 100
PointerAlignment: Left
SpaceBeforeParens: ControlStatements
IndentCaseLabels: true
NamespaceIndentation: All
EOF
    echo "Created .clang-format configuration"
fi

# Format all C++ files
find . -name "*.cpp" -o -name "*.hpp" -o -name "*.h" | while read file; do
    # Skip third_party directory
    if [[ $file == *"third_party"* ]]; then
        continue
    fi
    
    echo "Formatting: $file"
    clang-format -i -style=file "$file"
done

echo "✅ Formatting complete!"