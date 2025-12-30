## 🧠 Entendimento do MVP do `amb`

O MVP do **`amb` (Ambar Package Manager)** funciona da seguinte forma:

---

### 1️⃣ Instalação de bibliotecas via CLI 📦

Quando o desenvolvedor executa no terminal:

```bash
amb install name_lib@0.0.1
```

o **`amb`** é responsável por:

* 📥 localizar o pacote
* 🔐 validar a integridade (hash)
* 🧠 resolver dependências
* 📁 organizar os arquivos em pastas padronizadas

🚫 O `amb` **não compila código**
🚫 O `amb` **não interage diretamente com o compilador**

---

### 2️⃣ Organização previsível no filesystem 📂

Após a instalação, os arquivos do pacote ficam em um caminho conhecido:

```
ambar_modules/
└─ lib/
   └─ name_lib/
      └─ 0.0.1/
         ├─ src/
         ├─ ambar.json
         └─ README.md
```

📌 Essa estrutura padronizada é o **contrato principal** do sistema.

---

### 3️⃣ O papel do `ambar.lock` 🗺️

O arquivo **`ambar.lock`** funciona como um **registro do estado do projeto**, documentando:

* 📌 pacotes instalados
* 🔢 versões exatas
* 🌳 árvore de dependências
* 🔐 hashes de integridade

⚠️ Importante:
O `ambar.lock` **não conecta diretamente o `amb` ao compilador**.
Ele apenas garante **reprodutibilidade e previsibilidade** do ambiente.

---

### 4️⃣ Uso pelo compilador Ambar ⚙️

Quando o compilador encontra um import como:

```ambar
import "name_lib@0.0.1"
```

ele executa o seguinte fluxo:

1. 🧩 interpreta o nome e a versão
2. 📁 monta o caminho esperado:

```
./ambar_modules/lib/name_lib/0.0.1/
```

3. ✅ verifica se o diretório existe
4. 📄 carrega os arquivos como parte do projeto
5. 🔨 compila normalmente

📌 O compilador:

* ❌ não chama o `amb`
* ❌ não consulta o registry
* ❌ não resolve dependências

Ele apenas consome arquivos existentes.

---

### 5️⃣ Conceito-chave do MVP 🔑

> 🧡 O `amb` prepara o terreno.
> ⚙️ O compilador apenas anda sobre ele.

Essa separação torna o ecossistema:

* simples 🟢
* previsível 🧭
* escalável 📈
* fácil de manter 🧱

---

### 🧾 Resumo final

📦 `amb install` → organiza bibliotecas
🗺️ `ambar.lock` → registra o estado do projeto
📂 filesystem → ponto de integração
⚙️ compilador → usa os códigos como subarquivos

Esse é o **núcleo do MVP do Ambar Package Manager** — direto, explícito e profissional.