;
; Source file: test/pt2.tc
; Target file: test/pt2.j
; Tue Mar 31 16:18:30 2020
;

.source test/pt2.tc
.class public pt2
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
	iconst_1
	bipush 10
	iadd
	istore_1
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_1
	invokevirtual java/io/PrintStream/println(I)V
	iload_2
	iload_1
	if_icmpge _label0
	iconst_1
	goto _label1
_label0:
	iconst_0
_label1:
	.limit locals 10
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "i is bigger"
	invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
	iconst_0
	.limit locals 10
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "k is bigger"
	invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
	iconst_1
	iconst_1
	iload_1
	imul
	istore_1
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_1
	invokevirtual java/io/PrintStream/println(I)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc " "
	invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
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
