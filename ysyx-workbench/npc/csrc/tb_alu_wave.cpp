#include "verilated_vcd_c.h" //可选，如果要导出vcd则需要加上
#include "Valu.h"
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
 
    Valu *alu = new Valu("alu"); //调用VAccumulator.h里面的IO struct
 
    alu->trace(tfp, 0);   
    tfp->open("wave.vcd"); //打开vcd
    int i=0;
 
while (sc_time_stamp() < 1 && !Verilated::gotFinish()) { //控制仿真时间
        printf("\niteration %d\n", i); i++;
        // int a = rand() % 8;
        // int b = rand() % 8;
        int a = -7;
        int b = 9;
        int btn = 0;
        alu->a = a;
        alu->b = b;
        alu->btn=btn;
		alu->eval();
		tfp->dump(main_time); //dump wave
        main_time++; //推动仿真时间
    }

    // while (sc_time_stamp() < 5 && !Verilated::gotFinish()) { //控制仿真时间
    //     printf("\niteration %d\n", i); i++;
    //     int a = rand() % 8;
    //     int b = rand() % 8;
    //     // int a = -1;
    //     // int b = -2;
    //     int btn = 1;
    //     alu->a = a;
    //     alu->b = b;
    //     alu->btn=btn;
	// 	alu->eval();
	// 	tfp->dump(main_time); //dump wave
    //     main_time++; //推动仿真时间
    // }

    // while (sc_time_stamp() < 10 && !Verilated::gotFinish()) { //控制仿真时间
    //     printf("\niteration %d\n", i); i++;
    //     int a = - rand() % 8;
    //     int b = rand() % 8;
    //     // int a = -1;
    //     // int b = -2;
    //     int btn = 1;
    //     alu->a = a;
    //     alu->b = b;
    //     alu->btn=btn;
	// 	alu->eval();
	// 	tfp->dump(main_time); //dump wave
    //     main_time++; //推动仿真时间
    // }

    // while (sc_time_stamp() < 15 && !Verilated::gotFinish()) { //控制仿真时间
    //     printf("\niteration %d\n", i); i++;
    //     int a = rand() % 8;
    //     int b = - rand() % 8;
    //     // int a = -1;
    //     // int b = -2;
    //     int btn = 1;
    //     alu->a = a;
    //     alu->b = b;
    //     alu->btn=btn;
	// 	alu->eval();
	// 	tfp->dump(main_time); //dump wave
    //     main_time++; //推动仿真时间
    // }

    // while (sc_time_stamp() < 20 && !Verilated::gotFinish()) { //控制仿真时间
    //     printf("\niteration %d\n", i); i++;
    //     int a = - rand() % 8;
    //     int b = - rand() % 8;
    //     // int a = -1;
    //     // int b = -2;
    //     int btn = 1;
    //     alu->a = a;
    //     alu->b = b;
    //     alu->btn=btn;
	// 	alu->eval();
	// 	tfp->dump(main_time); //dump wave
    //     main_time++; //推动仿真时间
    // }
    
    alu->final();
    tfp->close();
    delete alu;
 
    return 0;
}

