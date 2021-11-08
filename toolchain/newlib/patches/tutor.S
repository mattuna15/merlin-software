/*
 * tutor.S -- board support for the TUTOR monitor.
 *
 * Copyright (c) 1995, 1996 Cygnus Support
 * Copyright (c) 2017, Jeff Tranter <tranter@pobox.com>
 *
 * The authors hereby grant permission to use, copy, modify, distribute,
 * and license this software and its documentation for any purpose, provided
 * that existing copyright notices are retained in all copies and that this
 * notice is included verbatim in any distributions. No written agreement,
 * license, or royalty fee is required for any of the authorized uses.
 * Modifications to this software may be copyrighted by their authors
 * and need not follow the licensing terms described here, provided that
 * the new terms are clearly indicated on the first page of each file where
 * they apply.
 
//  trap14_jump     dc.l cout * 0
//                 dc.l cin * 1
//                 dc.l cins * 2
//                 dc.l OUTPUT   *3
				
 */

#include "asm.h"
#include "tutor.h"

	.title "Lib"

	.text
	.global SYM (_exit)
	.global SYM (outln)
	.global SYM (outbyte)
	.global SYM (inbyte)
	.global SYM (inbyte_noecho)
	.global SYM (havebyte)

/*
 * _exit -- Exit from the application. Normally we cause a user trap
 *          to return to the ROM monitor for another run.
 */
	.text
	.align	2
SYM (_exit):
	move.b	#START,d7
	trap	IMM(14)

/*
 * inbyte -- get a byte from the console serial port
 *	d0 - contains the byte read in
 *
 * Echoes the character the the console.
 * Converts a carriage return character to newline.
 */
	.text
	.align	2
SYM (inbyte):
	movem.l	d1/a0,-(sp)		// Save modified registers
	move.b	#INCHE,d7		// Trap function code
	jsr     0x2f98	
	extw	d0			// Extend byte result to word
	extl	d0			// ...and longword
	cmp	#'\r',d0		// Is it newline?
	bne	notnl1			// Branch if not
	move.b	#'\n',d0		// Convert to newline
notnl1: bsr	outbyte			// Echo it
	movem.l	(sp)+,d1/a0		// Restore registers
	rts

        .text
        .align  2
SYM (inbyte_noecho):
        movem.l d1/a0,-(sp)             // Save modified registers
        move.b  #INCHE,d7               // Trap function code
        jsr     0x2f98
notln2: movem.l (sp)+,d1/a0             // Restore registers
        rts

/*
 * outbyte -- sends a byte out the serial port
 *	d0 - contains the byte to be sent
 *
 * Converts a newline to carriage return and newline.
 */
	.text
	.align	2
SYM (outbyte):
	movem.l	d0/d1/a0,-(sp)		// Save modified registers
	move.b	#OUTCH,d7		// Trap function code
	cmp	#'\n',d0		// Is it newline?
	bne	notnl2			// Branch if not
	move.b  #'\r',d0		// Carriage return
	jsr 0x2e22	
	move.b  #'\n',d0		// Newline
notnl2: jsr 0x2e22	
	movem.l	(sp)+,d0/d1/a0		// Restore registers
	rts

/*
 * outln -- sends a string of bytes out the serial port with a CR/LF
 *	a0 - contains the address of the string's first byte
 *	a1 - contains the address of the string's last byte
 */
	.text
	.align	2
SYM (outln):
	movem.l	d0/d1/a0/a5/a6,-(sp)	// Save modified registers
	move.l	a0,a5			// Start of string
	move.l	a1,a6			// End of string
	addq.l	#1,a6			// Adjust to point to end + 1
	move.b	#OUT1CR,d7		// Trap function code
	jsr 0x2bf8	// Call TUTOR function
	movem.l	(sp)+,d0/d1/a0/a5/a6	// Restore registers
	rts


/*
 * outstr -- sends a string of bytes out the serial port without a CR/LF
 *	a0 - contains the address of the string's first byte
 *	a1 - contains the address of the string's last byte
 */
	.text
	.align	2
SYM (outstr):
	movem.l	d0/d1/a0/a5/a6,-(sp)	// Save modified registers
	move.l	a0,a5			// Start of string
	move.l	a1,a6			// End of string
	addq.l	#1,a6			// Adjust to point to end + 1
	move.b	#OUTPUT,d7		// Trap function code
	jsr 0x2c12	// Call TUTOR function
	movem.l	(sp)+,d0/d1/a0/a5/a6	// Restore registers
	rts
	
/*
 * havebyte -- checks to see if there is a byte in the serial port,
 *             returns 1 if there is a byte, 0 otherwise.
 * TCP0_TxValid    => eth_ctl(6), --Transmit data valid
*        TCP0_TxReady    => eth_ctl(3), --Transmit data ready
*        TCP0_RxValid    => eth_ctl(2), --Receive data valid
*        TCP0_RxReady    => eth_ctl(5)  --Receive data ready
 */
	ACIA1=0xF40045		// ethernet address status
	.text
	.align	2
SYM (havebyte):
	movem.l	a0/d1,-(a7)		// Save working registers
	lea.l	ACIA1,a0		// A0 points to console ACIA
	move.b	(a0),d1			// Read ACIA status
	btst	#2,d1			// Test RDRF bit
	beq.s	RXNOTREADY		// Branch If ACIA Rx not ready
	move.l	#1,d0			// Return 1 to indicate data is available
	movem.l	(a7)+,a0/d1		// Restore working registers
	rts				// Return
RXNOTREADY:
	move.l	#0,d0			// Return 0 to indicate no data available
	movem.l (a7)+,a0/d1		// Restore working registers
	rts
