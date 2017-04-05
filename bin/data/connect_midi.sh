#!/bin/bash

# Connect midi through to virtual midi port on linux
# http://jazz-soft.net/download/Jazz-Plugin/LinuxSynth.html

sudo modprobe snd-virmidi
if aconnect -lo | grep TiMidity > /dev/null; then
  echo TiMidity is already running!
else
  echo Starting TiMidity...
  timidity -iAD > /dev/null
  sleep 1
fi
IFS=$'\n'; arr=`aconnect -lo`
for str in ${arr[@]}; do
  if echo $str | grep -e '^client' > /dev/null; then
    client=`echo $str | sed 's/:.*$//' | sed 's/^.* //'`
    tmdt_curr=""; vrmd_curr=""
  elif echo $str | grep -e '^ *[0-9]* ' > /dev/null; then
    port=`echo $str | sed 's/^ *//' | sed 's/ .*$//'`
    if echo $str | grep TiMidity > /dev/null; then
      tmdt_curr="$client:$port"
      [ ! "$tmdt" ] && tmdt="$tmdt_curr"
    elif echo $str | grep "Midi Through" > /dev/null; then
      vrmd_curr="$client:$port"
      [ ! "$vrmd" ] && vrmd="$vrmd_curr"
    fi
  elif echo $str | grep 'Connecting To:' > /dev/null && [ "$vrmd_curr" ]; then
    conn=`echo $str | sed 's/.*Connecting To: *//'`
    [ "$vrmd_conn" ] && vrmd_conn="$vrmd_conn "
    vrmd_conn="$vrmd_conn$vrmd_curr=$conn"
    vrmd=""
  elif echo $str | grep 'Connected From:' > /dev/null && [ "$tmdt_curr" ]; then
    conn=`echo $str | sed 's/.*Connected From: *//'`
    [ "$tmdt_conn" ] && tmdt_conn="$tmdt_conn "
    tmdt_conn="$tmdt_conn$conn=$tmdt_curr"
    tmdt=""
  fi
done
IFS=' '; arr=`echo $tmdt_conn`
for str in ${arr[@]}; do
  echo $vrmd_conn | grep $str > /dev/null && already_connected=1
done
if [ "$already_connected" ]; then
  echo Already connected!
elif [ "$vrmd" ] && [ "$tmdt" ]; then
  echo Connecting $vrmd to $tmdt...
  aconnect $vrmd $tmdt
else
  echo Cannot connect...
fi
echo
aconnect -lo
