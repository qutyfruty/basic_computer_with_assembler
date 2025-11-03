
`timescale 1ns / 1ps

module testbench;

    // --- Testbench Parameters ---
    parameter CLK_PERIOD = 10; // Clock period (10 ns)

    // --- Testbench Signals ---
    logic clock;
    logic reset;

    // --- Instantiate the Device Under Test (DUT) ---
    basic_computer dut (
        .clk(clock),
        .rst(reset)
    );

    // --- Clock Generator ---
    initial begin
        clock = 0;
        forever #(CLK_PERIOD / 2) clock = ~clock;
    end
    
    // --- Reset Signal ---
    initial begin
        reset=1;
        #30 reset=0;
        #2000 $stop;
    end

endmodule