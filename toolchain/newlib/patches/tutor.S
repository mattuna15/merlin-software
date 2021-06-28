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
				
// 				00E01598= 00E00D54                3451  trap14_jump     dc.l cout * 0
// 00E0159C= 00E00D76                3452                  dc.l cin * 1
// 00E015A0= 00E00D9A                3453                  dc.l cins * 2
// 00E015A4= 00E0173E                3454                  dc.l OUTPUT   *3
// 00E015A8= 00E0175C                3455                  dc.l out1cr * 4
 */

#include "asm.h"
#include "tutor.h"

	.title "Lib"

	.text
	.global SYM (_exit)
	.global SYM (outln)
	.global SYM (outbyte)
	.global SYM (inbyte)
	.global SYM (havebyte)
	.global SYM (inbyte_noecho)

/*
 * _exit -- Exit from the application. Normally we cause a user trap
 *          to return to the ROM monitor for another run.
 */
	.text
	.align	2
SYM (_exit):
	JMP 0xE00BC0
	
	
	
//no echo E00D9A
/*
 * inbyte - no echo -- get a byte from the console serial port
 *	d0 - contains the byte read in
 *
 * Echoes the character the the console.
 * Converts a carriage return character to newline.
 */
	.text
	.align	2
SYM (inbyte_noecho):
	movem.l	d1/a0,-(sp)		// Save modified registers
	jsr 0xE00D9A
	extw	d0			// Extend byte result to word
	extl	d0			// ...and longword
	
	movem.l	(sp)+,d1/a0		// Restore registers
	rts


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
	jsr 0xE00D76
	extw	d0			// Extend byte result to word
	extl	d0			// ...and longword
	
	movem.l	(sp)+,d1/a0		// Restore registers
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
	cmp	#'\n',d0		// Is it newline?
	bne	notnl2			// Branch if not
	move.b  #'\r',d0		// Carriage return
	move.b #0,d1
	jsr 0x00E00D54
	move.b  #'\n',d0		// Newline
notnl2:
	jsr 0x00E00D54		// Call TUTOR function
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
	
	move.b #4,d1
	jsr 0xE01734

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

	move.b #3,d1
	jsr 0x00E01716

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
