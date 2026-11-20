pkgname=breeze6-5.22-git
pkgver=5.22.5.r3425
pkgrel=1
pkgdesc='Breeze 5.22 colors, Qt styles, cursors, KWin decorations, Plasma desktop themes, and GTK styles'
arch=('x86_64')
url='https://github.com/guiodic/breeze6-5.22'
license=('GPL-2.0-or-later' 'LGPL-2.0-or-later' 'LGPL-2.1-only' 'LGPL-3.0-or-later')
depends=('frameworkintegration' 'frameworkintegration5' 'kcmutils' 'kcolorscheme'
         'kconfig' 'kconfig5' 'kconfigwidgets5' 'kcoreaddons' 'kcoreaddons5'
         'kdecoration' 'kguiaddons' 'kguiaddons5' 'ki18n' 'kiconthemes' 'kiconthemes5'
         'kwindowsystem' 'kwindowsystem5' 'qt5-base' 'qt5-declarative' 'qt5-x11extras'
         'qqc2-desktop-style' 'qt6-base>=6.11' 'qt6-declarative' 'qt6-svg')
optdepends=('plasma-workspace: use the bundled Plasma desktop themes'
            'gtk3: use the bundled GTK 3 styles' 'gtk4: use the bundled GTK 4 styles')
provides=("breeze-5.22-git=$pkgver" 'plasma6-style-5.22' 'plasma6-style-5.22-git')
conflicts=('breeze-5.22-git' 'breeze-oldstyle-git' 'plasma6-style-5.22' 'plasma6-style-5.22-git')
makedepends=('cmake' 'extra-cmake-modules' 'git' 'gzip' 'ninja' 'python-cairo' 'sassc')
_gitname=breeze6-5.22
source=("$_gitname::git+$url.git")
sha256sums=('SKIP')

pkgver() {
    git -C "$srcdir/$_gitname" log -1 --format='5.22.5.r%ct.g%h' --abbrev=9
}

build() {
    cmake -S "$srcdir/$_gitname" -B "$srcdir/build" -G Ninja \
        -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr \
        -DKDE_INSTALL_USE_QT_SYS_PATHS=ON -DCMAKE_DISABLE_FIND_PACKAGE_Git=ON \
        -DBUILD_QT5=ON -DBUILD_QT6=ON -DWITH_DECORATIONS=ON
    cmake --build "$srcdir/build"
}

package() {
    DESTDIR="$pkgdir" cmake --install "$srcdir/build"
    for cursor in Breeze Breeze_Snow; do
        install -Dm644 "$srcdir/$_gitname/cursors/$cursor/COPYING-ICONS" \
            "$pkgdir/usr/share/licenses/$pkgname/$cursor/COPYING-ICONS"
    done
}
