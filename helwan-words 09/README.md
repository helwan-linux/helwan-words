# Helwan Words

**A multilingual word guessing game for Helwan Linux.**

Helwan Words is a simple, lightweight and enjoyable word guessing game designed for **Helwan Linux**.

The game supports multiple languages and provides a clean GTK3 desktop experience without unnecessary complexity.

---

## Features

* 🌍 Multilingual word guessing game
* 🇪🇬 Arabic support
* 🇬🇧 English support
* 🇪🇸 Spanish support
* 🔤 Language-specific letter buttons
* 🐧 Friendly penguin-themed gameplay
* 🎯 Score system
* ⭐ Extra-attempt system
* 🔄 New game / next word support
* 🖥️ GTK3 desktop application
* 🐧 Designed for Helwan Linux
* 📦 Simple native Linux build system
* 🔓 Free and open source under the GPL-3.0 license

---

## Supported Languages

Helwan Words currently supports:

| Language | Word File     | Status    |
| -------- | ------------- | --------- |
| Arabic   | `data/ar.txt` | Supported |
| English  | `data/en.txt` | Supported |
| Spanish  | `data/es.txt` | Supported |

The game uses UTF-8 word files, allowing languages with non-ASCII characters to work correctly.

---

## Gameplay

Choose a language and try to reveal the hidden word by guessing its letters.

Correct guesses reveal letters in the word.

Incorrect guesses reduce the remaining attempts.

Complete the word to win the round and increase your score.

You can also spend points to purchase additional attempts when available.

---

## Building

### Requirements

You need:

* GCC
* Make
* GTK3
* `pkg-config`

On Arch Linux / Helwan Linux:

```bash
sudo pacman -S gcc make gtk3 pkgconf
```

### Build

Clone or download the project, then run:

```bash
make
```

This produces:

```text
helwan-words
```

### Run

During development, the game can be launched directly with:

```bash
./helwan-words
```

When running directly from the source tree, the game can use the word files from:

```text
data/ar.txt
data/en.txt
data/es.txt
```

---

## Installation

The project includes a native Makefile installation target.

Run:

```bash
sudo make install
```

The application is installed as:

```text
/usr/bin/helwan-words
```

Word files are installed under:

```text
/usr/share/helwan-words/data/
```

The application icon is installed under:

```text
/usr/share/icons/hicolor/512x512/apps/
```

The desktop entry is installed under:

```text
/usr/share/applications/
```

---

## Project Structure

```text
helwan-words/
├── src/
│   ├── main.c
│   ├── game.c
│   ├── game.h
│   ├── ui.c
│   └── ui.h
├── data/
│   ├── ar.txt
│   ├── en.txt
│   ├── es.txt
│   └── icons/
│       └── helwan-words.png
├── resources/
│   └── helwan-words.css
├── about.h
├── help.h
├── helwan-words.desktop
├── Makefile
├── PKGBUILD
├── LICENSE
└── README.md
```

---

## Adding Words

To add or update words, edit the appropriate language file:

```text
data/ar.txt
data/en.txt
data/es.txt
```

Each word should be placed on its own line.

Example:

```text
computer
linux
desktop
keyboard
```

UTF-8 characters are supported, including characters used by Arabic and Spanish.

---

## Technology

Helwan Words is written in:

* **C**
* **GTK3**
* **GLib**
* **GDK-Pixbuf**
* **Make**

The game uses native Linux technologies and does not require a web browser or Electron.

---

## Helwan Linux

Helwan Words is developed as part of the **Helwan Linux** project.

Helwan Linux is an Arch Linux-based distribution focused on providing a simple, practical and accessible desktop experience while developing native tools and applications for its users.

**Not just another distro.**

---

## License

Helwan Words is free and open-source software licensed under the:

**GNU General Public License v3.0**

See the `LICENSE` file for the complete license text.

---

## Contributing

Contributions, suggestions, translations, bug reports and improvements are welcome.

If you find a problem or have an idea for improving Helwan Words, please open an issue or contribute to the project.

