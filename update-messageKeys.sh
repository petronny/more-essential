#!/bin/sh
target=package.json

mv $target $target.old
messageKeys=`grep messageKey src/pkjs/config.js | cut -d ':' -f2`
messageKeys=`echo $messageKeys | sed 's/,$//'`
jq ".pebble.messageKeys=[$messageKeys]" $target.old > $target
