//#include <capnp/serialize.h>
#include "cereal/gen/c/log.capnp.h"
#include "cereal/gen/c/car.capnp.h"

// #include "capn.c"
// #include "capn-malloc.c"
// #include "capn-stream.c"

int main()
{
	uint8_t buf[4096];
  	ssize_t sz = 0;
  	int i;

    struct capn c;
    capn_init_malloc(&c);
    capn_ptr cr = capn_root(&c);
    struct capn_segment *cs = cr.seg;

	struct CarState_WheelSpeeds ws;



	ws.fl = 0.1;
	ws.fr = 0.2;
	ws.rl = 0.3;
	ws.rr = 0.4;

	ws.fl = 0.4;
	ws.fr = 0.3;
	ws.rl = 0.2;
	ws.rr = 0.1;

	CarState_WheelSpeeds_ptr pws = new_CarState_WheelSpeeds(cs);
	write_CarState_WheelSpeeds(&ws, pws);
	sz = capn_write_mem(&c, buf, sizeof(buf), 0 /* packed */);
	capn_free(&c);

	printf("write_CarState_WheelSpeeds: %f,%f,%f,%f\n", ws.fl, ws.fr, ws.rl, ws.rr);

	printf("data:\n");
	for(i=0; i<sz; i++) {
		printf(" %02x", buf[i]);
		if(i%16==0 && i>0 ) printf("\n");
	}
	printf("\n");

	struct capn rc;
    int init_mem_ret = capn_init_mem(&rc, buf, sz, 0 /* packed */);

	printf("init_mem_ret=%d sz=%d\n", init_mem_ret, sz);

	printf("data:\n");
 	for(i=0; i<sz; i++) {
		printf(" %02x", buf[i]);
		if(i%16==0 && i>0 ) printf("\n");
	}
    printf("\n");

    CarState_WheelSpeeds_ptr rroot;
    struct CarState_WheelSpeeds rws;
    rroot.p = capn_getp(capn_root(&rc), 0 /* off */, 1 /* resolve */);
    printf("buf_addr=%x, p.p=%x\n", buf, rroot.p);

    read_CarState_WheelSpeeds(&rws, rroot);

	printf("read_CarState_WheelSpeeds: %f,%f,%f,%f\n", rws.fl, rws.fr, rws.rl, rws.rr);

    capn_free(&rc);

	return 0;
}
