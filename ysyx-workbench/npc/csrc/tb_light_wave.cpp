#include <stdlib.h> //所有文件都要包含
#include <iostream> //所有文件都要包含
#include "verilated.h"     //Defines common routines
#include <verilated_vcd_c.h> //生成波形文件的API
#include "Vlight.h"          //在obj文件夹中
#include <cstdio>

#ifdef VM_TRACE         // --trace
static VerilatedVcdC* fp;      //to form *.vcd file
#endif

#define MAX_SIM_TIME 40  // 仿真总时钟边沿数
static Vlight* dut_ptr;   //定义一个类指针，对这个指针操作，相当于对这个module操作

//仿真信号定义
int main()
{
    dut_ptr = new Vlight;  //例化顶层模块

    //生产波形文件
    #ifdef VM_TRACE   
        ////// !!!  ATTENTION  !!!//////
        //  Call Verilated::traceEverOn(true) first.
        //  Then create a VerilatedVcdC object.    
        Verilated::traceEverOn(true);
        printf("Enabling waves ...\n");
        fp = new VerilatedVcdC;     //instantiating .vcd object   
        dut_ptr->trace(fp, 99);     //将两个类连接到一起
        fp->open("wave.vcd");   //记录到波形文件中
        fp->dump(0); //波形从0时刻开始
    #endif

    //仿真部分
    int cycle = 0;
    while (cycle < MAX_SIM_TIME) {

        //复位信号
        dut_ptr->rst_n = 0;
        if(cycle >= 4){
            dut_ptr->rst_n = 1;
        }

        //使能信号
        dut_ptr->en = 0;
        if(cycle >= 8 && cycle <= 20){
            dut_ptr->en = 1;
        }

        //时钟和控制信号
        dut_ptr->clk ^= 1; //clk 与 1 异或，翻转时钟
        dut_ptr->eval(); //更新模块的状态，每一个周期更新一次信号
        fp->dump(cycle);
        cycle++;
    }

#ifdef VM_TRACE
    fp->close();
    delete fp;
#endif
    delete dut_ptr;
    return 0;

}