;
; Source file: test/ex_2.tc
; Target file: test/ex_2.j
; Sun Dec  1 20:17:24 2019
;

.source test/ex_2.tc
.class public ex_2
.super java/lang/Object

.method public <init>()V
	.limit stack 1
	.limit locals 1
.line 0
	aload_0
	invokespecial java/lang/Object/<init>()V
	return
.end method

.method public static main([Ljava/lang/String;)V
	.limit stack 2
	.limit locals 2
.line 1
	iconst_5
	iload 16908546
.line 2
	iconst_1
	iload 808333614
.line 3
	iconst_0
	iload 0
.line 4
	iload 16908546
	iload 808333614
	if_icmpgt _label0
	iconst_1
	goto _label1
_label0:
	iconst_0
_label1:
.line 5
	iload 808333614
	iload 0
	iadd
	iload 0
.line 6
	iconst_1
	iload 808333614
	iadd
	iload 808333614
.line 7
	return
.end method
