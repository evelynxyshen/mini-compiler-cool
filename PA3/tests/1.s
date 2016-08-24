	.data
	.align	2
	.globl	class_nameTab
	.globl	Main_protObj
	.globl	Int_protObj
	.globl	String_protObj
	.globl	bool_const0
	.globl	bool_const1
	.globl	_int_tag
	.globl	_bool_tag
	.globl	_string_tag
_int_tag:
	.word	4
_bool_tag:
	.word	5
_string_tag:
	.word	6
	.globl	_MemMgr_INITIALIZER
_MemMgr_INITIALIZER:
	.word	_NoGC_Init
	.globl	_MemMgr_COLLECTOR
_MemMgr_COLLECTOR:
	.word	_NoGC_Collect
	.globl	_MemMgr_TEST
_MemMgr_TEST:
	.word	0
	.word	-1
str_const19:
	.word	6
	.word	5
	.word	String_dispTab
	.word	int_const1
	.byte	0	
	.align	2
	.word	-1
str_const18:
	.word	6
	.word	6
	.word	String_dispTab
	.word	int_const5
	.ascii	"String"
	.byte	0	
	.align	2
	.word	-1
str_const17:
	.word	6
	.word	6
	.word	String_dispTab
	.word	int_const3
	.ascii	"Bool"
	.byte	0	
	.align	2
	.word	-1
str_const16:
	.word	6
	.word	5
	.word	String_dispTab
	.word	int_const2
	.ascii	"Int"
	.byte	0	
	.align	2
	.word	-1
str_const15:
	.word	6
	.word	6
	.word	String_dispTab
	.word	int_const3
	.ascii	"Test"
	.byte	0	
	.align	2
	.word	-1
str_const14:
	.word	6
	.word	6
	.word	String_dispTab
	.word	int_const3
	.ascii	"Main"
	.byte	0	
	.align	2
	.word	-1
str_const13:
	.word	6
	.word	5
	.word	String_dispTab
	.word	int_const0
	.ascii	"IO"
	.byte	0	
	.align	2
	.word	-1
str_const12:
	.word	6
	.word	6
	.word	String_dispTab
	.word	int_const5
	.ascii	"Object"
	.byte	0	
	.align	2
	.word	-1
str_const11:
	.word	6
	.word	8
	.word	String_dispTab
	.word	int_const9
	.ascii	"<basic class>"
	.byte	0	
	.align	2
	.word	-1
str_const10:
	.word	6
	.word	12
	.word	String_dispTab
	.word	int_const10
	.ascii	"test String assignment success\n"
	.byte	0	
	.align	2
	.word	-1
str_const9:
	.word	6
	.word	9
	.word	String_dispTab
	.word	int_const11
	.ascii	"Bool3 test: fail\n"
	.byte	0	
	.align	2
	.word	-1
str_const8:
	.word	6
	.word	10
	.word	String_dispTab
	.word	int_const12
	.ascii	"Bool3 test: success\n"
	.byte	0	
	.align	2
	.word	-1
str_const7:
	.word	6
	.word	10
	.word	String_dispTab
	.word	int_const12
	.ascii	"Bool2 test: success\n"
	.byte	0	
	.align	2
	.word	-1
str_const6:
	.word	6
	.word	9
	.word	String_dispTab
	.word	int_const11
	.ascii	"Bool2 test: fail\n"
	.byte	0	
	.align	2
	.word	-1
str_const5:
	.word	6
	.word	9
	.word	String_dispTab
	.word	int_const11
	.ascii	"Bool1 test: fail\n"
	.byte	0	
	.align	2
	.word	-1
str_const4:
	.word	6
	.word	10
	.word	String_dispTab
	.word	int_const12
	.ascii	"Bool1 test: success\n"
	.byte	0	
	.align	2
	.word	-1
str_const3:
	.word	6
	.word	8
	.word	String_dispTab
	.word	int_const13
	.ascii	"Invokation End\n"
	.byte	0	
	.align	2
	.word	-1
str_const2:
	.word	6
	.word	7
	.word	String_dispTab
	.word	int_const14
	.ascii	"Invokation\n"
	.byte	0	
	.align	2
	.word	-1
str_const1:
	.word	6
	.word	8
	.word	String_dispTab
	.word	int_const15
	.ascii	"Hello World\n"
	.byte	0	
	.align	2
	.word	-1
