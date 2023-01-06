	.globl  MTA_init
	.ent 	MTA_init
MTA_init:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 167, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end  MTA_init

	.globl  MTA_fork
	.ent 	MTA_fork
MTA_fork:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 2, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end  MTA_fork
	
	.globl  MTA_halt
	.ent 	MTA_halt

MTA_halt:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 170, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_halt


	.globl  MTA_wait
	.ent 	MTA_wait

MTA_wait:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 173, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_wait
	
	.globl  MTA_start
	.ent 	MTA_start
MTA_start:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 172, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_start

	.globl  MTA_barrier
	.ent 	MTA_barrier
MTA_barrier:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 171, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_barrier

	.globl  MTA_Dummy
	.ent 	MTA_Dummy
MTA_Dummy:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 171, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_Dummy	

	.globl  MTA_Printf
	.ent 	MTA_Printf
MTA_Printf:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 168, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_Printf	

	.globl  MTA_Stats
	.ent 	MTA_Stats
MTA_Stats:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 174, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_Stats

	.globl  MTA_getthreadID
	.ent 	MTA_getthreadID
MTA_getthreadID:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 162, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_getthreadID

	.globl fetch_and_decrement
	.ent fetch_and_decrement 2
fetch_and_decrement:
$repeat_fad:
	.frame $sp, 0, $26, 0
	mb
	ldq_l $0, 0($16)
	subq    $0, 1, $0               # subtract 1 and store on register 1
        stq_c   $0, 0($16)              # store new value
        beq     $0, $repeat_fad
        mb
        ret     $31, ($26), 1           # $0 holds original value on success
	.end fetch_and_decrement


	.globl  test_and_set
        .ent    test_and_set 2
test_and_set:
        .frame  $sp, 0, $26, 0
        .prologue  0
        mb                              # !!! Extra memory barrier - gch
        bis     $17, $17, $1
        ldq_l   $0, 0($16)              # load link the address
        bne     $0, $finish             # failed if $0 != 0 (lock value set)
        stq_c   $1, 0($16)              # store conditional value
        beq     $1, $redo               # failed if $1 == 0 (lock flag clear)
        mb
$finish:
        ret     $31, ($26), 1
$redo:
        br      test_and_set
        .end    test_and_set
	
	.globl  MTA_Bar_Stats
	.ent 	MTA_Bar_Stats
MTA_Bar_Stats:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 175, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_Bar_Stats

	.globl  MTA_Bar_IDEAL
	.ent 	MTA_Bar_IDEAL
MTA_Bar_IDEAL:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 192, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_Bar_IDEAL

	.globl MTA_Ideal_Lock_Acquire
	.ent   MTA_Ideal_Lock_Acquire

MTA_Ideal_Lock_Acquire:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6

	mov 190, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_Ideal_Lock_Acquire

	.globl MTA_Ideal_Lock_Release
 	.ent MTA_Ideal_Lock_Release
MTA_Ideal_Lock_Release:
	.frame  $sp, 0, $26
    .prologue 0
#    .loc 1 6
	
	wmb
	mov 191, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_Ideal_Lock_Release

	.globl MTA_Lock_Acquire
	.ent   MTA_Lock_Acquire
MTA_Lock_Acquire:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	.align 5
$L1: 	ldl_l 	$0, 0($16)
	beq 	$0, $L2
	mov 	178, $0
	call_pal 0x83
	br 	$L1
$L2:    bis 	$0, 1, $0
	stl_c 	$0, 0($16)
	beq 	$0, $L1
	mb 
	ret	($26)													   # 000006
	.end MTA_Lock_Acquire

	.globl MTA_Lock_Release
 	.ent MTA_Lock_Release
MTA_Lock_Release:
	.frame  $sp, 0, $26
        .prologue 0
#        .loc 1 6
	
	wmb
	stl	$31, 0($16)
	ret	($26)													   # 000006
	.end MTA_Lock_Release

	.globl  MTA_Lock_Stats
	.ent 	MTA_Lock_Stats
MTA_Lock_Stats:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 176, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_Lock_Stats
	
	.globl  MTA_Bar_Instr
	.ent 	MTA_Bar_Instr
MTA_Bar_Instr:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 177, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_Bar_Instr
	
	.globl  MTA_acquiesce
	.ent 	MTA_acquiesce
MTA_acquiesce:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 178, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_acquiesce
	
	.globl  MTA_FASTFWD
	.ent 	MTA_FASTFWD
MTA_FASTFWD:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 179, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_FASTFWD
	
	.globl  MTA_RANDOM
	.ent 	MTA_RANDOM
MTA_RANDOM:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 180, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_RANDOM
	
	.globl  MTA_MEM
	.ent 	MTA_MEM
MTA_MEM:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 182, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_MEM
	
	.globl  MTA_PRINTGP
	.ent 	MTA_PRINTGP
MTA_PRINTGP:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 183, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_PRINTGP
	
	.globl  MTA_SHRDADDR
	.ent 	MTA_SHRDADDR
MTA_SHRDADDR:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 185, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_SHRDADDR
	
	.globl  MTA_STOPSIM
	.ent 	MTA_STOPSIM
MTA_STOPSIM:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 186, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_STOPSIM
	
	.globl  MTA_PRINTINSTR
	.ent 	MTA_PRINTINSTR
MTA_PRINTINSTR:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 189, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_PRINTINSTR
	.globl  MTA_DMA_WRITE
	.ent 	MTA_DMA_WRITE

MTA_DMA_WRITE:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 193, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_DMA_WRITE
	.globl  MTA_RMA_WRITE
	.ent 	MTA_RMA_WRITE

MTA_RMA_WRITE:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 194, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_RMA_WRITE
	.global  MTA_DMA_READ
	.ent  MTA_DMA_READ

MTA_DMA_READ:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 195, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_DMA_READ

	.global  MTA_RMA_READ
	.ent  MTA_RMA_READ

MTA_RMA_READ:
	.frame  $sp, 0, $26
	.prologue 0
#	.loc 1 6
	
	mov 196, $0
	call_pal 0x83
	ret	($26)													   # 000006
	.end MTA_RMA_READ


