#include <systemc.h>
#include "fir.h"
#include "tb.h"

SC_MODULE(SYSTEM) {
  // Module declarations
  tb *tb0;
  fir *fir0;
  // Local signal declarations
  sc_signal< sc_int<16> > inp_sig;
//  sc_signal< bool > inp_vld_sig;
//  sc_signal< bool > inp_rdy_sig;

  sc_signal< sc_int<16> > outp_sig;
//  sc_signal< bool > outp_vld_sig;
//  sc_signal< bool > outp_rdy_sig;

  sc_signal< bool > rst_sig;

  sc_clock clk_sig;

  SC_CTOR(SYSTEM)
    : clk_sig ("clk_sig", 10, SC_NS) // 第三个参数是时间单位，SC_NS表示纳秒，可以用SC_PS表示皮秒，这将产生周期为10NS的时钟信号
  {
    // Module instance signal connections
    tb0 = new tb("tb0");
    tb0->clk(clk_sig);
    tb0->rst(rst_sig);

    tb0->inp(inp_sig);
//    tb0->inp_vld(inp_vld_sig)
//    tb0->inp_rdy(inp_rdy_sig)

    tb0->outp(outp_sig);
//    tb0->outp_vld(outp_vld_sig)
//    tb0->outp_rdy(outp_rdy_sig)

    fir0 = new fir("fir0");
    fir0->clk(clk_sig);
    fir0->rst(rst_sig);

    fir0->inp(inp_sig);
//    fir0->inp_vld(inp_vld_sig)
//    fir0->inp_rdy(inp_rdy_sig)

    fir0->outp(outp_sig);
//    fir0->outp_vld(outp_vld_sig)
//    fir0->outp_rdy(outp_rdy_sig)
  }
  ~SYSTEM() {
    // Destructor
    delete tb0;
    delete fir0;
  }
};

// 以上代码仅仅只是定义了顶层模块，我们还需要定义执行入口
// C++的函数入口是main，SystemC中，则是sc_main
SYSTEM *top = NULL;

int sc_main(int argc, char *argv[]) {
  top = new SYSTEM("top");
  sc_start();
  return 0;
}

