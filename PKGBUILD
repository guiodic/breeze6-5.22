pkgname=breeze-oldstyle-git
pkgver=5.22.5.r3425
pkgrel=1
pkgdesc='Breeze 5.22 colors, Qt styles, cursors, KWin decorations, Plasma desktop themes, and GTK styles'
arch=('x86_64')
url='https://github.com/guiodic/breeze-oldstyle'
license=('GPL-2.0-or-later' 'LGPL-2.0-or-later' 'LGPL-2.1-only' 'LGPL-3.0-or-later')
depends=('frameworkintegration' 'frameworkintegration5' 'kcmutils' 'kcolorscheme'
         'kconfig' 'kconfig5' 'kconfigwidgets5' 'kcoreaddons' 'kcoreaddons5'
         'kdecoration' 'kguiaddons' 'kguiaddons5' 'ki18n' 'kiconthemes' 'kiconthemes5'
         'kwindowsystem' 'kwindowsystem5' 'qt5-base' 'qt5-declarative' 'qt5-x11extras'
         'qqc2-desktop-style' 'qt6-base>=6.11' 'qt6-declarative' 'qt6-svg')
optdepends=('plasma-workspace: use the bundled Plasma desktop themes'
            'gtk3: use the bundled GTK 3 styles' 'gtk4: use the bundled GTK 4 styles')
provides=("breeze-5.22-git=$pkgver" 'plasma6-style-5.22' 'plasma6-style-5.22-git')
conflicts=('breeze-5.22-git' 'plasma6-style-5.22' 'plasma6-style-5.22-git')
makedepends=('cmake' 'curl' 'extra-cmake-modules' 'gzip' 'ninja' 'python-cairo' 'sassc')
# Keep the resolved revision when makepkg re-reads the recipe under fakeroot.
if [[ -z ${_breeze522_archive_commit:-} ]]; then
    _breeze522_archive_commit=$(curl --fail --silent --show-error --location \
        --header 'Accept: application/vnd.github.sha' \
        https://api.github.com/repos/guiodic/breeze-oldstyle/commits/Plasma6-5.22) || return 1
fi
if [[ ! $_breeze522_archive_commit =~ ^[0-9a-f]{40}$ ]]; then
    printf 'Could not resolve the Plasma6-5.22 commit hash.\n' >&2
    return 1
fi
export _breeze522_archive_commit
_archive_dir=breeze-oldstyle-$_breeze522_archive_commit
source=("$_archive_dir.tar.gz::https://codeload.github.com/guiodic/breeze-oldstyle/tar.gz/$_breeze522_archive_commit")
sha256sums=('SKIP')

pkgver() {
    # GitHub's Git archive preserves the commit timestamp on its root directory.
    local timestamp
    timestamp=$(stat -c %Y "$srcdir/$_archive_dir") || return 1
    printf '5.22.5.r%s.g%s\n' "$timestamp" "${_breeze522_archive_commit:0:9}"
}

build() {
    cmake -S "$srcdir/$_archive_dir" -B "$srcdir/build" -G Ninja \
        -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr \
        -DKDE_INSTALL_USE_QT_SYS_PATHS=ON -DCMAKE_DISABLE_FIND_PACKAGE_Git=ON \
        -DBUILD_QT5=ON -DBUILD_QT6=ON -DWITH_DECORATIONS=ON
    cmake --build "$srcdir/build"
}

package() {
    DESTDIR="$pkgdir" cmake --install "$srcdir/build"
    for cursor in Breeze Breeze_Snow; do
        install -Dm644 "$srcdir/$_archive_dir/cursors/$cursor/COPYING-ICONS" \
            "$pkgdir/usr/share/licenses/$pkgname/$cursor/COPYING-ICONS"
    done
}
