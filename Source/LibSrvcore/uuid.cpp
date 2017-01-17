#include "srvEngine.h"
#ifdef __GNUC__
#include<sys/time.h>
#include<stdio.h>
#define EPOCHFILETIME 11644473600000000ULL 
#else
#include<windows.h>
#include<time.h>
#define EPOCHFILETIME 11644473600000000Ui64
#endif

namespace utils 
{
    uint64_t get_time(){
#ifdef __GNUC__
        struct timeval tv;
        gettimeofday(&tv,NULL);
        uint64_t time = tv.tv_usec;
        time /= 1000;
        time += (tv.tv_sec * 1000);
        return time;
#else
        FILETIME filetime;
        uint64_t time = 0;
        GetSystemTimeAsFileTime(&filetime);

        time |= filetime.dwHighDateTime;
        time <<= 32;
        time |= filetime.dwLowDateTime;
        
        time /= 10;
        time -= EPOCHFILETIME;
        return time / 1000;
#endif
    }


    unique_id_t :: unique_id_t()
    {
        epoch_ = 0;
        time_ = 0;
        machine_ = 0;
        sequence_ = 0;
    }

    unique_id_t :: ~unique_id_t(){

    }


    void unique_id_t::set_epoch(uint64_t epoch){
        epoch_ = epoch;
    }


    void unique_id_t:: set_machine(int32_t machine){
        machine_ = machine;
    }


    int64_t unique_id_t :: generate(){
        int64_t value = 0;
        uint64_t time = get_time() - epoch_;

        //保留后41位时间
        value = time << 22;

        //中间十位是机器代码 

        value |= (machine_ & 0x3FF) << 12;

        //最后12位是squenceID
        value |= sequence_++ & 0xFFF;

        if (sequence_ == 0x1000){
            sequence_ = 0;
        }
        return value;
    }
}

/*


#define __TEST__
#ifdef __TEST__
#include<iostream>
void test() {
	utils::unique_id_t * u_id_ptr = new utils::unique_id_t();
	u_id_ptr->set_epoch(uint64_t(1367505795100));
	u_id_ptr->set_machine(int32_t(100));
	for (int i = 0; i < 1024; ++i) {
		std::cout << u_id_ptr->generate() << std::endl;
	}

}
#endif

*/


//int 
//main(int argc, const char *argv[])
//{
//    test();
//    return 0;
//}
