# 🤖 Robô de Sumô

Este repositório contém o projeto de desenvolvimento de um **Robô de Sumô**. O objetivo do projeto é construir e programar um robô autônomo capaz de competir em arenas de sumô, utilizando sensores para detectar o adversário e limites da pista, tomando decisões rápidas e precisas para empurrar o oponente para fora da arena.

---

## 🎯 Objetivos do Projeto

- Construção de um robô autônomo para competições de Sumô.  
- Implementação de sensores para detecção de adversário e limites da arena.  
- Desenvolvimento de algoritmos de controle de movimento e tomada de decisão em tempo real.  
- Integração de hardware e software em uma plataforma embarcada.

---

## 🛠 Tecnologias e Ferramentas Utilizadas

- **ESP32**: Microcontrolador principal do robô.  
- **PlatformIO**: Configuração e gerenciamento do ambiente de desenvolvimento.  
- **C/C++**: Linguagens para programação do firmware.  
- **CMake**: Sistema de compilação.  
- **VSCode**: IDE para desenvolvimento e depuração.  
- Sensores de proximidade, infravermelho e/ou ultrassônicos para navegação e detecção do adversário.

---

## 📂 Estrutura do Projeto

```bash
codigo-robo/
├── .gitignore
├── CMakeLists.txt
├── platformio.ini
├── sdkconfig.esp32dev
├── .vscode/
├── include/
├── lib/
├── src/
├── test/
└── .pio/
```

- **.gitignore**: Arquivos e pastas ignoradas pelo Git.

- **CMakeLists.txt**: Configuração do sistema de compilação.

- **platformio.ini**: Parâmetros de configuração do PlatformIO.

- **sdkconfig.esp32dev**: Configurações específicas do ESP32.

- **.vscode/**: Configurações do VSCode para o projeto.

- **include/**: Arquivos de cabeçalho.

- **lib/**: Bibliotecas externas ou personalizadas.

- **src/**: Código-fonte principal do robô.

- **test/**: Testes unitários ou de funcionalidade.

- **.pio/**: Diretório gerado pelo PlatformIO durante a compilação.

---

## ⚙️ Como Compilar e Rodar

1. Instale o **PlatformIO** no **VSCode**.

2. Clone o repositório:

```bash
git clone https://github.com/lauratrigo/Robo_de_Sumo.git
cd robo-de-sumo
```

3. Abra o projeto no VSCode e selecione o ambiente ESP32.

4. Compile o projeto e faça upload para o microcontrolador.

5. Teste o robô na arena de Sumo, ajustando parâmetros de sensores e movimento conforme necessário.

---

## 📌 Observações

- O projeto foca em controle autônomo, sensores de proximidade e tomada de decisão rápida.  
- O ajuste fino de parâmetros de PID e calibragem de sensores é essencial para o desempenho do robô.  
- Possível expansão futura: detecção de adversário por visão computacional ou inteligência artificial simples.

---

## 🤝 Agradecimentos

Projeto desenvolvido como parte de atividades acadêmicas do oitavo período de engenharia da computação da UNIVAP.  
Agradecimentos especiais à **professora Virginia** e ao **professor Irapuan** pelo suporte e orientação.

---

## 📜 Licença

Este repositório está licenciado sob **MIT License**. Consulte o arquivo LICENSE para mais informações.
