;
; Source file: test/t1.tc
; Target file: test/t1.j
; Sun Dec 15 18:00:57 2019
;

.source test/t1.tc
.class public t1
.super java/lang/Object

.method public <init>()V
	.limit stack 1
	.limit locals 1
	aload_0
	invokespecial java/lang/Object/<init>()V
	return
.end method

.method public static main([Ljava/lang/String;)V
	.limit stack 10
	.limit locals 10
	iconst_2
	istore_1
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_1
	invokevirtual java/io/PrintStream/println(I)V
	iconst_3
	istore_1
	bipush 10
	istore_2
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_1
	invokevirtual java/io/PrintStream/println(I)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_2
	invokevirtual java/io/PrintStream/println(I)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "THis is a string etest"
	invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "1000"
	invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
	return
.end method
