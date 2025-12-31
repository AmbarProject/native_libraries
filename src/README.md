# 🧡 Ambar Package Manager (`amb`)

The official package manager for the **Ambar programming language**.

---

## 🚀 Status

**Development (MVP)**
Currently implementing the **Minimum Viable Product**.

---

## 📦 Features (Planned)

* ✅ **Package installation** — `amb install <package>`
* ✅ **Package removal** — `amb remove <package>`
* ✅ **Package listing** — `amb list`
* 🔄 **Dependency resolution**
* 🔄 **Version management**
* 🔄 **Lockfile for reproducible builds**
* 🔄 **Registry integration**

---

## 🛠️ Building from Source

### Prerequisites

* C++20 compatible compiler
  (GCC 10+, Clang 10+, MSVC 2019+)
* CMake 3.20+

### Build Steps

```bash
# Clone repository
git clone <repository-url>
cd ambar-package-manager

# Setup development environment (recommended)
./scripts/setup.sh

# Or build manually
mkdir build && cd build
cmake ..
make

# Run tests
ctest --output-on-failure
```

---

## 🚀 Quick Start

```bash
# Initialize a new project
amb init my_project
cd my_project

# Install a package
amb install math_utils@1.0.0

# List installed packages
amb list

# Build your project with the Ambar compiler
ambar compile main.ambar
```

---

## 📁 Project Structure

```text
ambar-package-manager/
├── src/           # Source code
├── include/       # Header files
├── tests/         # Unit tests
├── cmake/         # CMake modules
├── scripts/       # Utility scripts
└── third_party/   # External dependencies
```

---

## 🔧 Development

### Code Style

* Use `.clang-format` for consistent formatting
* Run the formatter before committing:

```bash
./scripts/format.sh
```

### Testing

```bash
cd build
make && ctest --verbose
```

---

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests
5. Submit a pull request

---

## 📄 License

MIT License — see the **LICENSE** file for details.

---

## 🚀 Como Usar Este Código

### Passo 1: Criar a Estrutura do Projeto

```bash
# Crie todos os diretórios
mkdir -p ambar-package-manager/{src/{core,cli,utils,commands},include/amb,tests/unit,cmake,scripts,.github/workflows,third_party}

# Crie cada arquivo com o conteúdo correspondente
# (copie e cole cada seção em seu respectivo arquivo)
```

---

### Passo 2: Build e Teste

```bash
cd ambar-package-manager

# Dê permissão aos scripts
chmod +x scripts/*.sh

# Configure e build
./scripts/setup.sh

# Teste o executável
./amb --help
./amb list
./amb install test
```