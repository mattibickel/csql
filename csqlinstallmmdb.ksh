#!/bin/sh
#Should run this command from the project root directory

#TODO:validate it is project root by checking some files
root_dir=`pwd`
install_dir=`grep "prefix = /" Makefile|tail -1|awk '{ print $3 }'`
if [ -z "$install_dir" ]
then
    echo "install_dir is not set properly."
    exit 1
fi

echo "installdir is ${install_dir}"
cd src/jdbc
./buildJdbcDriver.ksh
mkdir -p ${install_dir}/lib
cp CSqlJdbcDriver.jar ${install_dir}/lib
cd ${root_dir}

rm ${install_dir}/lib/*.la
rm ${install_dir}/lib/*.a

mkdir -p ${install_dir}/sample
cp  ${root_dir}/setupenv.ksh.install ${install_dir}/setupenv.ksh

cp ${root_dir}/README ${install_dir}/README
cp ${root_dir}/COPYING ${install_dir}
cp ${root_dir}/AUTHORS ${install_dir}
cp ${root_dir}/ChangeLog ${install_dir}
cp ${root_dir}/csql.conf.mmdb ${install_dir}/sample/csql.conf
cp ${root_dir}/setupenv.ksh.install ${install_dir}/setupenv.ksh

cp -R ${root_dir}/examples ${install_dir}
find ${install_dir}/examples -name "CVS" -exec rm -rf {} \; 2>/dev/null
rm -rf ${install_dir}/examples/dbapi

cp -R ${root_dir}/docs ${install_dir}
find ${install_dir}/docs -name "CVS" -exec rm -rf {} \; 2>/dev/null

rm -rf ${install_dir}/demo
mkdir ${install_dir}/demo
cp -R ${root_dir}/demo/wisc ${install_dir}/demo
find ${install_dir}/demo -name "CVS" -exec rm -rf {} \; 2>/dev/null
cp -R ${root_dir}/scripts ${install_dir}
find ${install_dir}/scripts -name "CVS" -exec rm -rf {} \; 2>/dev/null

cd ${root_dir}
echo "Build completed Successfully"
