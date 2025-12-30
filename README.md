# 🧡 Ambar Package Manager — `amb`

O **`amb`** é o gerenciador oficial de pacotes da linguagem **Ambar**.
Ele foi projetado para ser **simples, previsível, seguro e escalável**, servindo como base sólida para o ecossistema da linguagem.

> 📦 Organiza dependências
> 🔐 Garante integridade
> ⚙️ Integra-se naturalmente ao compilador
> 🚀 Escala sem complexidade desnecessária

---

## ✨ Visão Geral

O `amb` é responsável por:

* Instalar bibliotecas Ambar 📥
* Resolver versões e dependências 🧠
* Gerenciar múltiplas versões simultaneamente 🔁
* Manter builds reproduzíveis via lockfile 🔒
* Preparar pacotes para uso direto pelo compilador 🧩

Ele **não compila código** e **não executa scripts em tempo de build por padrão** — o foco é **organização e confiabilidade**.

---

## 🛠️ Instalação

*(em breve)*

```bash
amb --version
```

---

## 🚀 Uso Básico

### 📦 Instalar um pacote

```bash
amb install math_utils
```

### 🗑️ Remover um pacote

```bash
amb remove math_utils
```

### 🔄 Atualizar dependências

```bash
amb update
```

### 📋 Listar pacotes instalados

```bash
amb list
```

### 🔍 Buscar pacotes no registry

```bash
amb search math
```

---

## 📁 Estrutura de um Projeto Ambar

Após instalar dependências, seu projeto terá algo como:

```
my_project/
├─ ambar.json
├─ ambar.lock
├─ src/
└─ ambar_modules/
   └─ lib/
      └─ math_utils/
         └─ 1.2.3/
```

📌 **Múltiplas versões podem coexistir**, evitando conflitos.

---

## 📄 `ambar.json` (Manifesto do Projeto)

Arquivo principal de configuração do projeto Ambar.

Exemplo mínimo:

```json
{
  "name": "my_project",
  "version": "0.1.0",
  "dependencies": {
    "math_utils": "^1.2.0"
  }
}
```

---

## 🔒 `ambar.lock`

O `ambar.lock` garante **builds reproduzíveis**.

Ele registra:

* versões exatas 📌
* hashes dos pacotes 🔐
* árvore completa de dependências 🌳

👉 Se existe lockfile, o `amb` sempre o respeita.

---

## 🧠 Resolução de Dependências

* Usa **Semantic Versioning (SemVer)**
* Permite **múltiplas versões simultâneas**
* Conflitos de versão:

  * ❌ não são resolvidos automaticamente no MVP
  * ✅ geram erro claro e explícito

---

## 🔗 Integração com o Compilador Ambar

O `amb` **não depende do compilador**
e o compilador **não depende do `amb`**.

O contrato é simples:

> Se o pacote existir em um caminho conhecido,
> o compilador consegue usá-lo.

Exemplo de import:

```ambar
import "math_utils@1.2.3"
```

O compilador resolve isso via filesystem 📂.

---

## 🔐 Segurança

O `amb` implementa:

* ✅ Verificação de integridade (SHA-256)
* ✅ Estrutura pronta para assinaturas digitais
* ❌ Execução automática de código arbitrário (por design)

Segurança primeiro 🔒.

---

## 🧱 Arquitetura (Resumo)

* CLI escrita em **C++ moderno (C++20)** ⚙️
* Design modular e extensível 🧩
* Registry inicial baseado em filesystem 📁
* Preparado para registry remoto no futuro 🌐

---

## 🗺️ Roadmap

### MVP

* [x] CLI base
* [x] Instalação de pacotes
* [x] Múltiplas versões
* [x] Lockfile
* [x] Cache local

### Futuro

* 🔐 Assinaturas criptográficas
* 🌍 Registry remoto
* 📦 Pacotes binários
* 🧩 Plugins
* 🪞 Mirrors

---

## 🤝 Contribuindo

Contribuições são bem-vindas ❤️

Antes de começar:

1. Leia a arquitetura
2. Siga os padrões de código
3. Escreva testes sempre que possível

*(Guia de contribuição em breve)*

---

## 📜 Licença

Licença MIT.

---

## 🧡 Filosofia

> Simplicidade não é falta de poder.
> É poder sem confusão.

O `amb` existe para que **desenvolvedores Ambar pensem em código, não em dependências**.