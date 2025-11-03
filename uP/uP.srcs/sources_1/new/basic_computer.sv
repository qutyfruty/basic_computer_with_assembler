
module basic_computer(
        input logic clk,
        input logic rst
    );
    
    logic [31:0] w_data_read_instr;
    logic [7:0] w_i_addr_read;
    
    instr_mem mem_instr_0(
        .addr_read(w_i_addr_read),
        .data_read(w_data_read_instr)
    );
    
    logic [15:0] w_m_addr_read, w_m_addr_write, w_m_data_write, w_data_read;
    logic w_en;
    
    processor processor_0(
    .clk(clk),
    .rst(rst),
    .instr_mem_data_read(w_data_read_instr),
    .data_mem_data_read(w_data_read),
    
    .data_mem_addr_read(w_m_addr_read),
    .data_mem_addr_write(w_m_addr_write),
    .data_mem_data_write(w_m_data_write),
    .instr_mem_addr_read(w_i_addr_read),
    .data_mem_w_en(w_en)
    );
    
    data_mem data_mem_0(
        .clk(clk),
        .w_en(w_en),
        .addr_read(w_m_addr_read),
        .addr_write(w_m_addr_write),
        .data_write(w_m_data_write),
        
        .data_read(w_data_read)
    );
    
endmodule
