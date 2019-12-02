;
; Source file: test/t1.tc
; Target file: test/t1.j
; Mon Dec  2 16:20:23 2019
;

.source test/t1.tc
.class public t1
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
	.limit locals 3
.line 1
	iconst_5
	istore_2
.line 2
	iload_2
.line 3
	bipush 100
	istore_1
.line 4
	iload_1
.line 5
	return
.end method
