# Maintainer: Saeed Badreldin [helwanlinux@gmail.com](mailto:helwanlinux@gmail.com)

pkgname=hel-words
pkgver=1.0.0
pkgrel=1

pkgdesc="Multilingual word guessing game for Helwan Linux"
arch=('x86_64')

url="https://github.com/helwan-linux/helwan-words"
license=('GPL3')

depends=('gtk3')
makedepends=('gcc' 'pkgconf' 'git')

source=("git+https://github.com/helwan-linux/helwan-words.git")
sha256sums=('SKIP')

build() {
cd "$srcdir/helwan-words/helwan-words"

make \
    CFLAGS="-Wall -Wextra -O2 $(pkg-config --cflags gtk+-3.0)" \
    LIBS="$(pkg-config --libs gtk+-3.0)"


}

package() {
cd "$srcdir/helwan-words/helwan-words"


make \
    DESTDIR="$pkgdir" \
    PREFIX=/usr \
    install

install -Dm644 LICENSE/LICENSE \
    "$pkgdir/usr/share/licenses/$pkgname/LICENSE"

}

