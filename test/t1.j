;
; Source file: test/t1.tc
; Target file: test/t1.j
; Sun Dec 15 16:43:31 2019
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
	iconst_3
	istore_1
.line 2
	iconst_0
	istore_2
.line 3
	iconst_2
	istore_3
.line 4
	iconst_2
	istore_1
.line 5
.line 6
	invokevirtual java/io/PrintStream/println(I)V
	return
.end method
