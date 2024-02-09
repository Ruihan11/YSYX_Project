module light(
  input clk,
  input rst_n,
  input en,
  output reg [15:0] led
);
  reg [31:0] count;
  always @(posedge clk) begin
    if (!rst_n) begin 
        led <= 16'b0000_0000_0000_0001;
    end
    else if (count == 5) begin
        led <= {led[14:0], led[15]};
    end
  end

  always @(posedge clk) begin
    if (!rst_n) begin 
        count <= 0; 
    end
    else if(count >= 5) begin
        count <= 32'b0;
    end
    else if(en) begin
        count <= count + 1;
    end
  end

endmodule
