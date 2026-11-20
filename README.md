# Breeze 5.22 for Plasma 6

The Breeze 5.22.5 palettes and compiled cursors are taken from KDE's
[v5.22.5 release](https://github.com/KDE/breeze/tree/v5.22.5). The Qt Widgets
style and KWin decoration use current Qt and KDecoration3 APIs with the
historical sizing, button shading and window decoration defaults.

Each component can be selected separately in Plasma's System Settings.

| Component | Name or ID |
| --- | --- |
| Application Style | Breeze 5.22 (Qt style key `Breeze-5.22`) |
| Plasma Style | Breeze 5.22, Breeze Light 5.22 and Breeze Dark 5.22 |
| GTK applications | Breeze-5.22 and Breeze-Dark-5.22 |
| Window Decorations | Breeze 5.22 (`org.kde.breeze522`) |
| Colors | Breeze, Breeze Light, Breeze Dark and Breeze High Contrast, each with the 5.22 suffix |
| Cursors | Breeze 5.22 (`breeze_cursors_522`) and Breeze Light 5.22 (`Breeze_Snow_522`) |

The style and decoration settings use `breeze522rc`. All components can be
installed alongside the distribution's Breeze packages.

Choose **Breeze 5.22** in **Application Style** for application menus and
buttons. **Plasma Style** controls the panel, launcher and other shell widgets
through the bundled [Plasma desktop themes](https://github.com/guiodic/plasma6-style-5.22/tree/Plasma6-5.22).

## Qt Quick Controls

For Qt 6 applications, select **Breeze 5.22** in **Application Style** and
start the application with `QT_QUICK_CONTROLS_STYLE=org.kde.breeze522`.
For example, run `QT_QUICK_CONTROLS_STYLE=org.kde.breeze522 systemsettings`
after closing any running System Settings instance.

The Qt Quick style uses `qqc2-desktop-style` for its base controls and adds
Breeze 5.22 menu items and combo-box popups. It installs alongside
`org.kde.desktop`. Applications that explicitly import another Qt Quick
Controls style can choose their own appearance.

## GTK applications

Choose **Breeze-5.22** or **Breeze-Dark-5.22** in Plasma's GNOME/GTK
application style settings. GTK 4 reads the selection from
`~/.config/gtk-4.0/settings.ini` (under `$XDG_CONFIG_HOME` when set).

Apps that use libadwaita select Adwaita when they initialize. To try Breeze
in a GTK 3 or GTK 4 app, close any running instance and set the theme for
the new process:

```sh
GTK_THEME=Breeze-5.22 app-name
```

Use `GTK_THEME=Breeze-Dark-5.22` for the dark variant. Libadwaita apps can
still have widgets whose styling is supplied by libadwaita or the app.

The package includes the GTK 2, GTK 3 and GTK 4 styles from the
[Breeze GTK 5.22.5 release](https://github.com/guiodic/breeze-gtk-5.22/tree/v5.22.5),
generated with the bundled light and dark palettes. GTK 3 and GTK 4 menu items
use a 20 px minimum content height and 5 px padding on each side vertically,
matching the standard 30 px row in the Qt style. GTK 2 uses 5 px vertical
thickness on each side. Larger labels and icons can
increase the row height.

## Arch Linux

Install `base-devel` and `curl`, then run `makepkg -si` as a regular user from the root of
this repository. The `breeze6-5.22-git` package builds both Qt styles and the
KWin decoration and installs the Plasma and GTK styles from a source archive
of the latest commit on `Plasma6-5.22`.
It downloads the source snapshot without cloning the Git history. Run
`makepkg -si` again to update. If you are migrating from `breeze-5.22-git` or
`breeze-oldstyle-git`, let pacman remove the old package when prompted. If you have the standalone
`plasma6-style-5.22` or `plasma6-style-5.22-git` package, let pacman remove it
when prompted. The combined package provides the same three Plasma styles.

## Build manually

A full build requires Qt 5.15, Qt 6.11 or later, KDE Frameworks 5.102 and 6.30
or later, and KDecoration3. The dependencies are listed in the PKGBUILD.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr \
    -DKDE_INSTALL_USE_QT_SYS_PATHS=ON
cmake --build build --parallel
sudo cmake --install build
```

Use `-DBUILD_QT6=OFF -DQT_MAJOR_VERSION=5` for a Qt 5-only build. It also
installs the palettes and cursors. Window decorations and the graphical
settings modules are built with Qt 6, which also installs the Plasma styles.
The default build compresses the Plasma SVGs with gzip. Building the GTK
themes also requires sassc, Python 3 and Pycairo. Use
`-DBUILD_GTK_THEME=OFF` to omit them.
