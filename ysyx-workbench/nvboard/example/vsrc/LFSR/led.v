module led(
  input clk,
  input rst,
  input [4:0] btn,    //buttons
  input [7:0] sw,     //switches
  output [15:0] ledr  //LEDs

);

reg       en;
reg       reset;
reg [7:0] dout;
assign en = btn[0];
assign reset = btn[1];

always @(posedge en or posedge reset) begin
    if (reset) begin
        dout = 8'b00000001;
        $display("rstdout  %b",dout);
    end else if (dout==8'b00000000) dout = 8'b00000001;
    else if(en) begin
    
    dout={(dout[4]^dout[3]^dout[2]^dout[0]),dout[7:1]};
    $display("clkdout  %b",dout);
    end 
end

assign ledr = {8'b00000000,dout};

endmodule
