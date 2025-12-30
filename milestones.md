# 🧱 Blueprint do Ambar Package Manager (`amb`) Separado por Milestones

## Visão geral do caminho

Você vai sair de:
→ um binário que apenas imprime argumentos
até:
→ um gerenciador de pacotes funcional, integrado ao compilador Ambar

Cada etapa constrói **base estrutural**, não gambiarra.

---

# 🚀 Milestone 0 — Fundamentos do Projeto

Objetivo: preparar o terreno para crescer sem refatoração pesada depois.

## O que você constrói

* Repositório do `amb`
* Build funcionando em Linux e Windows
* Estrutura base de pastas
* Executável `amb` rodando

## Decisões aqui

* CMake como sistema de build
* C++ moderno (C++20)
* CLI parser (CLI11 recomendado)

## Estrutura inicial sugerida

```
amb/
├─ CMakeLists.txt
├─ src/
│  ├─ main.cpp
│  └─ cli/
├─ include/
├─ tests/
└─ README.md
```

## Critério de conclusão

```
amb --help
amb install foo
```

→ apenas imprime o que foi digitado, nada mais.

---

# 🧩 Milestone 1 — Núcleo da CLI

Objetivo: transformar texto do terminal em comandos internos bem definidos.

## O que você constrói

* Parser de comandos (`install`, `remove`, `list`, etc)
* Dispatcher de comandos
* Estrutura Command Pattern

## Conceito-chave

Cada comando vira um **objeto**, não um `if/else`.

## Exemplo mental

```
amb install math_utils
→ InstallCommand.execute("math_utils")
```

## Critério de conclusão

* Comandos reconhecidos corretamente
* Mensagens de erro claras
* Código extensível para novos comandos

---

# 🗂️ Milestone 2 — Configuração e Estado Local

Objetivo: dar memória ao `amb`.

## O que você constrói

* Diretório global `~/.ambar/`
* Configuração global (`config.json`)
* Detecção de projeto (`ambar.json`)
* Diferenciação:

  * instalação global
  * instalação local

## Conceitos importantes

* Nenhuma lógica de negócio ainda
* Apenas leitura e escrita de estado

## Critério de conclusão

* `amb` sabe onde está
* `amb` sabe se está dentro de um projeto
* Caminhos funcionam em Linux e Windows

---

# 📦 Milestone 3 — Especificação do Pacote Ambar

Objetivo: definir **o contrato** dos pacotes.

## O que você constrói

* Especificação final do `ambar.json`
* Validador de schema
* Loader de manifesto

## Exemplo mínimo

```
{
  "name": "math_utils",
  "version": "1.2.3",
  "dependencies": {
    "core": "^1.0.0"
  }
}
```

## Critério de conclusão

* Erros claros em manifests inválidos
* Estrutura pronta para evoluir

---

# 🗄️ Milestone 4 — Registry Local (Filesystem)

Objetivo: simular um “repositório oficial” sem internet.

## O que você constrói

* Registry baseado em pastas
* Index simples por pacote
* Consulta de versões disponíveis

## Estrutura exemplo

```
registry/
└─ math_utils/
   ├─ 1.0.0/
   ├─ 1.2.0/
   └─ 1.2.3/
```

## Critério de conclusão

* `amb search math_utils`
* `amb install math_utils` encontra versões

---

# 🧠 Milestone 5 — Resolução de Versões e Dependências

Objetivo: decidir **o que instalar**, não instalar ainda.

## O que você constrói

* Resolver de versões (SemVer)
* Leitura de dependências
* Árvore de dependências
* Detecção de conflitos simples

## Importante

* Sem backtracking no MVP
* Errou → aborta com mensagem clara

## Critério de conclusão

* Dependências resolvidas corretamente
* Árvore previsível e determinística

---

# 💾 Milestone 6 — Cache de Pacotes

Objetivo: não baixar / copiar duas vezes.

## O que você constrói

* Cache global
* Verificação de hash
* Reutilização de pacotes

## Estrutura

```
~/.ambar/cache/
└─ math_utils-1.2.3.zip
```

## Critério de conclusão

* Instalações repetidas usam cache
* Hash inválido aborta processo

---

# 🔐 Milestone 7 — Segurança Básica

Objetivo: impedir pacotes corrompidos ou adulterados.

## O que você constrói

* Hash SHA-256
* Validação antes de instalar
* Base para assinaturas futuras

## Critério de conclusão

* Pacote alterado → erro
* Pacote íntegro → segue

---

# 🧩 Milestone 8 — Instalação Física

Objetivo: colocar pacotes no lugar certo.

## O que você constrói

* Descompactação
* Organização por versão
* Estrutura padrão em `ambar_modules`

## Resultado final

```
ambar_modules/
└─ lib/
   └─ math_utils/
      └─ 1.2.3/
```

## Critério de conclusão

* Arquivos no lugar certo
* Nenhuma colisão de versões

---

# 🔒 Milestone 9 — Lockfile

Objetivo: builds reproduzíveis.

## O que você constrói

* `ambar.lock`
* Registro exato de versões
* Hashes e dependências

## Critério de conclusão

* Mesmo projeto → mesmo build
* `amb install` respeita lockfile

---

# 🔗 Milestone 10 — Integração com o Compilador Ambar

Objetivo: fechar o ciclo.

## O que você constrói

* Contrato entre `amb` e compilador
* Resolução de imports
* Caminho físico garantido

## Resultado

```
import "math_utils"
→ caminho resolvido automaticamente
```

## Critério de conclusão

* Compilador consome pacotes do `amb`
* Nenhum hardcode

---

# 🧪 Milestone 11 — Testes e Qualidade

Objetivo: estabilidade real.

## O que você constrói

* Testes unitários
* Testes de integração
* Casos de erro

## Critério de conclusão

* `amb` falha bem
* Mensagens claras
* Comportamento previsível

---

# 🗺️ Milestone 12 — Preparação para o Futuro

Objetivo: não se limitar.

## O que fica preparado

* Registry remoto
* Binários pré-compilados
* Plugins
* Assinaturas criptográficas
* Espelhos (mirrors)

Nada disso implementado ainda — só **preparado**.

---