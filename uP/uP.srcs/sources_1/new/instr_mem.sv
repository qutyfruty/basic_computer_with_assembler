
module instr_mem(
        input logic [7:0] addr_read,
        
        output logic [31:0] data_read
    );
    
    logic [31:0] mem [0:2**8-1];
    
    initial begin
        $readmemh("testbench.hex", mem);
    end
    
    assign data_read=mem[addr_read];
    
endmodule
