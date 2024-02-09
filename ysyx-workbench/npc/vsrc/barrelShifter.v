module barrelShifter(
input       clk,
input       rst,
input [2:0] shamt,
input [7:0] din,
input reg   LR,
input reg   AL,

output [7:0] dout
);



always @(posedge clk or posedge rst) begin
    if (rst) begin
        dout = 8'b00000000;
    end else begin
    case (LR)
        1'b0: // Right Shift
            case (AL)
                1'b0: dout = din >> shamt; // Logical right shift
                1'b1: dout = $signed(din) >>> shamt; // Arithmetic right shift
            endcase
        1'b1: // Left Shift
            dout = din << shamt; // Logical left shift (arithmetic same for left)
    endcase
    $display("shamt %b \nLR    %b \nAL    %b \ndin   %b \ndout  %b \n",shamt,LR,AL,din,dout);
    end
end

endmodule