#include "verilated_vcd_c.h" //可选，如果要导出vcd则需要加上
#include "VbarrelShifter.h"
#include "stdio.h"
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
 
vluint64_t main_time = 0;  //initial 仿真时间
 
double sc_time_stamp()
{
    return main_time;
}

void printBinary(int num) {
    // Size of integer in bits (assuming int is 32-bit)
    int size = sizeof(int) * 8;
    
    // Loop through each bit of the integer from left to right
    for (int i = size - 1; i >= 0; i--) {
        // Extract the i-th bit using bitwise AND
        int bit = (num >> i) & 1;
        
        // Print the bit
        printf("%d", bit);
        
        // Print a space after every 4 bits for readability
        if (i % 4 == 0)
            printf(" ");
    }
    
    printf("\n"); // Print a newline at the end
}

int main(int argc, char **argv)
{
    Verilated::commandArgs(argc, argv); 
    Verilated::traceEverOn(true); //导出vcd波形需要加此语句
 
    VerilatedVcdC* tfp = new VerilatedVcdC; //导出vcd波形需要加此语句
 
    VbarrelShifter *barrelShifter = new VbarrelShifter("barrelShifter"); //调用VAccumulator.h里面的IO struct
 
    barrelShifter->trace(tfp, 0);   
    tfp->open("wave.vcd"); //打开vcd
    int i=0;
    
    

while (sc_time_stamp() < 3 && !Verilated::gotFinish()) { //控制仿真时间
        // printf("iteration %d\n", i); i++;
        int shamt = 0b110;
        int LR = 0b0;
        int AL = 0b0;
        int din = 0b00100001;
        barrelShifter->shamt = shamt;
        barrelShifter->LR=LR;
        barrelShifter->AL = AL;
        barrelShifter->din = din;
        barrelShifter->clk = !barrelShifter->clk;
		barrelShifter->eval();
       
		tfp->dump(main_time); //dump wave
        main_time++; //推动仿真时间
    }


    barrelShifter->final();
    tfp->close();
    delete barrelShifter;
 
    return 0;
}

