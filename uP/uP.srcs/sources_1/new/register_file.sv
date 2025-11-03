

module register_file(
        input logic clk,
        input logic [3:0] addr_operand0,
        input logic [3:0] addr_operand1,
        input logic wr_en,
        input logic [3:0] addr_result,
        input logic [15:0] data_write,
        
        output logic [15:0] operand0,
        output logic [15:0] operand1
    );
    
    logic [15:0] mem [0:15];
    
    always_comb begin
        operand0 = mem[addr_operand0];
    end
    
    assign operand1 = mem[addr_operand1];
    
    always_ff @(posedge clk) begin
        if(wr_en==1) begin
            mem[addr_result] <= data_write;
        end      
    end
    
endmodule
