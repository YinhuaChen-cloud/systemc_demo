// checked
#include <systemc.h>
SC_MODULE(fir) {
  sc_in<bool> clk; // 时钟是输入信号，为bool类型
  sc_in<bool> rst; 
  sc_in< sc_int<16> > inp;
  sc_out< sc_int<16> > outp;

  void fir_main(); // 这里只是一个函数声明，我们可以在另外一个文件里实现函数细节，毕竟，你不希望把复杂的电路设计都放在一个文件里，不是吗？

  SC_CTOR(fir)  {
    SC_CTHREAD(fir_main, clk.pos()); // 两个参数，第二个参数表示时钟上升沿敏感
    reset_signal_is(rst, true); 
  }

};

