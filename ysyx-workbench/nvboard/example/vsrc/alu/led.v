module led(
  input clk,
  input rst,
  input [4:0] btn,    //buttons
  input [7:0] sw,     //switches
  output [15:0] ledr  //LEDs

  /*
  sw -- a and b
  btn - mode
  led - mode 0s  flow zero carry/borrow(go to seg) sum(go to seg)

  */
);

reg [2:0] mode;
reg carry;
reg zero;
reg flow;
reg [3:0] sum;
reg [3:0] a;
reg [3:0] b;
reg [3:0] b_temp;

always @(posedge clk or posedge btn[2]) begin
    if (btn[2]) begin
      mode = 3'b0;
    end
    else begin

    carry=0;
    zero=0;
    flow=0;

      /* mode input */
    if (btn[0]) mode[0]=1'b1;
    if (btn[1]) mode[1]=1'b1;
    if (btn[4]) mode[2]=1'b1;

    a = sw[3:0];
    b = sw[7:4];

    case (mode)
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


    end
    end


assign ledr = {mode,6'b0,flow,zero,carry,sum};
endmodule
