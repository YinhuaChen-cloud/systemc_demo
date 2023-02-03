// checked
#include "tb.h"

// 1. reset inp   2. generate output
void tb::source() {
  // Reset
  inp.write(0);
  rst.write(1);
  wait(); // reset for 1 clock cycles
  rst.write(0);
  wait();

  sc_int<16> tmp;

  // Send stimulus to FIR
  for(int i = 0; i < 64; i++) {
    if(i > 23 && i < 29)      
      tmp = 256;
    else 
      tmp = 0;
    inp.write(tmp);
    wait(); // 64个周期
  }
}

// 1. read data from FIR
void tb::sink() {
  sc_int<16> indata;

  // Read output coming from DUT
  for (int i = 0; i < 64; i++) {
    indata = outp.read();
    wait();
    cout << i << ":\t" <<
      indata.to_int() << endl;
  }

  // End simulation
  sc_stop(); // 这个函数放在接收数据的地方调用，目的是为了保证该观察到的现象都观察到了
}

