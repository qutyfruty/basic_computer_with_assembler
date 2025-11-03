project:
  name: "Basic Computer Project"
  description: >
    Implementare de basic computer în SystemVerilog, cu assembler scris în C++.
    Assemblerul convertește codul .asm în fișier .hex pentru simularea din Vivado.

structure:
  assembler:
    - main.cpp: "Assembler C++ care procesează instrucțiunile .asm"
    - test.asm: "Fișier de test pentru assembler"
  vivado:
    - uP.xpr: "Proiectul Vivado"
    - uP.srcs:
        sim_1/new/testbench.sv: "Testbench principal"
        sources_1/new:
          - alu.sv
          - basic_computer.sv
          - control_block.sv
          - data_mem.sv
          - instr_mem.sv
          - mux.sv
          - pc.sv
          - processor.sv
          - ralu.sv
          - reg_zero_flag.sv
          - register_file.sv
    - uP.sim/sim_1/behav/xsim/testbench.hex: "Fișierul generat de assembler"

assembler:
  language: "C++17"
  main_file: "main.cpp"
  description: >
    Assemblerul citește fișierul test.asm și generează testbench.hex, 
    care este încărcat automat în Vivado.
  features:
    - Elimină comentarii și spații
    - Identifică și salvează etichete
    - Traduce instrucțiunile (ADD, SUB, JMP, STORE, etc.)
    - Gestionează etichete necunoscute
    - Scrie ieșirea în format hexadecimal (32 biți)
  instruction_format: "[ opcode (4b) ][ dest (4b) ][ op0 (4b) ][ op1 (4b) ][ value (16b) ]"
  example:
    asm: "ADD R2, R0, R1"
    encoding: "0001 0010 0000 0001 0000000000000000"

usage:
  build:
    - "g++ main.cpp -o assembler"
  run:
    - "./assembler"
  output:
    - "Citește test.asm"
    - "Generează uP/uP.sim/sim_1/behav/xsim/testbench.hex"

vivado:
  steps:
    - "Deschide uP.xpr în Vivado"
    - "Rulează Run Simulation → Behavioral Simulation"
    - "Testbench-ul va încărca automat testbench.hex"
    - "Analizează rezultatele în waveform"
  version: "Vivado 2020.2+"

example_program:
  name: "Program simplu de test"
  file: "test.asm"
  content: |
    ; Program simplu de test
    START:
        VL R0, 5
        VL R1, 10
        ADD R2, R0, R1
        JMPZ STOP
        SUB R2, R2, R0
    STOP:
        HALT

requirements:
  software:
    - "C++17 sau mai nou"
    - "Xilinx Vivado 2020.2+"
    - "Visual Studio Code"
  os:
    - "Windows 10/11 sau Linux"

