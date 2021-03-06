// LOFAR_Station_Beamformed_Writer_LuMP0.h
// writes out whole subband LuMP pulsar format data
//_HIST  DATE NAME PLACE INFO
// 2011 Aug 18  James M Anderson  --MPIfR  Start
// 2012 Jan 28  JMA  --move file opening and closing to thread
// 2012 May 12  JMA  --RCUMODE is now per beamlet
// 2013 Feb 24  JMA  ---- changes to accomodate LuMP1 format
// 2013 Mar 09  JMA  ---- change to use uint32_t for LOFAR timestamp
// 2013 Jul 07  JMA  ---- add RA,Dec,Epoch info
// 2013 Jul 07  JMA  ---- add SourceName info
// 2013 Jul 25  JMA  ---- provide information about the number of channels
//                        recorded for the case when channels are missing
//                        (READ_DATA_FROM_PIPE)
// 2013 Aug 19  JMA  ---- convert to first sample offset in Base.h class

// Copyright (c) 2011,2012,2013,2014 James M. Anderson <anderson@mpifr-bonn.mpg.de>

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.



#ifndef LOFAR_Station_Beamformed_Writer_LuMP0_H
#define LOFAR_Station_Beamformed_Writer_LuMP0_H

// INCLUDES
#ifndef __STDC_CONSTANT_MACROS
#  define __STDC_CONSTANT_MACROS
#endif
#ifndef __STDC_LIMIT_MACROS
#  define __STDC_LIMIT_MACROS
#endif
#ifndef _ISOC99_SOURCE
#  define _ISOC99_SOURCE
#endif
#ifndef _GNU_SOURCE
#  define _GNU_SOURCE 1
#endif
#ifndef __USE_ISOC99
#  define __USE_ISOC99 1
#endif
#ifndef _ISOC99_SOURCE
#  define _ISOC99_SOURCE
#endif
#ifndef __USE_MISC
#  define __USE_MISC 1
#endif
#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif
#include <inttypes.h>
#include <limits>
#ifdef __cplusplus
#  include <cstddef>
#else
#  include <stddef.h>
#endif
#include <stdint.h>
// we want to use ISO C9X stuff
// we want to use some GNU stuff
// But this sometimes breaks time.h
#include <time.h>


#include "JMA_math.h"
#include "LOFAR_Station_Complex.h"
#include "LOFAR_Station_Common.h"
#include "LOFAR_Station_Beamformed_Writer_Base.h"
#include <stdio.h>
#include <stdlib.h>
#include "LOFAR_Station_Beamformed_Valid.h"