str_const0:
	.word	6
	.word	7
	.word	String_dispTab
	.word	int_const16
	.ascii	"tests/1.cl"
	.byte	0	
	.align	2
	.word	-1
int_const16:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	10
	.word	-1
int_const15:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	12
	.word	-1
int_const14:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	11
	.word	-1
int_const13:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	15
	.word	-1
int_const12:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	20
	.word	-1
int_const11:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	17
	.word	-1
int_const10:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	31
	.word	-1
int_const9:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	13
	.word	-1
int_const8:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	1
	.word	-1
int_const7:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	8
	.word	-1
int_const6:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	7
	.word	-1
int_const5:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	6
	.word	-1
int_const4:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	5
	.word	-1
int_const3:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	4
	.word	-1
int_const2:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	3
	.word	-1
int_const1:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	0
	.word	-1
int_const0:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	2
	.word	-1
bool_const0:
	.word	5
	.word	4
	.word	Bool_dispTab
	.word	0
	.word	-1
bool_const1:
	.word	5
	.word	4
	.word	Bool_dispTab
	.word	1
class_nameTab:
	.word	str_const12
	.word	str_const13
	.word	str_const14
	.word	str_const15
	.word	str_const16
	.word	str_const17
	.word	str_const18
class_objTab:
	.word	Object_protObj
	.word	Object_init
	.word	IO_protObj
	.word	IO_init
	.word	Main_protObj
	.word	Main_init
	.word	Test_protObj
	.word	Test_init
	.word	Int_protObj
	.word	Int_init
	.word	Bool_protObj
	.word	Bool_init
	.word	String_protObj
	.word	String_init
Object_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
String_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	String.length
	.word	String.concat
	.word	String.substr
Bool_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
Int_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
IO_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
Test_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
Main_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Main.myPrint
	.word	Main.main
	.word	-1
Object_protObj:
	.word	0
	.word	3
	.word	Object_dispTab
	.word	-1
String_protObj:
	.word	6
	.word	5
	.word	String_dispTab
	.word	int_const1
	.word	0
	.word	-1
Bool_protObj:
	.word	5
	.word	4
	.word	Bool_dispTab
	.word	0
	.word	-1
Int_protObj:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	0
	.word	-1
IO_protObj:
	.word	1
	.word	3
	.word	IO_dispTab
	.word	-1
Test_protObj:
	.word	3
	.word	3
	.word	Test_dispTab
	.word	-1
Main_protObj:
	.word	2
	.word	10
	.word	Main_dispTab
	.word	str_const19
	.word	str_const19
	.word	int_const1
	.word	int_const1
	.word	bool_const0
	.word	bool_const0
	.word	bool_const0
	.globl	heap_start
heap_start:
	.word	0
	.text
	.globl	Main_init
	.globl	Int_init
	.globl	String_init
	.globl	Bool_init
	.globl	Main.main
Object_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
String_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Bool_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Int_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
IO_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Test_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	IO_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Main_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	IO_init
	la	$a0 str_const1
	sw	$a0 16($s0)
	la	$a0 int_const0
	sw	$a0 20($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Main.myPrint:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	la	$a0 str_const2
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label0
	la	$a0 str_const0
	li	$t1 11
	jal	_dispatch_abort
label0:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$a0 20($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label1
	la	$a0 str_const0
	li	$t1 12
	jal	_dispatch_abort
label1:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$a0 16($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label2
	la	$a0 str_const0
	li	$t1 13
	jal	_dispatch_abort
label2:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label3
	la	$a0 str_const0
	li	$t1 14
	jal	_dispatch_abort
label3:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	la	$a0 str_const3
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label4
	la	$a0 str_const0
	li	$t1 15
	jal	_dispatch_abort
label4:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 24
	jr	$ra	
Main.main:
	addiu	$sp $sp -24
	sw	$fp 24($sp)
	sw	$s0 20($sp)
	sw	$ra 16($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	sw	$s1 8($fp)
	sw	$s2 4($fp)
	sw	$s3 0($fp)
	la	$a0 bool_const0
	lw	$t1 12($a0)
	beqz	$t1 label5
	la	$s3 int_const2
	la	$a0 int_const0
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s3)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s3 $a0
	la	$a0 int_const2
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s3)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s3 $a0
	la	$s2 int_const3
	la	$s1 int_const4
	la	$a0 int_const5
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s1)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s2)
	mul	$t1 $t1 $t2
	sw	$t1 12($a0)
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s3)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s3 $a0
	la	$a0 int_const4
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s3)
	mul	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s3 $a0
	la	$a0 int_const6
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s3)
	mul	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s3 $a0
	la	$a0 int_const7
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s3)
	mul	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s3 $a0
	la	$a0 int_const3
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s3)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s3 $a0
	la	$a0 int_const2
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s3)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	sw	$a0 24($s0)
	sw	$a0 20($s0)
	b	label6
