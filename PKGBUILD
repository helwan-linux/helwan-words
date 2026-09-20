# Maintainer: Saeed Badreldin <saeed@helwanlinux.org>

pkgname=helwan-words
pkgver=1.0.0
pkgrel=1

pkgdesc="Multilingual word guessing game for Helwan Linux"
arch=('x86_64')

url="https://github.com/helwan-linux/helwan-games"
license=('GPL3')

depends=('gtk3')
makedepends=('gcc' 'pkgconf')

source=()

build() {
    cd "$srcdir"

    make \
        CFLAGS="-Wall -Wextra -Wpedantic -O2 $(pkg-config --cflags gtk+-3.0)" \
        LIBS="$(pkg-config --libs gtk+-3.0)"
}

package() {
    cd "$srcdir"

    make DESTDIR="$pkgdir" PREFIX=/usr install

    install -Dm644 LICENSE \
        "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
}