🌐 [English](README.md) | **Português**

# Front-End Compilador Linguagem P

Projeto do curso de compiladores desenvolvido em **C**, com foco no **Front-End** de uma pequena linguagem de programação personalizada (P) definida pelo professor Guilherme Silva da UFSJ.

## O que já foi desenvolvido

- **Analisador léxico:** percorre um arquivo de código-fonte caractere por caractere e converte seu conteúdo em tokens.
- **Reconhecimento de tokens:** identifica palavras reservadas, identificadores, literais inteiros e de ponto flutuante, caracteres, strings, operadores e delimitadores.
- **Identificação de erros:** classifica sequências inválidas ou não reconhecidas como `TOKEN_ERROR`.
- **Exibição de tokens:** apresenta o tipo, o lexema e o número da linha de cada token.

## Como executar

Compile e execute na raiz do repositório utilizando GCC:

```bash
gcc compiler.c -o compiler
./compiler test.txt
```
