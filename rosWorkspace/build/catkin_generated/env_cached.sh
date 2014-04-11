#!/usr/bin/env sh
# generated from catkin/cmake/templates/env.sh.in

if [ $# -eq 0 ] ; then
  /bin/echo "Usage: env.sh COMMANDS"
  /bin/echo "Calling env.sh without arguments is not supported anymore. Instead spawn a subshell and source a setup file manually."
  exit 1
fi

# source setup_cached.sh from same directory as this file
_CATKIN_SETUP_DIR=$(cd "`dirname "$0"`" && pwd)
. "$_CATKIN_SETUP_DIR/setup_cached.sh"
exec "$@"
