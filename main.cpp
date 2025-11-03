#include <iostream>   // Pentru std::cout, std::cerr
#include <string>     // Pentru std::string
#include <cstdint>    // Pentru uint32_t
#include <fstream>    // Pentru std::ifstream, std::ofstream (fișiere)
#include <sstream>    // Pentru std::stringstream (parsare linii)
#include <iomanip>    // Pentru std::hex, std::setw, std::setfill
#include <map>        // Pentru std::map (harta de etichete)

/**
 * @brief Funcție ajutătoare pentru a curăța o linie:
 * - Elimină comentariile (de la ';')
 * - Elimină spațiile și TAB-urile de la început și sfârșit
 */
std::string curataLinie(std::string linie) {
    // Găsește comentariul și îl elimină
    size_t comment_pos = linie.find(';');
    if (comment_pos != std::string::npos) {
        linie = linie.substr(0, comment_pos);
    }

    // Elimină spațiile și tab-urile de la început
    // " \t\n\r\f\v" acoperă toate tipurile de spații albe
    linie.erase(0, linie.find_first_not_of(" \t\n\r\f\v"));

    // Elimină spațiile și tab-urile de la sfârșit
    linie.erase(linie.find_last_not_of(" \t\n\r\f\v") + 1);

    return linie;
}

/**
 * @brief Funcție ajutătoare pentru a verifica dacă un string e un număr
 */
bool esteNumar(const std::string& s) {
    if(s.empty()) return false;
    for(char const &c : s) {
        // Verifică dacă fiecare caracter este o cifră
        if(std::isdigit(c) == 0) return false;
    }
    return true;
}


