#include "verilated_vcd_c.h" //可选，如果要导出vcd则需要加上
#include "Vmux.h"
#include "stdio.h"
#include <stdlib.h>
 
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
 
    Vmux *mux = new Vmux("mux"); //调用VAccumulator.h里面的IO struct
 
    mux->trace(tfp, 0);   
    tfp->open("wave.vcd"); //打开vcd
 
    while (sc_time_stamp() < 5 && !Verilated::gotFinish()) { //控制仿真时间   
        int a = rand() & 1;
		int b = rand() & 1;
        int c = rand() & 1;
		int d = rand() & 1;
        int s1 = 0;
        int s0 = 0;
		mux->a = a;
		mux->b = b;
        mux->c = c;
		mux->d = d;
        mux->s1 = s1;
        mux->s0 = s0;
		mux->eval();
        printf("a = %d, b = %d, c = %d, d = %d, s = %d%d, y = %d\n", a, b, c, d, s1,s0, mux->y);
        tfp->dump(main_time); //dump wave
        main_time++; //推动仿真时间 	
    }
    while (sc_time_stamp() < 10 && !Verilated::gotFinish()) { //控制仿真时间
        
        int a = rand() & 1;
		int b = rand() & 1;
        int c = rand() & 1;
		int d = rand() & 1;
        int s1 = 0;
        int s0 = 1;
		mux->a = a;
		mux->b = b;
        mux->c = c;
		mux->d = d;
        mux->s1 = s1;
        mux->s0 = s0;
		mux->eval();
        printf("a = %d, b = %d, c = %d, d = %d, s = %d%d, y = %d\n", a, b, c, d, s1,s0, mux->y);
        tfp->dump(main_time); //dump wave
        main_time++; //推动仿真时间 	
    }
    while (sc_time_stamp() < 15 && !Verilated::gotFinish()) { //控制仿真时间
        
        int a = rand() & 1;
		int b = rand() & 1;
        int c = rand() & 1;
		int d = rand() & 1;
        int s1 = 1;
        int s0 = 0;
		mux->a = a;
		mux->b = b;
        mux->c = c;
		mux->d = d;
        mux->s1 = s1;
        mux->s0 = s0;
		mux->eval();
        printf("a = %d, b = %d, c = %d, d = %d, s = %d%d, y = %d\n", a, b, c, d, s1,s0, mux->y);
        tfp->dump(main_time); //dump wave
        main_time++; //推动仿真时间 	
    }
    while (sc_time_stamp() < 20 && !Verilated::gotFinish()) { //控制仿真时间
        
        int a = rand() & 1;
		int b = rand() & 1;
        int c = rand() & 1;
		int d = rand() & 1;
        int s1 = 1;
        int s0 = 1;
		mux->a = a;
		mux->b = b;
        mux->c = c;
		mux->d = d;
        mux->s1 = s1;
        mux->s0 = s0;
		mux->eval();
        printf("a = %d, b = %d, c = %d, d = %d, s = %d%d, y = %d\n", a, b, c, d, s1,s0, mux->y);
        tfp->dump(main_time); //dump wave
        main_time++; //推动仿真时间 	
    }
    
    mux->final();
    tfp->close();
    delete mux;
 
    return 0;
}

