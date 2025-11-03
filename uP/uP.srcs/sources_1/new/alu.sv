
module alu(
        input logic [0:3] opcode,
        input logic [0:15] operand0,
        input logic [0:15] operand1,
        
        output logic [0:15] result,
        output logic zero
    );
    
    always_comb begin
        case(opcode)
            0: result = 23; // NOP
            1: result = operand0 + operand1; //ADD
            2: result = operand0 - operand1; //SUB
            3: result = operand0 * operand1; //MULT
            4: result = operand1 >> 1; // SHIFT 1 RIGHT
            5: result = 23; //nu e implementat
            6: result = operand0 & operand1; // AND
            7: result = operand0 | operand1; // OR
            8: result = operand0 ^ operand1; //XOR
            9: result = 23; //nu e implementat
            10: result = operand1; // VALUE LOAD
            11: result = operand1; // JMP
            12: result = operand1; // JMPZ (daca e flagul verificam inainte)
            13: result = operand0; // WRITE MEM
            14: result = operand1; // READ MEM
            15: result = 0; // HALT
        endcase
    end
    
    assign zero = (result==0);
    
endmodule
