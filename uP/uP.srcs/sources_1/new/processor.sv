module processor(
    input logic clk,
    input logic rst,
    input logic [31:0] instr_mem_data_read,
    input logic [15:0] data_mem_data_read,
    
    output logic [15:0] data_mem_addr_read,
    output logic [15:0] data_mem_addr_write,
    output logic [15:0] data_mem_data_write,
    output logic [7:0] instr_mem_addr_read,
    output logic data_mem_w_en
);
    
    logic controlX_ralu_en, zero_raluXcontrol;
    
ralu ralu_0(
    .clk(clk),
    .opcode(instr_mem_data_read[31:28]),
    .addr_operand0(instr_mem_data_read[23:20]),
    .addr_operand1(instr_mem_data_read[19:16]),
    .w_en(controlX_ralu_en),
    .addr_result(instr_mem_data_read[27:24]),
    .data_mem_data_read(data_mem_data_read),
    .instr_value(instr_mem_data_read[15:0]),
    .operand0(data_mem_addr_read),
    .operand1(data_mem_addr_write),
    .result(data_mem_data_write),
    .zero_flag(zero_raluXcontrol)
);
    
    logic pc_enXcontrol, pc_doXcontrol;
    
pc pc_0(
    .clk(clk),
    .rst(rst), 
    .en(pc_enXcontrol),
    .do_jump(pc_doXcontrol),
    .jump_value(data_mem_data_write[7:0]),
    .pc(instr_mem_addr_read)
    );
    
control_block control0(
    .opcode(instr_mem_data_read[31:28]),
    .zero_flag(zero_raluXcontrol),
    .ralu_w_en(controlX_ralu_en),
    .pc_en(pc_enXcontrol),
    .do_jump(pc_doXcontrol),
    .data_mem_w_en(data_mem_w_en)
);
    
endmodule
