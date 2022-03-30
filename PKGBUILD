pkgname="privacy-protection-messenger-cli"
epoch=1
pkgver=0
pkgrel=0
pkgdesc="terminal interface for secure SSL messenger"
arch=("x86_64")
url="https://github.com/imperzer0/$pkgname"
license=('GPL')
depends=("iptables-nft" "privacy-protection-messenger>=1.0-3")
makedepends=("cmake>=3.0")

_libfiles=("CMakeLists.txt" "main.cpp" "call_backend.hpp")

for _libfile in ${_libfiles[@]}
{
    source=(${source[@]} "local://$_libfile")
}

for _libfile in ${_libfiles[@]}
{
    md5sums=(${md5sums[@]} "SKIP")
}

build()
{
	cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ .
	make
}

package()
{
	install -Dm755 $pkgname "$pkgdir/usr/bin/$pkgname"
}
