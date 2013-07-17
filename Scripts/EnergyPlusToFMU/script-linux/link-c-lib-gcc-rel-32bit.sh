#!/usr/bin/env  bash


#--- Purpose.
#
#   Link the object file(s) named as command-line arguments.
# ** Use gcc/c.
# ** Make a shared library.
# ** Release version.
# ** Force 32-bit.


#--- Command-line invocation.
#
scriptBaseName=$(basename "$0")
usageStr="USAGE: ./${scriptBaseName}  <name of output>  <name(s) of files to link>"


#--- Check command-line arguments.
#
if test $# -lt 2
then
  echo "Error: ${scriptBaseName}: require at least two command-line arguments"  1>&2
  echo "${usageStr}"  !>&2
  exit 1
fi
#
outputName="$1"
#
# Shift {outputName} off, so object arguments start at $1.
shift 1


#--- Link.
#
gcc -shared -m32 -lm  -o "${outputName}"  "$@"