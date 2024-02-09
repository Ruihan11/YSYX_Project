#include "verilated_vcd_c.h" //可选，如果要导出vcd则需要加上
#include "Vencoder.h"
#include "stdio.h"
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
 
vluint64_t main_time = 0;  //initial 仿真时间
 
double sc_time_stamp()
{
    return main_time;
}
 
int main(int argc, char **argv)
{
    Verilated::commandArgs(argc, argv); 
    Verilated::traceEverOn(true); //导出vcd波形需要加此语句
 
    VerilatedVcdC* tfp = new VerilatedVcdC; //导出vcd波形需要加此语句
 
    Vencoder *encoder = new Vencoder("encoder"); //调用VAccumulator.h里面的IO struct
 
    encoder->trace(tfp, 0);   
    tfp->open("wave.vcd"); //打开vcd
    int i=0;
 
    while (sc_time_stamp() < 10 && !Verilated::gotFinish()) { //控制仿真时间
        printf("iteration %d\n", i); i++;
        int x = rand() % 8;
        int k =x;
        int en =1;
        encoder->en = en;
		encoder->x= 1<<k;


		encoder->eval();
		// printf("x = %d, en = %d, y = %d\n", x, en, encoder->y);
		tfp->dump(main_time); //dump wave
        main_time++; //推动仿真时间
    }
    encoder->final();
    tfp->close();
    delete encoder;
 
    return 0;
}

