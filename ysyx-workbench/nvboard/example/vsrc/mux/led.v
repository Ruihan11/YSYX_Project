module led(
  input clk,
  input rst,
  input [4:0] btn,    //buttons
  input [7:0] sw,     //switches
  output [15:0] ledr  //LEDs
);
  // reg [31:0] count;

  reg [8:0] empty = 0;
  reg y;
  always @(posedge clk) begin

      assign y=(((~sw[5])&(~sw[4]))&sw[0])
      |(((~sw[5])&(sw[4]))&sw[1])
      |(((sw[5])&(~sw[4]))&sw[2])
      |(((sw[5])&(sw[4]))&sw[3]);
    end
  

  assign ledr = {y,empty,sw[5:0]};
endmodule
