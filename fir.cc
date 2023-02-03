// checked
#include "fir.h"

// Coefficients for each FIR
const sc_uint<8> coef[5] = {
  18,
  77,
  107,
  77,
  18
};

// FIR Main thread
void fir::fir_main(void) {
  // 可以在开头定义一些内部变量
  sc_int<16> taps[5];

  // reset_signal_is函数会在每个时钟沿检查rst信号，若有效，则fir_main会从头开始执行, 因此一开始的代码用于重置信号
  // Reset code
  // Reset internal variables
  for(int i = 0; i < 5; i++) {
    taps[i] = 0;
  }
  // Initialize handshake
//  inp_rdy.write(0);
//  outp_vld.write(0);
  outp.write(0);
  wait(); // 等待第一个时钟沿

  while(true) {
    // Read inputs
    // Algorithm code
    for(int i = 5-1; i > 0; i--) {
      taps[i] = taps[i-1];
    }
    // -------------- added in tutorial 4 -------------- start
//    inp_rdy.write(1);
//    do {
//      wait();
//    } while(!inp_vld.read());
    // -------------- added in tutorial 4 -------------- end
    taps[0] = inp.read();
    // -------------- added in tutorial 4 -------------- start
//    inp_rdy.write(0);
    // -------------- added in tutorial 4 -------------- end

    sc_int<16> val;
    for(int i = 0; i < 5; i++) {
      val += coef[i] * taps[i];
    }
    // Write outputs
    outp.write(val);
    wait(); // 等待下一个时钟沿
  }

}

