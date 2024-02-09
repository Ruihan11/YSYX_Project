module seg(
  input        clk,
  input        rst,
  input  [7:0] dout,
  output [7:0] o_seg0,
  output [7:0] o_seg1,
  output [7:0] o_seg2,
  output [7:0] o_seg3,
  output [7:0] o_seg4,
  output [7:0] o_seg5,
  output [7:0] o_seg6,
  output [7:0] o_seg7
);

wire [7:0] segs [15:0];
assign segs[0] = 8'b11111100;
assign segs[1] = 8'b01100000;
assign segs[2] = 8'b11011010;
assign segs[3] = 8'b11110010;
assign segs[4] = 8'b01100110;
assign segs[5] = 8'b10110110;
assign segs[6] = 8'b10111110;
assign segs[7] = 8'b11100000;
assign segs[8] = 8'b11111110;
assign segs[9] = 8'b11100110;
assign segs[10] = 8'b11101110;
assign segs[11] = 8'b00111110;
assign segs[12] = 8'b10011100;
assign segs[13] = 8'b01111010;
assign segs[14] = 8'b10011110;
assign segs[15] = 8'b10001110;

reg [7:0] hex0;
reg [7:0] hex1;
reg [3:0] dout0;
reg [3:0] dout1;
assign dout0 = dout [3:0];
assign dout1 = dout [7:4];

always @(posedge clk) begin
  
  case(dout0)
            4'b0000: hex0 = 8'b11111100;
            4'b0001: hex0 = 8'b01100000;
            4'b0010: hex0 = 8'b11011010;
            4'b0011: hex0 = 8'b11110010;
            4'b0100: hex0 = 8'b01100110;
            4'b0101: hex0 = 8'b10110110;
            4'b0110: hex0 = 8'b10111110;
            4'b0111: hex0 = 8'b11100000;
            4'b1000: hex0 = 8'b11111110;
            4'b1001: hex0 = 8'b11100110;
            4'b1010: hex0 = 8'b11101110;
            4'b1011: hex0 = 8'b00111110;
            4'b1100: hex0 = 8'b10011100;
            4'b1101: hex0 = 8'b01111010;
            4'b1110: hex0 = 8'b10011110;
            4'b1111: hex0 = 8'b10001110;
            default: hex0 = 8'b00000000; 
  endcase

  case(dout1)
            4'b0000: hex1 = 8'b11111100;
            4'b0001: hex1 = 8'b01100000;
            4'b0010: hex1 = 8'b11011010;
            4'b0011: hex1 = 8'b11110010;
            4'b0100: hex1 = 8'b01100110;
            4'b0101: hex1 = 8'b10110110;
            4'b0110: hex1 = 8'b10111110;
            4'b0111: hex1 = 8'b11100000;
            4'b1000: hex1 = 8'b11111110;
            4'b1001: hex1 = 8'b11100110;
            4'b1010: hex1 = 8'b11101110;
            4'b1011: hex1 = 8'b00111110;
            4'b1100: hex1 = 8'b10011100;
            4'b1101: hex1 = 8'b01111010;
            4'b1110: hex1 = 8'b10011110;
            4'b1111: hex1 = 8'b10001110;
            default: hex1 = 8'b00000000; 
  endcase

          
end


assign o_seg0 = ~hex0;
assign o_seg1 = ~hex1;
assign o_seg2 = 8'b11111111;
assign o_seg3 = 8'b11111111;
assign o_seg4 = 8'b11111111;
assign o_seg5 = 8'b11111111;
assign o_seg6 = 8'b11111111;
assign o_seg7 = 8'b11111111;


endmodule
