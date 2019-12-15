;
; Source file: test/parsertests/pt2.tc
; Target file: test/parsertests/pt2.j
; Sun Dec 15 16:22:45 2019
;

.source test/parsertests/pt2.tc
.class public parsertests/pt2
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
.line 2
	invokevirtual java/io/PrintStream/println(I)V
	return
.end method