// set up a namespace area for stuff.
namespace MPIfR {

namespace LOFAR {

namespace Station {





//_CLASS  LOFAR_Station_Beamformed_Writer_LuMP0
class LOFAR_Station_Beamformed_Writer_LuMP0 :
        public LOFAR_Station_Beamformed_Writer_Base {
//_DESC  full description of class

//_FILE  files used and logical units used

//_LIMS  design limitations

//_BUGS  known bugs

//_CALL  list of calls

//_KEYS  

//_HIST  DATE NAME PLACE INFO

//_END


// NAMESPACE ISSUES    


public:
    LOFAR_Station_Beamformed_Writer_LuMP0(const char* const restrict filename_base_,
                                          const char* const restrict station_name_,
                                          const uint32_t reference_time_,
                                          const uint_fast16_t CLOCK_SPEED_IN_MHz_,
                                          const uint_fast32_t PHYSICAL_BEAMLET_OFFSET_,
                                          const uint_fast16_t NUM_Beamlets_,
                                          const uint_fast16_t NUM_Blocks_,
                                          const LOFAR_raw_data_type_enum DATA_TYPE_,
                                          const int32_t id_,
                                          const uint_fast32_t NUM_OUTPUT_CHANNELS_,
                                          const uint_fast16_t NUM_Output_Beamlets_,
                                          const uint_fast32_t* const restrict Physical_Beamlets_Array_,
                                          const uint_fast32_t* const restrict Physical_Subband_Array_,
                                          const uint_fast32_t* const restrict RCUMODE_Array_,
                                          const Real64_t* const restrict RightAscension_Array_,
                                          const Real64_t* const restrict Declination_Array_,
                                          const char* const * const restrict Epoch_Array_,
                                          const char* const * const restrict SourceName_Array_) throw();

    virtual ~LOFAR_Station_Beamformed_Writer_LuMP0();


    static const uint16_t LuMP_HEADER_SIZE = 4096;

protected:
    FILE* restrict * restrict fp_data;
    void* fp_data_void;
    
    uint_fast64_t num_raw_packet_commands_processed;

    uint_fast32_t NUM_FP_DATA;
    uint_fast32_t initialized;

    int_fast32_t status;
    LOFAR_Station_Beamformed_Valid_Writer* restrict valid_object;
    uint64_t pad_to_guarantee_64_bit_aligned;
    char LuMP_header[LuMP_HEADER_SIZE];

    virtual int_fast32_t do_work(LOFAR_Station_Beamformed_Writer_Base_Work_Enum work_code_copy) throw();

    void write_into_header(uint_fast32_t pos, const char* const format,
                           uint_fast32_t MAX_SIZE) throw();
    template <class T> void write_into_header(uint_fast32_t pos,
                                              const char* const format,
                                              uint_fast32_t MAX_SIZE,
                                              const T datap) throw();

private:

    static uint16_t VERSION() throw() {return uint16_t(MPIfR_LOFAR_STATION_SOFTWARE_VERSION);}
    static uint16_t WRITER_TYPE() throw() {return uint16_t(LOFAR_DOFF_LuMP0_OUT);}

    static const int LuMP_STATION_NAME_STR_SIZE = 32;



    int_fast32_t thread_constructor() restrict;
    int_fast32_t thread_destructor() restrict;
    int_fast32_t close_output_files() throw();
    int_fast32_t report_file_error(const char* const restrict msg) const throw();
    int_fast32_t write_header_init() throw();
    int_fast32_t write_header_start() throw();
    int_fast32_t write_header_end() throw();
    int_fast32_t write_standard_packets() throw();
    int_fast32_t write_partial_packet() throw();


    // prevent copying
    LOFAR_Station_Beamformed_Writer_LuMP0(const LOFAR_Station_Beamformed_Writer_LuMP0& a);
    LOFAR_Station_Beamformed_Writer_LuMP0& operator=(const LOFAR_Station_Beamformed_Writer_LuMP0& a);

    
};


// CLASS FUNCTIONS



// HELPER FUNCTIONS
int_fast32_t JD(int_fast32_t year, int_fast32_t month, int_fast32_t day);
double JD(int_fast32_t year, int_fast32_t month, int_fast32_t day,
          int_fast32_t hour, int_fast32_t minute, int_fast32_t second,
          double sec_fraction);
double MJD(int_fast32_t year, int_fast32_t month, int_fast32_t day,
           int_fast32_t hour, int_fast32_t minute, int_fast32_t second,
           double sec_fraction);

const char* const LuMP_Telescope_Name_Converter(const char* const station_name) throw();


// GLOBALS
#ifdef LOFAR_Station_Beamformed_Writer_LuMP0_H_FILE
#  define NUM(x) =x;
#else
#  define NUM(x)
#endif

extern const char* const LuMP_HEADER_BASE  NUM("HEADER     LuMP\nHDR_SIZE         \nOBS_ID                                  \nPRIMARY  unset                          \nSECONDARY unset                         \nFILE_NAME                                                                       \nFILE_SIZE 0                             \nFILE_NUMBER 1                           \nUTC_START 2011-05-11-15:00:00\nMJD_START 55692                                                                 \nOBS_OFFSET 0\nOBS_OVERLAP 0\nSOURCE                                  \nRA                                      \nDEC                                     \nTELESCOPE                               \nINSTRUMENT  LuMP\nFREQ                                    \nBW                                      \nTSAMP                                   \nNBIT     \nNDIM 2\nNPOL 2\nIN_USE 1\nNCHAN                                   \nBINARY_FORMAT                           \nPOL_ORDERING                            \nENDIAN       \nUTC_REFERENCE_TIME_T 0x                 \nUTC_OFFSET_START_LEADING 0                                   \nUTC_OFFSET_START_CENTER                                     \nSTATE                         \nLUMP_VERSION 0x               \nLUMP_MODE pulsar\nLUMP_SCALE 1                            \nANTENNA_SET                             \nFILTER_SELECTION                        \nREAD_DATA_FROM_PIPE       \nNCHAN_RECORDED                                   \n");
const uint_fast32_t LuMP_HEADER_BASE_HDR_SIZE_OFFSET      = 25;
const uint_fast32_t LuMP_HEADER_BASE_OBS_ID_OFFSET        = 41;
const uint_fast32_t LuMP_HEADER_BASE_FILE_NAME_OFFSET     = 167;
const uint_fast32_t LuMP_HEADER_BASE_FILE_SIZE_OFFSET     = 248;
const uint_fast32_t LuMP_HEADER_BASE_FILE_NUMBER_OFFSET   = 291;
const uint_fast32_t LuMP_HEADER_BASE_UTC_START_OFFSET     = 330;
const uint_fast32_t LuMP_HEADER_BASE_MJD_START_OFFSET     = 360;
const uint_fast32_t LuMP_HEADER_BASE_SOURCE_OFFSET        = 465;
const uint_fast32_t LuMP_HEADER_BASE_RA_OFFSET            = 502;
const uint_fast32_t LuMP_HEADER_BASE_DEC_OFFSET           = 544;
const uint_fast32_t LuMP_HEADER_BASE_TELESCOPE_OFFSET     = 591;
const uint_fast32_t LuMP_HEADER_BASE_FREQ_OFFSET          = 644;
const uint_fast32_t LuMP_HEADER_BASE_BW_OFFSET            = 683;
const uint_fast32_t LuMP_HEADER_BASE_TSAMP_OFFSET         = 727;
const uint_fast32_t LuMP_HEADER_BASE_NBIT_OFFSET          = 767;
const uint_fast32_t LuMP_HEADER_BASE_NDIM_OFFSET          = 777;
const uint_fast32_t LuMP_HEADER_BASE_NCHAN_OFFSET         = 801;
const uint_fast32_t LuMP_HEADER_BASE_BINARY_FORMAT_OFFSET = 850;
const uint_fast32_t LuMP_HEADER_BASE_POL_ORDERING_OFFSET  = 890;
const uint_fast32_t LuMP_HEADER_BASE_ENDIAN_OFFSET        = 925;
const uint_fast32_t LuMP_HEADER_BASE_UTC_REFERENCE_TIME_T_OFFSET       = 953;
const uint_fast32_t LuMP_HEADER_BASE_UTC_OFFSET_START_LEADING_OFFSET   = 998;
const uint_fast32_t LuMP_HEADER_BASE_UTC_OFFSET_START_CENTER_OFFSET    = 1059;
const uint_fast32_t LuMP_HEADER_BASE_STATE_OFFSET         = 1102;
const uint_fast32_t LuMP_HEADER_BASE_LUMP_VERSION_OFFSET  = 1140;
const uint_fast32_t LuMP_HEADER_BASE_LUMP_SCALE_OFFSET    = 1186;
const uint_fast32_t LuMP_HEADER_BASE_ANTENNA_SET_OFFSET   = 1228;
const uint_fast32_t LuMP_HEADER_BASE_FILTER_SELECTION_OFFSET           = 1274;
const uint_fast32_t LuMP_HEADER_BASE_READ_DATA_FROM_PIPE_OFFSET        = 1318;
const uint_fast32_t LuMP_HEADER_BASE_NCHAN_RECORDED_OFFSET= 1340;



}  // end namespace Station
}  // end namespace LOFAR
}  // end namespace MPIfR

#undef NUM
#endif // LOFAR_Station_Beamformed_Writer_LuMP0_H
