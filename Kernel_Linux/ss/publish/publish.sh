#!/bin/sh
#ls | grep -v "publish.sh" | xargs rm -rf {}

if [ $# == 2 ] ; then

  python svnchanged_export.py -r $1:$2 ../configure ./configure
  python svnchanged_export.py -r $1:$2 ../work/example_start.sh ./work/
  python svnchanged_export.py -r $1:$2 ../work/example_terminal.sh ./work/
  python svnchanged_export.py -r $1:$2 ../work/export ./work/
  python svnchanged_export.py -r $1:$2 ../build ./build

  package=`ls -d configure work build`
  echo "package=$package"

  tar -cf msserver.tar.gz $package
  tar -cf publish_patch.tar.gz configure.sh  msserver.tar.gz  publish.readme
  rm -rf configure work build msserver.tar.gz

else

  mkdir work

  svn export ../configure/ configure/
  svn export ../build/ build/
  svn export ../work/example_start.sh work/example_start.sh
  svn export ../work/example_terminal.sh work/example_terminal.sh
  svn export ../work/export work/export

  tar -cf msserver.tar.gz build work configure
  tar -cf publish.tar.gz configure.sh  msserver.tar.gz  publish.readme
  rm -rf configure work build msserver.tar.gz
fi

