;
; Source file: test/t1.tc
; Target file: test/t1.j
; Sun Dec 15 17:01:07 2019
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
	iconst_2
	istore_1
.line 2
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_1
.line 3
	invokevirtual java/io/PrintStream/println(I)V
.line 4
	iconst_3
	istore_1
.line 5
	bipush 10
	istore_2
.line 6
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_1
.line 7
	invokevirtual java/io/PrintStream/println(I)V
.line 8
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_2
.line 9
	invokevirtual java/io/PrintStream/println(I)V
	return
.end method
