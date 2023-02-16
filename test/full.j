;
; Source file: ./new_tests/full.tc
; Target file: ./new_tests/full.j
; Thu Feb 16 10:22:43 2023
;

.source ./new_tests/full.tc
.class public full
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
	bipush 12
	istore_2
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "k is "
	invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_2
	invokevirtual java/io/PrintStream/println(I)V
	bipush 10
	iconst_2
	idiv
	istore_2
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "k is  after 10 / 2"
	invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_2
	invokevirtual java/io/PrintStream/println(I)V
	iload_2
	iconst_2
	idiv
	istore_2
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "k is  after k / 2"
	invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_2
	invokevirtual java/io/PrintStream/println(I)V
	return
.end method
