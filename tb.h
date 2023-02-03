#include <systemc.h>

SC_MODULE(tb) {
  sc_in<bool> clk;
  sc_out<bool> rst;
  sc_out< sc_int<16> > inp;
  sc_in< sc_int<16> > outp;

  // 以下这两个函数会被用在构造函数中，也可以叫做Thread
  void source(); // 1. reset inp   2. generate output
  void sink(); // 1. read data from FIR
  // 把Testbench里的线程分成source和sink是非常重要的, 特别是在涉及到生产者-消费者模型的时候, 你会在以后见识到

  FILE *outfp;
  // added in tutorial 5 for timestamp -- start
//	sc_time start_time[64], end_time[64], clock_period;
  // added in tutorial 5 for timestamp -- end

  SC_CTOR(tb) {
    SC_CTHREAD(source, clk.pos());
    SC_CTHREAD(sink, clk.pos());
    // 这里没有reset_signal_is函数的调用，原因是测试床不需要reset信号
    // 没看到上面那个rst信号是output吗？rst信号是由tb产生的！
  }

};

