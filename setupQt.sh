#!/bin/sh
#set -e
if [ -z ${QTVER+x} ] ; then 
    echo "QTVER is unset"
    return 1
fi
echo "Setup Qt version: $QTVER"
if [ $QTVER = "53" ] ; then
    sudo add-apt-repository -y ppa:beineri/opt-qt532-trusty
    sudo apt-get -qq update
    sudo apt-get install -y qt53base qt53declarative qt53quickcontrols qt53quickcontrols2
    QTDIR="/opt/qt53" && PATH="$QTDIR/bin:$PATH"
    source /opt/qt53/bin/qt53-env.sh
elif [ $QTVER = "57" ] ; then
    sudo add-apt-repository -y ppa:beineri/opt-qt571-trusty
    sudo apt-get -qq update
    sudo apt-get install -y qt57base qt57declarative # qt57quickcontrols qt57quickcontrols2
    QTDIR="/opt/qt57" && PATH="$QTDIR/bin:$PATH"
    source /opt/qt57/bin/qt57-env.sh
else
    echo "Unknown version!"
    return 2
fi
#qmake -v