int main() {

    std::string numeFisierIntrare = "test.asm";
    std::string numeFisierIesire = "uP/uP.sim/sim_1/behav/xsim/testbench.hex";

    
    std::cout << "Se ruleaza cu intrarea: " << numeFisierIntrare << std::endl;
    std::cout << "Se scrie la iesirea:  " << numeFisierIesire << std::endl;

    // Harta pentru a stoca etichetele și adresele lor
    std::map<std::string, uint32_t> hartaEtichete;

    // ====================================================================
    // --- PRIMA TRECERE: Construirea hărții de etichete ---
    // ====================================================================

    std::ifstream fisierIntrare(numeFisierIntrare);
    if (!fisierIntrare.is_open()) {
        std::cerr << "Eroare: Nu am putut deschide fisierul de intrare: " << numeFisierIntrare << std::endl;
        return 1;
    }

    std::cout << "Prima trecere: Cautare etichete..." << std::endl;
    std::string linie;
    uint32_t numarAdresa = 0; // Contorul de adrese (numărul instrucțiunii)

    while (std::getline(fisierIntrare, linie)) {
        linie = curataLinie(linie);
        if (linie.empty()) {
            continue; // Ignoră liniile goale
        }

        // Verifică dacă linia conține o etichetă (ex: "bucla:")
        size_t label_pos = linie.find(':');
        if (label_pos != std::string::npos) {
            std::string eticheta = linie.substr(0, label_pos);
            // Curăță eticheta de spații (ex: " bucla :")
            eticheta.erase(0, eticheta.find_first_not_of(" \t"));
            eticheta.erase(eticheta.find_last_not_of(" \t") + 1);

            if (hartaEtichete.count(eticheta)) {
                std::cerr << "Eroare: Eticheta '" << eticheta << "' este definita de mai multe ori." << std::endl;
                fisierIntrare.close();
                return 1;
            }

            // Adaugă eticheta în hartă, pointând la adresa curentă
            hartaEtichete[eticheta] = numarAdresa;
            std::cout << "  > Gasit eticheta '" << eticheta << "' la adresa 0x" << std::hex << numarAdresa << std::dec << std::endl;

            // Elimină eticheta din linie
            linie = linie.substr(label_pos + 1);
            linie = curataLinie(linie);
        }

        // Dacă linia NU este goală DUPĂ ce am scos eticheta,
        // înseamnă că e o instrucțiune, deci incrementăm adresa.
        if (!linie.empty()) {
            numarAdresa++;
        }
    }
    fisierIntrare.close();
    std::cout << "Prima trecere finalizata. " << hartaEtichete.size() << " etichete gasite." << std::endl;


    // ====================================================================
    // --- A DOUA TRECERE: Asamblarea codului ---
    // ====================================================================

    std::cout << "A doua trecere: Asamblare cod..." << std::endl;
    // Deschide fișierele din nou
    fisierIntrare.open(numeFisierIntrare);
    std::ofstream fisierIesire(numeFisierIesire);

    if (!fisierIntrare.is_open() || !fisierIesire.is_open()) {
        std::cerr << "Eroare: Nu am putut redeschide fisierele pentru a doua trecere." << std::endl;
        return 1;
    }

    std::string opcode_citit;
    int numarLinieCurenta = 0;

    while (std::getline(fisierIntrare, linie)) {
        numarLinieCurenta++;
        linie = curataLinie(linie);

        // Elimină eticheta (dacă există) din linie
        size_t label_pos = linie.find(':');
        if (label_pos != std::string::npos) {
            linie = linie.substr(label_pos + 1);
            linie = curataLinie(linie);
        }

        if (linie.empty()) {
            continue; // Ignoră liniile goale sau cele care conțineau doar etichete
        }

        // Folosim stringstream pentru a parsa linia (gestionează automat spații/tab-uri)
        std::stringstream ss(linie);
        ss >> opcode_citit;

        uint32_t instructiune_ansamblata = 0;
        uint32_t opcode = 0, dest = 0, op0 = 0, op1 = 0, value = 0;
        char a; // Pentru a citi 'R'
        std::string operandJMP; // Pentru a citi eticheta sau valoarea JMP

        if(opcode_citit == "NOP"){
            opcode = 0; dest = 0; op0 = 0; op1 = 0; value = 0;
        }
        else if(opcode_citit == "ADD"){
            opcode = 1;
            ss >> a >> dest; ss.ignore(); // ex: R2,
            ss >> a >> op0;  ss.ignore(); // ex: R0,
            ss >> a >> op1;               // ex: R1
            value = 0;
        }
        else if(opcode_citit == "SUB"){
            opcode = 2;
            ss >> a >> dest; ss.ignore();
            ss >> a >> op0;  ss.ignore();
            ss >> a >> op1;
            value = 0;
        }
        else if(opcode_citit == "MULT"){
            opcode = 3;
            ss >> a >> dest; ss.ignore();
            ss >> a >> op0;  ss.ignore();
            ss >> a >> op1;
            value = 0;
        }
        else if(opcode_citit == "SHIFT"){
            opcode = 4;
            ss >> a >> dest; ss.ignore();
            ss >> a >> op1;
            op0 = 0; value = 0;
        }
        else if(opcode_citit == "AND"){
            opcode = 6;
            ss >> a >> dest; ss.ignore();
            ss >> a >> op0;  ss.ignore();
            ss >> a >> op1;
            value = 0;
        }
        else if(opcode_citit == "OR"){
            opcode = 7;
            ss >> a >> dest; ss.ignore();
            ss >> a >> op0;  ss.ignore();
            ss >> a >> op1;
            value = 0;
        }
        else if(opcode_citit == "XOR"){
            opcode = 8;
            ss >> a >> dest; ss.ignore();
            ss >> a >> op0;  ss.ignore();
            ss >> a >> op1;
            value = 0;
        }
        else if(opcode_citit == "VL"){
            opcode = 10;
            ss >> a >> dest; // ex: R15
            ss.ignore();     // ignoră virgula
            ss >> value;     // ex: 0
            op0 = 0; op1 = 0;
        }
        else if(opcode_citit == "JMP"){
            opcode = 11;
            ss >> operandJMP; // Citim operandul (poate fi "5" sau "bucla")

            if (esteNumar(operandJMP)) {
                value = std::stoul(operandJMP); // E un număr
            } else {
                // E o etichetă, o căutăm în hartă
                if (hartaEtichete.count(operandJMP)) {
                    value = hartaEtichete[operandJMP];
                } else {
                    std::cerr << "Eroare [linia " << numarLinieCurenta << "]: Eticheta necunoscuta: '" << operandJMP << "'" << std::endl;
                    fisierIntrare.close();
                    fisierIesire.close();
                    return 1;
                }
            }
            op0 = 0; op1 = 0; dest = 0;
        }
        else if(opcode_citit == "JMPZ"){
            opcode = 12;
            ss >> operandJMP; // La fel ca la JMP

            if (esteNumar(operandJMP)) {
                value = std::stoul(operandJMP);
            } else {
                if (hartaEtichete.count(operandJMP)) {
                    value = hartaEtichete[operandJMP];
                } else {
                    std::cerr << "Eroare [linia " << numarLinieCurenta << "]: Eticheta necunoscuta: '" << operandJMP << "'" << std::endl;
                    fisierIntrare.close();
                    fisierIesire.close();
                    return 1;
                }
            }
            op0 = 0; op1 = 0; dest = 0;
        }
        else if(opcode_citit == "STORE"){
            opcode = 13;
            ss >> a >> op0; ss.ignore(); // ex: R15,
            ss >> a >> op1;              // ex: R2
            dest = 0; value = 0;
        }
        else if(opcode_citit == "LOAD"){
            opcode = 14;
            ss >> a >> op0; ss.ignore();
            ss >> a >> op1;
            dest = 0; value = 0;
        }
        else if(opcode_citit == "HALT"){
            opcode = 15;
            op0 = 0; op1 = 0; dest = 0; value = 0;
        }
        else {
            std::cerr << "Eroare [linia " << numarLinieCurenta << "]: Opcode necunoscut: '" << opcode_citit << "'" << std::endl;
            fisierIntrare.close();
            fisierIesire.close();
            return 1; // Oprește asamblarea la eroare
        }

        // --- Asamblarea biților ---
        instructiune_ansamblata = (opcode & 15) << 28 | (dest & 15) << 24 |
                                 (op0 & 15) << 20 | (op1 & 15) << 16 | (value & 65535);

        // --- Scrie în fișierul .hex ---
        // Formatează ca hexazecimal pe 8 caractere (32 biți), cu '0' la început
        fisierIesire << std::hex << std::setfill('0') << std::setw(8)
                     << instructiune_ansamblata << std::endl;

        // NU ne oprim la HALT pt ca citim pana la end of file
        /*
        if (opcode_citit == "HALT") {
            break;
        }
        */
    }

    fisierIntrare.close();
    fisierIesire.close();
    std::cout << "Asamblare finalizata." << std::endl;
    return 0;

}