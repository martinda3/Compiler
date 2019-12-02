;
; Source file: test/p3_test.tc
; Target file: test/p3_test.j
; Mon Dec  2 12:27:58 2019
;

.source test/p3_test.tc
.class public p3_test
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
	.limit stack 10
	.limit locals 10
.line 1
	iconst_4
	iload_1
	if_icmple _label0
	iconst_1
	goto _label1
_label0:
	iconst_0
_label1:
.line 2
	iconst_5
	iload_1
.line 3
	iconst_0
.line 4
	iload_1
.line 5
	bipush 10
	iload_2
.line 6
	iconst_1
	iload_2
	iadd
	iload_2
.line 7
.line 8
	bipush 100
	iload_3
.line 9
	return
.end method
