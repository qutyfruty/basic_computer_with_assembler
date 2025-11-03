; Program de test
start:
  VL R1, 10
  VL R2, 2

bucla:
  SUB R1, R1, R2
  JMPZ final
  JMP bucla

final:
  HALT