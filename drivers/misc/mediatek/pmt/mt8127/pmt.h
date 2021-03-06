#ifndef _PMT_H
#define _PMT_H

#include "partition_define.h"
//mt6516_partition.h has defination
//mt6516_download.h define again, both is 20

#define MAX_PARTITION_NAME_LEN 64
#if defined(MTK_EMMC_SUPPORT) || defined(CONFIG_MTK_EMMC_SUPPORT)
/*64bit*/
typedef struct
{
    char name[MAX_PARTITION_NAME_LEN];     /* partition name */
    unsigned long long size;     						/* partition size */	
    unsigned long long part_id;                          /* partition region */
    unsigned long long offset;       					/* partition start */
    unsigned long long mask_flags;       				/* partition flags */

} pt_resident;
/*32bit*/
typedef struct 
{
    char name[MAX_PARTITION_NAME_LEN];     /* partition name */
    unsigned long  size;     						/* partition size */	
    unsigned long  offset;       					/* partition start */
    unsigned long mask_flags;       				/* partition flags */

} pt_resident32;
#else

typedef struct
{
    char name[MAX_PARTITION_NAME_LEN];     /* partition name */
    unsigned long long size;     						/* partition size */
	unsigned long long part_id;                          /* partition region */
    unsigned long long offset;       					/* partition start */
    unsigned long long mask_flags;       				/* partition flags */

} pt_resident;
#endif


#define DM_ERR_OK 0
#define DM_ERR_NO_VALID_TABLE 9
#define DM_ERR_NO_SPACE_FOUND 10
#define ERR_NO_EXIST  1

//Sequnce number


//#define PT_LOCATION          4090      // (4096-80)
//#define MPT_LOCATION        4091            // (4096-81)
#define PT_SIG      0x50547633            //"PTv3"
#define MPT_SIG    0x4D505433           //"MPT3"
#define PT_SIG_SIZE 4
//#define is_valid_mpt(buf) ((*(unsigned int *)(buf))==MPT_SIG)
//#define is_valid_pt(buf) ((*(unsigned int *)(buf))==PT_SIG)
#define is_valid_pt(buf) (!memcmp(buf, "3vTP", 4))
#define is_valid_mpt(buf) (!memcmp(buf, "3TPM", 4))
#define RETRY_TIMES 5

/*MBR or EBR struct*/

struct MBR_EBR_struct{
    char xbr_name[8];
    int part_index[4];
};

#define XBR_COUNT 8
//extern struct MBR_EBR_struct MBR_EBR_px[XBR_COUNT];

struct DM_PARTITION_INFO_x {
    char part_name[MAX_PARTITION_NAME_LEN];             /* the name of partition */
    unsigned long long part_id;                 /* the region of partition */
    unsigned long long start_addr;                                  /* the start address of partition */
    unsigned long long part_len;                                    /* the length of partition */
    unsigned char visible;                              /* part_visibility is 0: this partition is hidden and CANNOT download */
                                                        /* part_visibility is 1: this partition is visible and can download */                                            
    unsigned char dl_selected;                                  /* dl_selected is 0: this partition is NOT selected to download */
                                                        /* dl_selected is 1: this partition is selected to download */
};

struct DM_PARTITION_INFO_PACKET_x {
    unsigned int pattern;
    unsigned int part_num;                              /* The actual number of partitions */
    struct DM_PARTITION_INFO_x part_info[PART_MAX_COUNT];
};

struct pt_info {
	int sequencenumber:8;
	int tool_or_sd_update:8;
	int mirror_pt_dl:4;   //mirror download OK
	int mirror_pt_has_space:4;
	int pt_changed:4;
	int pt_has_space:4;
};

#endif
   
