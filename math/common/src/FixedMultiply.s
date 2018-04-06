#if (__sgi && ML_FIXED_POINT && !ML_MATH_DEBUG)
	.verstamp	3 19
	.option	pic2
	.data	
	.align	2
	.align	0
$$81:
	.ascii	"Assert Failure: FixedMultiply.s: %d: (No overflow in opA*opB) failed!\X0A\X00"
	.text	
	.align	2
	.file	2 "FixedMultiply.s"
	.globl	FixedMultiply__FClT1
/* 	.loc	2 206 */
 # 206	{
	.ent	FixedMultiply__FClT1 2
FixedMultiply__FClT1:
	.option	O1
	.frame	$sp, 0, $31
/*	.loc	2 208 */

 # 207		AuScalar ans; 
 #		
 #		opA * opB -> HI, LO 64-bit multiply w/o overflow.
	mult	$4, $5
 #		
 #		download HI.LO into registers
 #		
	mfhi	$10
	mflo	$11
 #		
 #		HI & sign_mask
 #		
	and	$6, $10, 0x80000000
	
#if defined(ML_DEBUG)
	/**************************************************************/
	/*
	 * if the result is positive, then overflow occured if 
	 *	HI & 0x7fff8000 has any bits on.
	 * But if the result is negative, then overflow occured if 
	 *	~HI & 0x7fff8000 has any bits on.
	 */
 # 	
 #		(~)HI & overflow_mask
 #		
	beq	$6, 0, $102
$101:
	not	$13, $10
	and	$7, $13, 0x7fff8000
	b	$103
$102:
	and	$7, $10, 0x7fff8000
$103:		
 # 	
 #		check whether overflow occured and abort!
 #		
	beq	$7, 0, $105
$104:
	la	$4, __iob
	addu	$4, $4, 16
	la	$5, $$81
	li	$6, 22
	.livereg	0x0E00000E,0x00000000
	jal	fprintf
	la	$4, __iob
	addu	$4, $4, 16
	.livereg	0x0800000E,0x00000000
	jal	fflush
	.livereg	0x0000000E,0x00000000
	jal	abort
$105:			
	/**************************************************************/
#endif
	
 #		
 #		(HI & high_mask) << 16
 #		
	and	$7, $10, 0x7fff
	sll	$12, $7, 16
 #		
 #		(LO & low_mask) >> 16
 #		
	srl	$8, $11, 16
 #		
 #		sign | hi
 #		
	or	$9, $6, $12
 #		
 #		| lo
 #		
	or	$2, $9, $8
	
 # 318		return ans;
	.livereg	0x2000FF0E,0x00000FFF
	j	$31
	.end	FixedMultiply__FClT1
#endif /* (__sgi && ML_FIXED_POINT && !ML_MATH_DEBUG) */
