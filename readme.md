# WkHtmlToPDF

> [!WARNING]
> This not ready for production use yet, here be dragons!

> [!IMPORTANT]
> This is a fork of the original wkhtmltopdf project tailored for use with
> Odoo. It is not intended for general use. If you are looking for the
> original project, please see https://github.com/wkhtmltopdf/wkhtmltopdf

wkhtmltopdf and wkhtmltoimage are command line tools to render HTML into PDF and various image formats using the QT Webkit rendering engine. These run entirely "headless" and do not require a display or display service.

See https://wkhtmltopdf.org for updated documentation.


## Changes

Since this fork doesn't need to follow upstream QT and WebKit, we have made the following opinionated changes:

 - Greatly reduced the amount of style recomputations and layout passes which improves performances by 50% in most cases
 - Disabled bearer networking because it caused file descriptor leaks
 - Merge everything into a single repository, including the patched QT
 - In general, everything that is not needed by wkhtmltopdf has been removed from QT
 - Removed support for DSA since it is deprecated in OpenSSL and breaks the build on archlinux
 - Switched to build system to CuteKit instead of the hand-rolled one
 - Greatly improved tooling and build system with support for CPU and memory profiling

## Roadmap

The long term goal is to make wkhtmltopdf as lean as possible and improve speed and stability. This will be done by:

 - [ ] Slim down QT even further and keep the bare minimum for rendering and networking
 - [ ] Remove the need for X11 and OpenGL
 - [ ] Slim down WebKit and keep the bare minimum for parsing and rendering HTML
 - [ ] Implement an area allocator to reduce memory fragmentation and improve cache locality when building the DOM and CSS Box Tree with the aim of improving performance and reducing memory usage
 - [ ] Add support for more recent versions of CSS and HTML
 - [ ] Remove support for JavaScript (?)

## Building

```bash
$ ./bootstrap.sh tools setup

$ ./bootstrap.sh wk configure

$ ./bootstrap.sh wk build
```

## License

<a href="https://opensource.org/license/lgpl-3-0/">
  <img align="right" height="64" alt="LGPL License" src="doc/lgpl.svg" />
</a>

WkHtmlToPDF is licensed under the **LGPL License**.

The full text of the license can be accessed via [this link](https://opensource.org/license/lgpl-3-0/) and is also included in the [license.txt](license.txt) file of this software package.
