# Blueprint Oficial – Ambar Package Manager (amb)

Este documento consolida **todas as decisões, definições técnicas e arquiteturais** levantadas para a construção do **gerenciador de pacotes da linguagem Ambar**, chamado **`amb`**. Ele serve como **fonte única de verdade** para implementação, manutenção e evolução do ecossistema.

---

## 1. Visão Geral

O **Ambar Package Manager (amb)** é o gerenciador oficial de pacotes da linguagem Ambar. Seu papel é:

* Instalar, remover, atualizar e listar bibliotecas
* Publicar bibliotecas em um registry central
* Resolver dependências com suporte a múltiplas versões
* Integrar-se diretamente ao compilador Ambar
* Garantir segurança (integridade e autoria dos pacotes)

O projeto segue o princípio **architecture first**, priorizando estabilidade, clareza e evolução futura.

---

## 2. Decisões Fundamentais (Travadas)

### 2.1 CLI

* Nome do comando: `amb`
* Linguagem de implementação: **C++**
* Execução via terminal (CLI)

### 2.2 Compilador Ambar

* Implementado em **C++**
* Utiliza **LLVM** em partes do pipeline
* Já existente
* Integração direta com o `amb`

### 2.3 Plataformas Suportadas

* Linux
* Windows

Desde o início do projeto.

### 2.4 Tipo de Pacote

* Pacotes contêm **apenas código-fonte**
* Compilação ocorre localmente via compilador Ambar
* Suporte a binários pré-compilados **não faz parte do MVP**, mas é possível no futuro

### 2.5 Escopo do MVP

Incluído:

* install
* remove
* publish
* list
* search
* múltiplas versões paralelas
* registry simples baseado em filesystem

Excluído do MVP:

* mirrors
* resolução avançada de conflitos
* banco de dados
* UI
* otimizações avançadas

---

## 3. Estrutura de Diretórios

### 3.1 Diretórios Globais

```
~/.ambar/
├─ lib/        # bibliotecas globais
├─ cache/      # cache de pacotes baixados
└─ config.json # configuração global do amb
```

### 3.2 Diretórios Locais (Projeto)

```
./ambar_modules/
├─ lib/        # bibliotecas locais
└─ config.json # configuração do projeto
```

### 3.3 Estrutura de um Pacote Ambar

```
meu_pacote/
├─ ambar.json
├─ src/
│  └─ main.ambar
├─ tests/
├─ README.md
├─ LICENSE
└─ build.sh (opcional)
```

---

## 4. Arquivo ambar.json (Manifesto)

### 4.1 Finalidade

* Define a **intenção** do pacote
* Metadados, dependências e scripts

### 4.2 Campos Obrigatórios

* name
* version
* author
* description
* license

### 4.3 Campos Opcionais

* dependencies
* optional_dependencies
* dev_dependencies
* scripts

### 4.4 Exemplo

```json
{
  "name": "math_utils",
  "version": "1.0.0",
  "author": "Matheus",
  "description": "Biblioteca matemática",
  "license": "MIT",
  "dependencies": {
    "json_parser": ">=1.0,<2.0"
  },
  "scripts": {
    "build": "bash build.sh",
    "pre_install": "echo pre",
    "post_install": "echo post"
  }
}
```

---

## 5. Lockfile – ambar.lock

### 5.1 Finalidade

* Garante builds reproduzíveis
* Registra versões **exatas** instaladas

### 5.2 Papel

* `ambar.json` → intenção
* `ambar.lock` → realidade

### 5.3 Conteúdo

* Nome do pacote
* Versão resolvida
* Hash SHA-256
* Dependências resolvidas

---

## 6. Versionamento

* Semantic Versioning obrigatório
* Formato: MAJOR.MINOR.PATCH

---

## 7. Convenção de Nomes de Pacotes

* Igual ao Python
* lowercase
* snake_case
* sem namespaces no MVP

Exemplos válidos:

* math_utils
* http_client
* json_parser

---

## 8. Registry (Repositório Central)

### 8.1 Tipo

* Registry oficial único
* Baseado em filesystem

### 8.2 Estrutura

```
registry/
├─ math_utils/
│  ├─ 1.0.0/
│  │  └─ math_utils-1.0.0.zip
│  └─ 1.1.0/
│     └─ math_utils-1.1.0.zip
```

### 8.3 Operações

* upload
* download
* search
* remove

### 8.4 Autenticação

* Obrigatória para publicar/remover

---

## 9. CLI – amb

### 9.1 Comandos

```
amb install pacote@versao
amb remove pacote
amb update
amb publish
amb list
amb search nome
amb init
```

### 9.2 Cache

* `~/.ambar/cache`

### 9.3 Hooks

* pre_install
* post_install

---

## 10. Resolução de Dependências

* Múltiplas versões paralelas permitidas
* Aviso ao usuário quando houver duplicação
* Conflitos causam falha (MVP)

Instalação por versão:

```
ambar_modules/lib/math_utils/1.0.0/
```

---

## 11. Integração com o Compilador Ambar

### 11.1 Import

```ambar
import "math_utils@1.0.0"
```

### 11.2 Ordem de Resolução

1. Local (`./ambar_modules/lib`)
2. Global (`~/.ambar/lib`)

### 11.3 Atualizações

* Mudanças exigem recompilação
* `amb update` controla upgrades

---

## 12. Segurança

* Hash SHA-256 obrigatório
* Assinatura digital dos pacotes
* Verificação no download e instalação

---

## 13. Roadmap de Implementação

1. Arquitetura interna do amb
2. Parser de ambar.json / ambar.lock
3. CLI mínima (install/remove/publish)
4. Registry filesystem
5. Cache e verificação de integridade
6. Hooks
7. Integração com compilador
8. Testes
9. Documentação

---

## 14. Considerações Finais

Este documento define a **base oficial do ecossistema Ambar**.

Qualquer mudança futura deve:

* manter compatibilidade
* ser documentada
* respeitar o MVP estabelecido

Este blueprint permite a implementação do `amb`.
