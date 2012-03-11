#!/usr/bin/awk
#
# This script appends additional token codes to the end of the
# parse.h file that lemon generates.  These extra token codes are
# not used by the parser.  But they are used by the tokenizer and/or
# the code generator.
#
#
BEGIN {
  max = 0
}
/^#define TK_/ {
  print $0
  if( max<$3 ) max = $3
}
END {
  printf "#define TK_%-29s %4d\n", "SPACE",           ++max
}
