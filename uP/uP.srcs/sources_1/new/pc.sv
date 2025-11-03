
module pc(
    input logic clk,
    input logic rst, 
    input logic en,
    input logic do_jump,
    input logic [7:0] jump_value,
    output logic [7:0] pc
    );
    
    always_ff @(posedge clk) begin 
        if(rst==1) begin
            pc<=0;
        end
        else begin
            if(en==1) begin
                if(do_jump==1) begin
                    pc<=jump_value;
                end
                else begin
                    pc<=pc+1;
                end
            end
        end
    end
    
endmodule