label5:
	la	$s3 int_const8
	la	$s2 int_const0
	la	$a0 int_const2
	jal	Object.copy
	lw	$t1 12($a0)
	neg	$t1 $t1
	sw	$t1 12($a0)
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s2)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s3)
	div	$t1 $t1 $t2
	sw	$t1 12($a0)
	sw	$a0 24($s0)
	sw	$a0 20($s0)
	la	$s3 int_const0
	la	$a0 int_const2
	lw	$t1 12($s3)
	lw	$t2 12($a0)
	la	$a0 bool_const1
	blt	$t1 $t2 label7
	la	$a0 bool_const0
label7:
	sw	$a0 28($s0)
	la	$s3 int_const0
	la	$t2 int_const3
	move	$t1 $s3
	la	$a0 bool_const1
	beq	$t1 $t2 label8
	la	$a1 bool_const0
	jal	equality_test
label8:
	sw	$a0 32($s0)
	la	$a0 int_const0
	jal	Object.copy
	lw	$t1 12($a0)
	neg	$t1 $t1
	sw	$t1 12($a0)
	jal	Object.copy
	lw	$t1 12($a0)
	neg	$t1 $t1
	sw	$t1 12($a0)
	move	$s3 $a0
	la	$a0 int_const2
	lw	$t1 12($s3)
	lw	$t2 12($a0)
	la	$a0 bool_const1
	blt	$t1 $t2 label11
	la	$a0 bool_const0
label11:
	lw	$t1 12($a0)
	la	$a0 bool_const1
	beqz	$t1 label10
	la	$a0 bool_const0
label10:
	lw	$t1 12($a0)
	la	$a0 bool_const1
	beqz	$t1 label9
	la	$a0 bool_const0
label9:
	sw	$a0 36($s0)
	lw	$a0 28($s0)
	lw	$t1 12($a0)
	beqz	$t1 label12
	la	$a0 str_const4
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label14
	la	$a0 str_const0
	li	$t1 25
	jal	_dispatch_abort
label14:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	b	label13
label12:
	la	$a0 str_const5
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label15
	la	$a0 str_const0
	li	$t1 26
	jal	_dispatch_abort
label15:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
label13:
	lw	$a0 32($s0)
	lw	$t1 12($a0)
	beqz	$t1 label16
	la	$a0 str_const6
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label18
	la	$a0 str_const0
	li	$t1 28
	jal	_dispatch_abort
label18:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	b	label17
label16:
	la	$a0 str_const7
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label19
	la	$a0 str_const0
	li	$t1 29
	jal	_dispatch_abort
label19:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
label17:
	lw	$a0 36($s0)
	lw	$t1 12($a0)
	beqz	$t1 label20
	la	$a0 str_const8
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label22
	la	$a0 str_const0
	li	$t1 31
	jal	_dispatch_abort
label22:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	b	label21
label20:
	la	$a0 str_const9
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label23
	la	$a0 str_const0
	li	$t1 32
	jal	_dispatch_abort
label23:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
label21:
label6:
	la	$a0 str_const10
	sw	$a0 12($s0)
	lw	$a0 12($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label24
	la	$a0 str_const0
	li	$t1 37
	jal	_dispatch_abort
label24:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$a0 16($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label25
	la	$a0 str_const0
	li	$t1 38
	jal	_dispatch_abort
label25:
	la	$t1 IO_dispTab
	lw	$t1 12($t1)
	jalr		$t1
	lw	$a0 16($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label26
	la	$a0 str_const0
	li	$t1 39
	jal	_dispatch_abort
label26:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	lw	$s1 8($fp)
	lw	$s2 4($fp)
	lw	$s3 0($fp)
	lw	$fp 24($sp)
	lw	$s0 20($sp)
	lw	$ra 16($sp)
	addiu	$sp $sp 24
	jr	$ra	
