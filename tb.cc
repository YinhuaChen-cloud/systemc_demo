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
    if(i > 23 && i < 29)       // 24, 25, 26, 27, 28
      tmp = 1;
    else 
      tmp = 0;
    inp.write(tmp);
    wait(); // 64个周期
  }
}

// 1. read data from FIR
void tb::sink() {
  sc_int<16> indata;

	char output_file[256];
	sprintf(output_file, "./output.dat");
	outfp = fopen(output_file, "w");
	if(NULL == outfp) {
		printf("Could not open output.dat for writing.\n");
		exit(1);
	}

  // Read output coming from DUT
  for (int i = 0; i < 64; i++) {
    indata = outp.read();
    wait();

		fprintf(outfp, "%d:\t%d\n", i, (int)indata);

    cout << i << ":\t" <<
      indata.to_int() << endl;
  }

	fclose(outfp);

  // End simulation
  sc_stop(); // 这个函数放在接收数据的地方调用，目的是为了保证该观察到的现象都观察到了
}

