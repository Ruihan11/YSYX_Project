module shifter(
input       clk,
input       rst,
input [2:0] mode,
input [7:0] inRegister,
input reg   leftMost,

output [7:0] regShifter,
output [15:0] ledr
);


always @(posedge clk or posedge rst) begin
    if (rst) begin
        regShifter = 8'b00000000;
    end else begin
    case (mode)
        3'b000: regShifter = 8'b00000000;
        3'b001: regShifter = inRegister;
        3'b010: regShifter = {1'b0,regShifter[7:1]};
        3'b011: regShifter = {regShifter[6:0],1'b0};
        3'b100: regShifter = {regShifter[7],regShifter[7:1]};
        3'b101: regShifter = {leftMost,regShifter[7:1]};
        3'b110: regShifter = {regShifter[0],regShifter[7:1]};
        3'b111: regShifter = {regShifter[6:0],regShifter[7]};
        default: regShifter = 8'b00000000; // Default case 
    endcase

    $display("mode %b\nregi %b",mode,regShifter);
    end
end

// assign ledr = {carry,sum,btn[2:0],b,a};
endmodule