---

# العربية

## Helwan Words

**لعبة تخمين كلمات متعددة اللغات لنظام Helwan Linux.**

Helwan Words هي لعبة بسيطة وخفيفة لتخمين الكلمات، تم تطويرها لتوفير تجربة ممتعة وسهلة على سطح مكتب Linux.

تدعم اللعبة عدة لغات وتستخدم GTK3 لتقديم تطبيق أصلي وخفيف على النظام.

### المميزات

* 🌍 دعم عدة لغات
* 🇪🇬 العربية
* 🇬🇧 الإنجليزية
* 🇪🇸 الإسبانية
* 🔤 أزرار حروف مناسبة لكل لغة
* 🐧 تصميم مستوحى من البطريق
* 🎯 نظام نقاط
* ⭐ إمكانية شراء محاولات إضافية
* 🔄 جولة جديدة وكلمات جديدة
* 🖥️ تطبيق GTK3 أصلي
* 📦 نظام بناء بسيط
* 🔓 برنامج حر ومفتوح المصدر بترخيص GPL-3.0

### ملفات الكلمات

```text
data/ar.txt
data/en.txt
data/es.txt
```

كل كلمة يجب أن تكون في سطر مستقل.

اللعبة تستخدم UTF-8، ولذلك يمكنها التعامل مع الحروف العربية والحروف غير الإنجليزية مثل `Ñ`.

### البناء

المتطلبات:

* GCC
* Make
* GTK3
* pkg-config

على Arch Linux وHelwan Linux:

```bash
sudo pacman -S gcc make gtk3 pkgconf
```

ثم:

```bash
make
```

وتشغيل اللعبة:

```bash
./helwan-words
```

### التثبيت

```bash
sudo make install
```

سيتم تثبيت البرنامج والملفات اللازمة في المسارات القياسية لنظام Linux.

### الترخيص

Helwan Words برنامج حر ومفتوح المصدر تحت ترخيص:

**GNU General Public License v3.0**

راجع ملف `LICENSE` للحصول على النص الكامل للترخيص.

---

# Español

## Helwan Words

**Un juego multilingüe de adivinación de palabras para Helwan Linux.**

Helwan Words es un juego sencillo y ligero para adivinar palabras, diseñado para ofrecer una experiencia de escritorio limpia y fácil de usar en Linux.

El juego admite varios idiomas y utiliza GTK3 para proporcionar una aplicación nativa y ligera.

### Características

* 🌍 Soporte multilingüe
* 🇪🇬 Árabe
* 🇬🇧 Inglés
* 🇪🇸 Español
* 🔤 Botones de letras específicos para cada idioma
* 🐧 Diseño inspirado en un pingüino
* 🎯 Sistema de puntuación
* ⭐ Posibilidad de comprar intentos adicionales
* 🔄 Nuevas rondas y nuevas palabras
* 🖥️ Aplicación nativa GTK3
* 📦 Sistema de compilación sencillo
* 🔓 Software libre y de código abierto bajo GPL-3.0

### Archivos de palabras

```text
data/ar.txt
data/en.txt
data/es.txt
```

Cada palabra debe estar en una línea independiente.

El juego utiliza UTF-8, por lo que admite correctamente caracteres especiales como `Ñ`.

### Compilación

Requisitos:

* GCC
* Make
* GTK3
* pkg-config

En Arch Linux y Helwan Linux:

```bash
sudo pacman -S gcc make gtk3 pkgconf
```

Después:

```bash
make
```

Para ejecutar el juego:

```bash
./helwan-words
```

### Instalación

```bash
sudo make install
```

### Licencia

Helwan Words es software libre y de código abierto bajo:

**GNU General Public License v3.0**

Consulta el archivo `LICENSE` para obtener el texto completo de la licencia.

---

## Helwan Linux

**Helwan Words is part of the Helwan Linux project.**

Helwan Linux is an Arch Linux-based distribution focused on simplicity, practicality, accessibility and native Linux software.

**Not just another distro.**
