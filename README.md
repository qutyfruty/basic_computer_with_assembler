> **Implementare de Basic Computer în SystemVerilog, cu assembler scris în C++.** > Assemblerul convertește codul sursă `.asm` în fișier `.hex` (Machine Code) pentru simularea din Vivado.

---

## Structura Proiectului

```text
├── assembler/
│   ├── main.cpp            # Sursa C++ pentru assembler
│   └── test.asm            # Fișier de test (Assembly code)
│
└── vivado/
    ├── uP.xpr              # Proiectul Xilinx Vivado
    ├── uP.srcs/
    │   ├── sim_1/new/
    │   │   └── testbench.sv        # Testbench principal
    │   └── sources_1/new/
    │       ├── processor.sv        # Top Module
    │       ├── control_block.sv    # Unitatea de control
    │       ├── alu.sv              # Arithmetic Logic Unit
    │       ├── register_file.sv    # Blocul de regiștri
    │       ├── instr_mem.sv        # Memoria de instrucțiuni
    │       ├── data_mem.sv         # Memoria de date
    │       ├── pc.sv               # Program Counter
    │       └── ... (mux.sv, ralu.sv, reg_zero_flag.sv)
    │
    └── uP.sim/.../testbench.hex    # Fișierul generat automat de assembler
```

---

## Assembler (C++)

Assemblerul este scris în **C++17** și are rolul de a traduce instrucțiunile mnemonice în cod mașină hexazecimal pe care procesorul îl poate executa.

### Funcționalități:
* ✅ **Curățare:** Elimină automat comentariile (`;`) și spațiile inutile.
* ✅ **Etichete:** Identifică și gestionează etichete (labels) pentru salturi.
* ✅ **Traducere:** Convertește instrucțiunile (ADD, SUB, JMP, etc.) în cod mașină.
* ✅ **Output:** Generează fișierul `.hex` pe 32 de biți pentru Vivado (`readmemh`).

### Formatul Instrucțiunii (32-bit)

| Opcode (4b) | Dest (4b) | Op0 (4b) | Op1 (4b) | Value (16b) |
| :---: | :---: | :---: | :---: | :---: |
| `[31:28]` | `[27:24]` | `[23:20]` | `[19:16]` | `[15:0]` |

**Exemplu:**
* **ASM:** `ADD R2, R0, R1`
* **Encoding:** `0001 0010 0000 0001 0000000000000000`

---

## Utilizare

### Compilare și Rulare Assembler

```bash
# 1. Navighează în folderul assembler
cd assembler

# 2. Compilează codul C++
g++ main.cpp -o assembler

# 3. Rulează executabilul
# Acesta va citi 'test.asm' și va genera 'testbench.hex' în folderul Vivado
./assembler
```

**Output așteptat:**
> Citește test.asm...  
> Generează ../vivado/uP.sim/sim_1/behav/xsim/testbench.hex...  

### 2. Simulare în Vivado

1.  Deschide fișierul `uP.xpr` în **Xilinx Vivado**.
2.  În panoul din stânga, apasă pe **Run Simulation** → **Run Behavioral Simulation**.
3.  Testbench-ul (`testbench.sv`) va încărca automat fișierul `.hex` generat anterior.
4.  Analizează semnalele în fereastra de waveform pentru a verifica execuția instrucțiunilor.

---

## Exemplu de Program (.asm)

Fișierul `test.asm` inclus demonstrează funcționalitățile de bază (încărcare valori, operații aritmetice, salt condiționat).

```assembly
; Program simplu de test pentru Basic Computer
START:
    VL R0, 5          ; Încarcă valoarea 5 în R0
    VL R1, 10         ; Încarcă valoarea 10 în R1
    ADD R2, R0, R1    ; R2 = R0 + R1 (ar trebui să fie 15)
    
    JMPZ STOP         ; Dacă rezultatul anterior e Zero, sari la STOP (nu sare aici)
    SUB R2, R2, R0    ; R2 = R2 - R0 (15 - 5 = 10)

STOP:
    HALT              ; Oprește execuția
```
