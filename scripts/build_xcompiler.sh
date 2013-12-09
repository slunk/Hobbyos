BINUTILS_VERSION=2.22.90
GCC_VERSION=4.6.3
GMP_VERSION=4.3.2
MPFR_VERSION=2.4.2
MPC_VERSION=0.8.1

echo "Setting up env variables"
export DIR=$1
export PREFIX="$DIR/opt/cross"
export TARGET=i586-elf
export PATH="$PREFIX/bin:$PATH"

mkdir $DIR/src
mkdir $DIR/src/build-binutils
mkdir $DIR/src/build-gcc
mkdir $DIR/opt
mkdir $DIR/opt/cross

pushd $DIR/src

echo "Downloading sources"
wget ftp://sourceware.org/pub/binutils/snapshots/binutils-$BINUTILS_VERSION.tar.bz2
wget ftp://ftp.gnu.org/gnu/gcc/gcc-4.6.3/gcc-$GCC_VERSION.tar.bz2
wget ftp://gcc.gnu.org/pub/gcc/infrastructure/gmp-$GMP_VERSION.tar.bz2
wget ftp://gcc.gnu.org/pub/gcc/infrastructure/mpfr-$MPFR_VERSION.tar.bz2
wget ftp://gcc.gnu.org/pub/gcc/infrastructure/mpc-$MPC_VERSION.tar.gz

echo "Decompressing sources"
tar xvjf binutils-$BINUTILS_VERSION.tar.bz2
tar xvjf gcc-$GCC_VERSION.tar.bz2
tar xvjf gmp-$GMP_VERSION.tar.bz2
tar xvjf mpfr-$MPFR_VERSION.tar.bz2
tar xvzf mpc-$MPC_VERSION.tar.gz

rm -rf binutils-$BINUTILS_VERSION.tar.bz2
rm -rf gcc-$GCC_VERSION.tar.bz2
rm -rf  gmp-$GMP_VERSION.tar.bz2
rm -rf mpfr-$MPFR_VERSION.tar.bz2
rm -rf mpc-$MPC_VERSION.tar.gz


echo "Building binutils"
pushd build-binutils
../binutils-$BINUTILS_VERSION/configure --target=$TARGET --prefix="$PREFIX" --disable-nls
make -j2
make install
popd

echo "Building gcc"
mv gmp-$GMP_VERSION gcc-$GCC_VERSION/gmp
mv mpfr-$MPFR_VERSION gcc-$GCC_VERSION/mpfr
mv mpc-$MPC_VERSION gcc-$GCC_VERSION/mpc
pushd build-gcc
../gcc-$GCC_VERSION/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make -j2 all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
popd
popd
