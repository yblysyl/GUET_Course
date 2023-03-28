/*
 * GeekOS C code entry point
 * Copyright (c) 2001,2003,2004 David H. Hovemeyer <daveho@cs.umd.edu>
 * Copyright (c) 2003, Jeffrey K. Hollingsworth <hollings@cs.umd.edu>
 * Copyright (c) 2004, Iulian Neamtiu <neamtiu@cs.umd.edu>
 * $Revision: 1.51 $
 *
 * This is free software.  You are permitted to use,
 * redistribute, and modify it as specified in the file "COPYING".
 */

#include <geekos/bootinfo.h>
#include <geekos/string.h>
#include <geekos/screen.h>
#include <geekos/mem.h>
#include <geekos/crc32.h>
#include <geekos/tss.h>
#include <geekos/int.h>
#include <geekos/kthread.h>
#include <geekos/trap.h>
#include <geekos/timer.h>
#include <geekos/keyboard.h>
#include <geekos/dma.h>
#include <geekos/ide.h>
#include <geekos/floppy.h>
#include <geekos/pfat.h>
#include <geekos/vfs.h>
#include <geekos/user.h>
#include <geekos/paging.h>


/*
 * Define this for a self-contained boot floppy
 * with a PFAT filesystem.  (Target "fd_aug.img" in
 * the makefile.)
 */
/*#define FD_BOOT*/

#ifdef FD_BOOT
#  define ROOT_DEVICE "fd0"
#  define ROOT_PREFIX "a"
#else
#  define ROOT_DEVICE "ide0"
#  define ROOT_PREFIX "c"
#endif

#define INIT_PROGRAM "/" ROOT_PREFIX "/shell.exe"



static void Mount_Root_Filesystem(void);
static void Spawn_Init_Process(void);

/*
 * Kernel C code entry point.
 * Initializes kernel subsystems, mounts filesystems,
 * and spawns init process.
 */
void Main(struct Boot_Info* bootInfo)
{
    Init_BSS();
    Init_Screen();
    Init_Mem(bootInfo);
    Init_CRC32();
    Init_TSS();
    Init_Interrupts();
    Init_VM(bootInfo);
    Init_Scheduler();
    Init_Traps();
    Init_Timer();
    Init_Keyboard();
    Init_DMA();
    Init_Floppy();
    Init_IDE();
    Init_PFAT();

    Mount_Root_Filesystem();

    Set_Current_Attr(ATTRIB(BLACK, GREEN|BRIGHT));
    Print("Welcome to GeekOS!\n");
    Set_Current_Attr(ATTRIB(BLACK, GRAY));

    //Éú³ÉÒ»žöœø³Ì
    Spawn_Init_Process();

    /* Now this thread is done. */
    Exit(0);
}



static void Mount_Root_Filesystem(void)
{
    if (Mount(ROOT_DEVICE, ROOT_PREFIX, "pfat") != 0)
	Print("Failed to mount /" ROOT_PREFIX " filesystem\n");
    else
	Print("Mounted /" ROOT_PREFIX " filesystem!\n");

    Init_Paging();
}






static void Spawn_Init_Process(void)
{
    int rc;
    struct Kernel_Thread *initProcess;

    /* Load and run a.exe, the "init" process */
    Print("Spawning init process (%s)\n", INIT_PROGRAM);
    rc = Spawn("/c/shell.exe", "/c/shell.exe",
	&initProcess);


    if (rc != 0) {
	Print("Failed to spawn init process: error code = %d\n",rc);
    } else {
	/* Wait for it to exit */
	int exitCode = Join(initProcess);
	Print("Init process exited with code %d\n", exitCode);
    }
}
