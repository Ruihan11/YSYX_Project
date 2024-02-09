#include "verilated_vcd_c.h" //可选，如果要导出vcd则需要加上
#include "Vshifter.h"
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
 
    Vshifter *shifter = new Vshifter("shifter"); //调用VAccumulator.h里面的IO struct
 
    shifter->trace(tfp, 0);   
    tfp->open("wave.vcd"); //打开vcd
    int i=0;
    
    

while (sc_time_stamp() < 10 && !Verilated::gotFinish()) { //控制仿真时间
        // printf("iteration %d\n", i); i++;
        int mode = 0b001;
        int leftMost = 0b1;
        int inRegister = 0b01000000;
        shifter->mode = mode;
        shifter->inRegister=inRegister;
        shifter->leftMost = leftMost;
        shifter->clk = !shifter->clk;
		shifter->eval();
       
		tfp->dump(main_time); //dump wave
        main_time++; //推动仿真时间
    }

while (sc_time_stamp() < 20 && !Verilated::gotFinish()) { //控制仿真时间
        // printf("iteration %d\n", i); i++;
        int mode = 0b010;
        int leftMost = 1;
        shifter->mode = mode;
        shifter->leftMost = leftMost;
        shifter->clk = !shifter->clk;
		shifter->eval();
		tfp->dump(main_time); //dump wave
        main_time++; //推动仿真时间
    }
while (sc_time_stamp() < 30 && !Verilated::gotFinish()) { //控制仿真时间
        // printf("iteration %d\n", i); i++;
        int mode = 0b011;
        int leftMost = 1;
        shifter->mode = mode;
        shifter->leftMost = leftMost;
        shifter->clk = !shifter->clk;
		shifter->eval();
		tfp->dump(main_time); //dump wave
        main_time++; //推动仿真时间
    }
while (sc_time_stamp() < 40 && !Verilated::gotFinish()) { //控制仿真时间
        // printf("iteration %d\n", i); i++;
        int mode = 0b100;
        int leftMost = 1;
        shifter->mode = mode;
        shifter->leftMost = leftMost;
        shifter->clk = !shifter->clk;
		shifter->eval();
		tfp->dump(main_time); //dump wave
        main_time++; //推动仿真时间
    }
while (sc_time_stamp() < 50 && !Verilated::gotFinish()) { //控制仿真时间
        // printf("iteration %d\n", i); i++;
        int mode = 0b101;
        int leftMost = 1;
        shifter->mode = mode;
        shifter->leftMost = leftMost;
        shifter->clk = !shifter->clk;
		shifter->eval();
		tfp->dump(main_time); //dump wave
        main_time++; //推动仿真时间
    }
while (sc_time_stamp() < 60 && !Verilated::gotFinish()) { //控制仿真时间
        // printf("iteration %d\n", i); i++;
        int mode = 0b110;
        int leftMost = 1;
        shifter->mode = mode;
        shifter->leftMost = leftMost;
        shifter->clk = !shifter->clk;
		shifter->eval();
		tfp->dump(main_time); //dump wave
        main_time++; //推动仿真时间
    }
while (sc_time_stamp() < 70 && !Verilated::gotFinish()) { //控制仿真时间
        // printf("iteration %d\n", i); i++;
        int mode = 0b111;
        int leftMost = 1;
        shifter->mode = mode;
        shifter->leftMost = leftMost;
        shifter->clk = !shifter->clk;
		shifter->eval();
		tfp->dump(main_time); //dump wave
        main_time++; //推动仿真时间
    }
while (sc_time_stamp() < 80 && !Verilated::gotFinish()) { //控制仿真时间
        // printf("iteration %d\n", i); i++;
        int mode = 0b000;
        int leftMost = 1;
        shifter->mode = mode;
        shifter->leftMost = leftMost;
        shifter->clk = !shifter->clk;
		shifter->eval();
		tfp->dump(main_time); //dump wave
        main_time++; //推动仿真时间
    }




    shifter->final();
    tfp->close();
    delete shifter;
 
    return 0;
}

