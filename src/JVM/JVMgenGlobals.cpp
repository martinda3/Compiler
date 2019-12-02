#include <iostream>

namespace toyc {
    int LINE_COUNTER = 0;
  std::string className = "";
  std::string LABELTAG  = "_label";

  std::string INPUT_STREAM_OBJ = "InputStream";
  std::string INPUT_READER_OBJ = "BufferedReader";
  std::string OUTPUT_STREAM_OBJ = "PrintStream";
 
  std::string ROOT_CLASS = "java/lang/Object";
  std::string STRING_CLASS = "java/lang/String";
  std::string STRING_OBJECT = "Ljava/lang/String;";

  std::string SCANNER = "java/util/Scanner";
  std::string BUFFEREDREADER = "java/io/BufferedReader";
  std::string INPUTSTREAMREADER = "java/io/InputStreamReader";
  std::string IOEXCEPTION = "java/io/IOException";
  std::string STRINGTOKENIZER = "java/util/StringTokenizer";

  std::string OUTPUT_FIELD_SPEC = "java/lang/System/out";
  std::string OUTPUT_DESCRIPTOR = "Ljava/io/PrintStream;";
  std::string INPUT_FIELD_SPEC = "java/lang/System/in";
  std::string INPUT_DESCRIPTOR = "Ljava/io/InputStream;";
  
  std::string OBJECT_CONSTRUCTOR =
	        "java/lang/Object/<init>()V";
  std::string INPUTSTREAM_CONSTRUCTOR =
	        "java/io/InputStreamReader/<init>(Ljava/io/InputStream;)V";
  std::string READER_CONSTRUCTOR =
	        "java/io/BufferedReader/<init>(Ljava/io/Reader;)V";
  std::string SCANNER_CONSTRUCTOR =
	        "java/util/Scanner/<init>(Ljava/io/InputStream;)V";
  std::string STRINGTOKENIZER_CONSTRUCTOR = 
		"java/util/StringTokenizer/<init>(Ljava/lang/String;)V";

  std::string PARSEINT_METHOD_SPEC = 
                   "java/lang/Integer/parseInt(Ljava/lang/String;)I";
  std::string PARSEINT_METHOD = 
                   "java/lang/Integer/parseInt";

  std::string READLINE_METHOD_SPEC = 
                   "java/io/BufferedReader/readLine()Ljava/lang/String;";
  std::string READ_INT_METHOD_SPEC =
                   "java/util/Scanner/nextInt()I";
  std::string NEWLINE_METHOD_SPEC = 
                   "java/io/PrintStream/println()V";
  std::string PRINT_INT_METHOD_SPEC = 
                   "java/io/PrintStream/print(I)V";
  std::string PRINT_INT_NEWLINE_METHOD_SPEC = 
                   "java/io/PrintStream/println(I)V";
  std::string PRINT_STRING_METHOD_SPEC = 
                   "java/io/PrintStream/print(Ljava/lang/String;)V";
  std::string NEXT_TOKEN_METHOD_SPEC =
		   "java/util/StringTokenizer/nextToken()Ljava/lang/String;";

}


