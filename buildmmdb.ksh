
if [ "$JDK_HOME" == "" ]
then
	echo "Please set JDK_HOME"
	exit 1
fi
cp src/sql/Makefile.am.mmdb src/sql/Makefile.am
cp src/tools/Makefile.am.mmdb src/tools/Makefile.am
cp src/odbc/Makefile.am.mmdb src/odbc/Makefile.am
cp src/jdbc/Makefile.am.mmdb src/jdbc/Makefile.am
cp src/Makefile.am.mmdb src/Makefile.am

make -f Makefile.cvs

./configure --prefix=`pwd`/install CXXFLAGS="-g  -DMMDB -I$JDK_HOME/include -I$JDK_HOME/include/linux"
make
make install
./csqlinstallmmdb.ksh
