
module mux(
        input logic [3:0] sel,
        input logic [15:0] in0,
        input logic [15:0] in1,
        input logic [15:0] in2,
        input logic [15:0] in3,
        input logic [15:0] in4,
        input logic [15:0] in5,
        input logic [15:0] in6,
        input logic [15:0] in7,
        input logic [15:0] in8,
        input logic [15:0] in9,
        input logic [15:0] in10,
        input logic [15:0] in11,
        input logic [15:0] in12,
        input logic [15:0] in13,
        input logic [15:0] in14,
        input logic [15:0] in15,
        
        output logic [15:0] out
    );
    
    always_comb begin
        case(sel)
            0: out=in0;
            1: out=in1;
            2: out=in2;
            3: out=in3;
            4: out=in4;
            5: out=in5;
            6: out=in6;
            7: out=in7;
            8: out=in8;
            9: out=in9;
            10: out=in10;
            11: out=in11;
            12: out=in12;
            13: out=in13;
            14: out=in14;
            15: out=in15;
            default: out=0;
            
        endcase
    end
    
    
endmodule
