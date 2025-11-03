
module ralu(
        input logic clk,
        input logic [3:0] opcode,
        input logic [3:0] addr_operand0,
        input logic [3:0] addr_operand1,
        input logic w_en,
        input logic [3:0] addr_result,
        input logic [15:0] data_mem_data_read,
        input logic [15:0] instr_value,
        
        output logic [15:0] operand0,
        output logic [15:0] operand1,
        output logic [15:0] result,
        output logic zero_flag
    );
    
logic [15:0] reg_file_op1, alu_zero; // din ce modul iese si cum se numeste
    
    register_file register_file_0(
        .clk(clk),
        .addr_operand0(addr_operand0),
        .addr_operand1(addr_operand1),
        .wr_en(w_en),
        .addr_result(addr_result),
        .data_write(result),
        .operand0(operand0),
        .operand1(reg_file_op1)
    );
    
    // de unde se ia valoarea pt instructiuni (in dependenta de opcode)
    // daca din reg file, instructiune sau memorie
    mux mux_0(
        .in0(0),
        .in1(reg_file_op1),
        .in2(reg_file_op1),
        .in3(reg_file_op1),
        .in4(reg_file_op1),
        .in5(0),
        .in6(reg_file_op1),
        .in7(reg_file_op1),
        .in8(reg_file_op1),
        .in9(0),
        .in10(instr_value),
        .in11(instr_value),
        .in12(instr_value),
        .in13(reg_file_op1),
        .in14(data_mem_data_read),
        .in15(0),
        .sel(opcode),
        .out(operand1)
    );
    
    alu  alu0(
        .opcode(opcode),
        .operand0(operand0),
        .operand1(operand1),
        .result(result),
        .zero(alu_zero)
    );
    
    reg_zero_flag  reg_z0(
        .clk(clk),
        .in(alu_zero),
        .out(zero_flag)
    );
    
    
endmodule