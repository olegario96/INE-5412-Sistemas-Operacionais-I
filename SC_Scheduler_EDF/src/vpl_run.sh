#!/bin/bash
rm *.o 2>/dev/null
SOURCE_FILES=$(ls *.cpp)
for SOURCE in $SOURCE_FILES
do
   echo "Compiling source file: "$SOURCE
   g++ -c -g -std=c++11 -MMD -MP $SOURCE
   if [ "$?" != "0" ]; then
      echo "ERROR: Compilation error" 1>&2
      exit 1
   fi
done   
OBJECT_FILES=$(ls *.o)
echo "Arquivos objeto: "$OBJECT_FILES
MAIN="a.out"
#echo "Linking object files"
g++ -o $MAIN $OBJECT_FILES
if [ -f $MAIN  ] ; then
    mv $MAIN vpl_execution
    echo "SUCCESS: Executable file created"
else
   echo "ERROR: Could not generate executable file. See error(s) above."
fi
