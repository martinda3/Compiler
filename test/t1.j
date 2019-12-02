;
; Source file: test/t1.tc
; Target file: test/t1.j
; Mon Dec  2 14:06:05 2019
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
	.limit stack 10
	.limit locals 10
.line 1
	istore_1
	iconst_5
	iload_1
.line 2
	return
.end method
