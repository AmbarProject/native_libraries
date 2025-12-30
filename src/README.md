# 🧡 Ambar Package Manager (`amb`)

🚧 **Em desenvolvimento inicial** — MVP em construção

O **gerenciador oficial de pacotes** da linguagem de programação **Ambar**.

---

## 📦 Funcionalidades Planejadas (MVP)

* [x] Estrutura básica do projeto
* [ ] CLI funcional
* [ ] Instalação e remoção de pacotes
* [ ] Gerenciamento de dependências
* [ ] Registry local
* [ ] Lockfile para builds reproduzíveis
* [ ] Integração com o compilador Ambar

---

## 🛠️ Build

```bash
# Clone o repositório
git clone <repo-url>
cd ambar-package-manager

# Configure o build
mkdir build && cd build
cmake ..

# Compile
make -j4

# Execute
./bin/amb --help
```

---

## 🧪 Desenvolvimento

```bash
# Setup do ambiente de desenvolvimento
./scripts/setup_dev.sh

# Build com testes
cd build
cmake .. -DAMB_BUILD_TESTS=ON
make && ctest

# Formatação de código
./scripts/format_code.sh
```

---

## 📁 Estrutura do Projeto

```text
ambar-package-manager/
├── src/           # Código-fonte
├── include/       # Headers públicos
├── tests/         # Testes unitários e de integração
├── cmake/         # Scripts CMake
├── scripts/       # Scripts auxiliares
└── third_party/   # Dependências externas
```

---

## 📚 Documentação

* 📘 **Blueprint** — Design e arquitetura
* 🗺️ **Milestones** — Roadmap de implementação
* 🧠 **Decisões Técnicas** — Decisões arquiteturais

---

## 🤝 Contribuindo

1. Faça um fork do repositório
2. Crie uma branch

   ```bash
   git checkout -b feature/nova-funcionalidade
   ```
3. Commit suas mudanças

   ```bash
   git commit -m "Adiciona nova funcionalidade"
   ```
4. Envie para a branch

   ```bash
   git push origin feature/nova-funcionalidade
   ```
5. Abra um Pull Request

---

## 📄 Licença

MIT — veja o arquivo **LICENSE** para mais detalhes.