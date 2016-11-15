#!/bin/bash
rm *.o *.d
./vpl_run.sh
   if [ "$?" != "0" ]; then
      exit 1
   fi
./vpl_execution