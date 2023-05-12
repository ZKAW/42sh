#!/bin/bash

MYSHELL="$PWD/42sh"
REFER="/bin/tcsh -f"
TRAPSIG=0

CAT=`which cat`
GREP=`which grep`
SED=`which sed`
RM=`which rm`
TR=`which tr`
HEAD=`which head`
TAIL=`which tail`
WC=`which wc`
CHMOD=`which chmod`
EXPR=`which expr`
MKDIR=`which mkdir`
CP=`which cp`

test_nb=0
failed_tests=0

for i in `env | grep BASH_FUNC_ | cut -d= -f1`; do
    f=`echo $i | sed s/BASH_FUNC_//g | sed s/%%//g`
    unset -f $f
done

disp_test()
{
  id=$1
  $CAT tests/tests_list | $GREP -A1000 "\[$id\]" | $GREP -B1000 "^\[$id-END\]" | $GREP -v "^\[.*\]"
}

run_script()
{
  SC="$1"
  echo "$SC" > /tmp/.tmp.$$
  . /tmp/.tmp.$$
  $RM -f /tmp/.tmp.$$
}

prepare_test()
{
  local testfn="/tmp/.tester.$$"
  local runnerfn="/tmp/.runner.$$"
  local refoutfn="/tmp/.refer.$$"
  local shoutfn="/tmp/.shell.$$"

  WRAPPER="$runnerfn"

  echo "#!/bin/bash" > $runnerfn
  echo "$SETUP" >> $runnerfn
  echo "/bin/bash -c '"$testfn" | "$MYSHELL" ; echo Shell exit with code \$?' > "$shoutfn" 2>&1" >> $runnerfn
  echo "$CLEAN" >> $runnerfn
  echo "$SETUP" >> $runnerfn
  echo "$TCSHUPDATE" >> $runnerfn
  echo "/bin/bash -c '"$testfn" | "$REFER" ; echo Shell exit with code \$?' > "$refoutfn" 2>&1" >> $runnerfn
  echo "$CLEAN" >> $runnerfn

  echo "#!/bin/bash" > $testfn
  echo "$tests_list" | $TR "²" "\n" >> $testfn

  chmod 755 $testfn
  chmod 755 $runnerfn
}

load_test()
{
  id=$1
  debug=$2
  SETUP=`disp_test "$id" | $GREP "SETUP=" | $SED s/'SETUP='// | $SED s/'"'//g`
  CLEAN=`disp_test "$id" | $GREP "CLEAN=" | $SED s/'CLEAN='// | $SED s/'"'//g`
  NAME=`disp_test "$id" | $GREP "NAME=" | $SED s/'NAME='// | $SED s/'"'//g`
  TCSHUPDATE=`disp_test "$id" | $GREP "TCSHUPDATE=" | $SED s/'TCSHUPDATE='// | $SED s/'"'//g`
  tests_list=`disp_test "$id" | $GREP -v "SETUP=" | $GREP -v "CLEAN=" | $GREP -v "NAME=" | $GREP -v "TCSHUPDATE=" | $GREP -v "tests_list=" | $TR "\n" "²" | $SED s/"²$"//`
  prepare_test
  $WRAPPER
  nb=`$CAT /tmp/.refer.$$ | $GREP -v '^_=' | $GREP -v '^\[1\]' | $WC -l`
  i=1
  ok=1
  while [ $i -le $nb ]
  do
    l=`$CAT /tmp/.refer.$$ | $GREP -v '^_=' | $GREP -v '^\[1\]' | $HEAD -$i | $TAIL -1`
    a=`$CAT /tmp/.shell.$$ | $GREP -v '^_=' | $GREP -v '^\[1\]' | $GREP -- "$l$" | $WC -l`
    if [ $a -eq 0 ]
    then
      ok=0
    fi
    i=`$EXPR $i + 1`
  done

  if [ $ok -eq 1 ]
  then
    if [ $debug -ge 1 ]
    then
      echo "Test $id ($NAME) : OK"
      if [ $debug -eq 2 ]
      then
        echo "Output $MYSHELL :"
        $CAT -e /tmp/.shell.$$
        echo "" 
        echo "Output $REFER :"
        $CAT -e /tmp/.refer.$$
        echo ""
      fi
    else
      echo "OK"
    fi
  else
    failed_tests=$((failed_tests+1))
    if [ $debug -ge 1 ]
    then
      echo "Test $id ($NAME) : KO - Check output in /tmp/test.$$/$id/" 
      $MKDIR -p /tmp/test.$$/$id 2>/dev/null
      $CP /tmp/.shell.$$ /tmp/test.$$/$id/mysh.out
      $CP /tmp/.refer.$$ /tmp/test.$$/$id/tcsh.out
    else
      echo "KO"
    fi
  fi
}

if [ $TRAPSIG -eq 1 ]
then
  for sig in `trap -l`
  do
    echo "$sig" | grep "^SIG" >/dev/null 2>&1
    if [ $? -eq 0 ]
    then
      trap "echo Received signal $sig !" $sig
    fi
  done
fi

if [ ! -f tests/tests_list ]
then
  echo "No tests_list file. Please read README.ME" >&2
  exit 1
fi

if [ ! -f $MYSHELL ]
then
  echo "$MYSHELL not found" >&2
  exit 1
fi

if [ $# -eq 2 ]
then
  echo "Debug mode" >&2
  echo "Shell : $MYSHELL" >&2
  echo "Reference : $REFER" >&2
  echo ""
fi

if [ $# -eq 0 ]
then
  for lst in `cat tests/tests_list | grep "^\[.*\]$" | grep -vi end | sed s/'\['// | sed s/'\]'//`
  do
    test_nb=$((test_nb+1))
    path_backup=$PATH
    load_test $lst 1
    export PATH=$path_backup
  done
else
  if [ $# -eq 1 ]
  then
    load_test $1 0
  else
    if [ "X$1" = "X-d" ]
    then
      load_test $2 2
    else
      load_test $1 2
    fi
  fi
fi

echo -e "\nTests results:"
if [ $failed_tests -eq 0 ]; then
    echo -e "\e[32mAll tests passed\e[0m"
else
    # echo -e "\e[31m$failed_tests/$test_nb tests failed\e[0m"
    echo -e "\e[31m$failed_tests\e[0m/\e[31m$test_nb\e[0m tests failed"
fi