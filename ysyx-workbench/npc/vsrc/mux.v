module mux(a,b,c,d,s1,s0,y);

  input a,b,c,d,s1,s0;
  output y;

  assign y=(((~s1)&(~s0))&a)|(((~s1)&(s0))&b)|(((s1)&(~s0))&c)|(((s1)&(s0))&d); // 4 to 1 mux

endmodule
