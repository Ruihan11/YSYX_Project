module alu(
//   input clk,
//   input rst,
input [4:0] btn, 

input signed [3:0] a,
input signed [3:0] b,
// output [15:0] ledr,  //LEDs
output reg carry,
output reg zero,
output reg flow,
output signed [3:0] sum

);

reg [3:0] b_temp;
always @* begin
    // Default values
    carry = 1'b0;
    zero  = 1'b0;
    flow  = 1'b0;
    sum = 4'b0000;

    case (btn[2:0])
        3'b000: begin
                {carry , sum}= a + b;
                if ((a[3]==b[3])&&(sum[3]!==a[3])) flow=1;
        end
        3'b001: begin
                b_temp = ~b + 1;
                sum = a + b_temp;
                carry = (a<b);
                
                // if (sum[3] == 1) begin
                //     carry = 1'b1;
                // end
                // else begin 
                //     carry = 1'b0;
                // end
                if ((a[3]==b_temp[3])&&(sum[3]!==a[3])) flow=1;
        end
        3'b010: sum = ~a;     // Invert A
        3'b011: sum = a & b;   // Bitwise AND
        3'b100: sum = a | b;   // Bitwise OR
        3'b101: sum = a ^ b;   // Bitwise XOR
        3'b110: sum[0] = (a>b);
        3'b111: begin
                if (a==b)sum[0] = 1'b1;
                else sum[0] = 1'b0;
        end
        default: sum = 4'b0000; // Default case
        
    endcase
    if (sum==0) zero = 1;
    $display("a      %b %d\nb      %b %d\nsum    %b %d\ncarry  %b\nzero   %b\nflow   %b",a,a,b,b,sum,sum,carry,zero,flow);
end

// assign ledr = {carry,sum,btn[2:0],b,a};
endmodule