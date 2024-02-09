module led(
  input clk,
  input rst,
  input [4:0] btn,    //buttons
  input [7:0] sw,     //switches
  output [15:0] ledr  //LEDs
);


  reg [4:0] empty = 0;
  reg [2:0] y;
  integer i;
  always @(posedge clk) begin
      if (sw==0) y=0;

      for( i = 0; i <= 7; i = i+1)
          if(sw[i] == 1)  y = i[2:0];
      end

// led { output ----  en 8-bit-input}
  assign ledr = {y,empty,sw[7:0]};
endmodule
