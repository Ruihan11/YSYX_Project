module seg(
  input        clk,
  input        rst,
  input  [2:0] encoded,
  output [7:0] o_seg0,
  output [7:0] o_seg1,
  output [7:0] o_seg2,
  output [7:0] o_seg3,
  output [7:0] o_seg4,
  output [7:0] o_seg5,
  output [7:0] o_seg6,
  output [7:0] o_seg7
);

wire [7:0] segs [9:0];
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

reg [3:0] decimal;


always @(posedge clk) begin
  
  case(encoded)
            3'b000: decimal = 4'b0000; // Binary 0 converts to decimal 0
            3'b001: decimal = 4'b0001; // Binary 1 converts to decimal 1
            3'b010: decimal = 4'b0010; // Binary 2 converts to decimal 2
            3'b011: decimal = 4'b0011; // Binary 3 converts to decimal 3
            3'b100: decimal = 4'b0100; // Binary 4 converts to decimal 4
            3'b101: decimal = 4'b0101; // Binary 5 converts to decimal 5
            3'b110: decimal = 4'b0110; // Binary 6 converts to decimal 6
            3'b111: decimal = 4'b0111; // Binary 7 converts to decimal 7
            default: decimal = 4'b0000; // Default case (shouldn't happen)
  endcase
          
end

assign o_seg0 = ~segs[decimal];
assign o_seg1 = 8'b11111111;
assign o_seg2 = 8'b11111111;
assign o_seg3 = 8'b11111111;
assign o_seg4 = 8'b11111111;
assign o_seg5 = 8'b11111111;
assign o_seg6 = 8'b11111111;
assign o_seg7 = 8'b11111111;

// assign o_seg0 = ~segs[offset + 3'd0];
// assign o_seg1 = ~segs[offset + 3'd1];
// assign o_seg2 = ~segs[offset + 3'd2];
// assign o_seg3 = ~segs[offset + 3'd3];
// assign o_seg4 = ~segs[offset + 3'd4];
// assign o_seg5 = ~segs[offset + 3'd5];
// assign o_seg6 = ~segs[offset + 3'd6];
// assign o_seg7 = ~segs[offset + 3'd7];

endmodule
