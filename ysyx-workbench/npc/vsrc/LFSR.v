module LFSR(
input       clk,
input       rst,
input reg   en,

output [7:0] dout
);



always @(posedge clk or posedge rst) begin
    if (rst) begin
        dout = 8'b00000001;
        $display("rstdout  %b",dout);
    end else if (dout==8'b00000000) dout = 8'b00000001;
    else if(en) begin
    
    dout={(dout[4]^dout[3]^dout[2]^dout[0]),dout[7:1]};
    $display("clkdout  %b",dout);
    end 
end

endmodule