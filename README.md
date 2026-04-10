# Basic Computer Architecture & Assembler

---

## Română

### 📖 Descriere
Proiectul constă într-o microarhitectură de procesor implementată în **SystemVerilog**, împreună cu un **Assembler scris în C++**. Acesta traduce codul sursă din limbaj de asamblare (`.asm`) în cod mașină (`.hex`) pentru simularea în Vivado.

### 🛠️ Structura Proiectului
* **assembler/**: Conține `main.cpp` (codul sursă al translatorului) și `test.asm`.
* **vivado/**: Conține fișierele SystemVerilog (`alu.sv`, `control_block.sv`, `processor.sv` etc.) și proiectul Xilinx.

### 📑 Formatul Instrucțiunii (32-bit)
| Opcode (4b) | Dest (4b) | Op0 (4b) | Op1 (4b) | Value (16b) |
| :---: | :---: | :---: | :---: | :---: |
| `[31:28]` | `[27:24]` | `[23:20]` | `[19:16]` | `[15:0]` |

* **Opcode:** Identifică operația (ex: `0001` pentru ADD).
* **Dest/Op0/Op1:** Adresele regiștrilor utilizați.
* **Value:** Valoare imediată pe 16 biți pentru instrucțiuni de tip `VL` (Load Value).

### 🚀 Utilizare Rapidă
1. **Compilare Assembler:** `g++ main.cpp -o assembler` în folderul `assembler/`.
2. **Generare Cod:** `./assembler` (citește `test.asm` și exportă `testbench.hex`).
3. **Simulare:** Deschide proiectul în Vivado și rulează **Behavioral Simulation**.

---

## English

### 📖 Description
This project features a processor microarchitecture implemented in **SystemVerilog**, supported by a **custom C++ Assembler**. It provides a full flow from writing assembly code (`.asm`) to generating machine code (`.hex`) for Vivado simulations.

### 🛠️ Project Structure
* **assembler/**: Includes `main.cpp` (the translator source code) and `test.asm`.
* **vivado/**: Includes SystemVerilog modules (`alu.sv`, `control_block.sv`, `processor.sv`, etc.) and the Xilinx project files.

### 📑 Instruction Format (32-bit)
| Opcode (4b) | Dest (4b) | Op0 (4b) | Op1 (4b) | Value (16b) |
| :---: | :---: | :---: | :---: | :---: |
| `[31:28]` | `[27:24]` | `[23:20]` | `[19:16]` | `[15:0]` |

* **Opcode:** Identifies the operation (e.g., `0001` for ADD).
* **Dest/Op0/Op1:** Target and source register addresses.
* **Value:** 16-bit immediate value for `VL` (Load Value) instructions.

### 🚀 Quick Start
1. **Compile Assembler:** Run `g++ main.cpp -o assembler` inside the `assembler/` folder.
2. **Generate Hex:** Run `./assembler` to translate `test.asm` into `testbench.hex`.
3. **Simulation:** Open the project in Vivado and run **Behavioral Simulation**.

---

### 📝 Example Code (.asm)
```assembly
START:
    VL R0, 5          ; R0 = 5
    VL R1, 10         ; R1 = 10
    ADD R2, R0, R1    ; R2 = R0 + R1
    SUB R2, R2, R0    ; R2 = R2 - R0
STOP:
    HALT              ; Stop execution
